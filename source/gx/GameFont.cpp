#include <GameFont.h>
#include <glad/glad.h>
#include "../debug/debug.h"
#include <ResourceManager.h>
#include <RenderSystem.h>
extern RenderSystem *gameRenderSystem;
extern ResourceManager *gameResourceManager;
/**
 * @brief Load a font from a file into the GameFont object.
 *
 * Given a .ttf file path and a font size, this function will load the font
 * into the GameFont object. This function will also generate a texture atlas
 * containing the glyphs of the font, and upload it to OpenGL.
 *
 * The generated texture atlas is a 512x512 image, with each glyph aligned
 * horizontally. The texture coordinates for each glyph is stored in the
 * Glyph member of the GameFont object.
 *
 * @param[in] filePath The path to the .ttf file.
 * @param[in] fontSize The size of the font to load.
 */
void GameFont::LoadFont(const char *filePath, int fontSize)
{

    glUseProgram(gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->getShaderInterface()->getProgramHandle());
    mdlvMtx = gameRenderSystem->ortho_projection * gameRenderSystem->mainCamera->transform;
            
    gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->SetUniformMat4F("projection", mdlvMtx);
    






    this->size = size;

    // Initialize FreeType
    FT_Init_FreeType(&ft);

    // Load the font file
    FT_New_Face(ft, filePath, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 48); 
    // Set the font size
    FT_Set_Char_Size(face, 0, size * 64, 0, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Create a texture to store the font glyphs
    for (unsigned char c = 0; c < 128; c++)
    {
      // load character glyph 
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
          debugLog("ERROR::FREETYTPE: Failed to load Glyph");
          continue;
      }
      // generate texture
      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
      );
      // set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // now store character for later use
      Character character = {
          texture, 
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          face->glyph->advance.x
      };
      this->Characters.insert(std::pair<char, Character>(c, character));
    }
    // Create a VAO and VBO to store the font vertex data
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}




void GameFont::RenderText(std::string text, glm::vec2 pos, float scale, glm::vec3 color)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
   
    // activate corresponding render state	
    glUseProgram(gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->getShaderInterface()->getProgramHandle());
    glUniform3f(glGetUniformLocation(gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->getShaderInterface()->getProgramHandle(), "textColor"), color.x, color.y, color.z);
    mdlvMtx = gameRenderSystem->ortho_projection * gameRenderSystem->mainCamera->transform;      
    gameResourceManager->_engineMaterials.getGameFontMaterial()->shader->SetUniformMat4F("projection", mdlvMtx);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = this->Characters[*c];

        float xpos = pos.x + ch.Bearing.x * scale;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_ONE, GL_ZERO);
}


GameFont::~GameFont()
{
     // Clean up FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


}
