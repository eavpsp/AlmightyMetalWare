#include <GameFont.h>
#include <glad/glad.h>
#include <ResourceManager.h>
#include "../debug/debug.h"
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
void LoadFont(const char *filePath, int fontSize)
{
  FT_Library fontLibrary;
  FT_Init_FreeType(&fontLibrary);
    if (fontLibrary == NULL)
    {
        debugLog("Failed to initialize FreeType Library");
        return;
    }
    
  FT_Face fontFace;
  FT_New_Face(fontLibrary, filePath, 0, &fontFace);
  if (fontFace == NULL)
  {
    debugLog("Failed to load font");
    return;
  }
  
  FT_Set_Pixel_Sizes(fontFace, 0, fontSize);

  int padding = 2;
  int row = 0;
  int col = padding;

  const int textureWidth = 512;
  char textureBuffer[textureWidth  * textureWidth];
  for (FT_ULong glyphIdx = 32; glyphIdx < 127; ++glyphIdx)
  {
    FT_UInt glyphIndex = FT_Get_Char_Index(fontFace, glyphIdx);
    FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_DEFAULT);
    FT_Error error = FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

    if (col + fontFace->glyph->bitmap.width + padding >= 512)
    {
      col = padding;
      row += fontSize;
    }

    // Font Height
  gameResourceManager->fontData->fontHeight = 
  glm::max(static_cast<int>((fontFace->size->metrics.ascender - fontFace->size->metrics.descender) >> 6), 
          gameResourceManager->fontData->fontHeight);

    for (unsigned int y = 0; y < fontFace->glyph->bitmap.rows; ++y)
    {
      for (unsigned int x = 0; x < fontFace->glyph->bitmap.width; ++x)
      {
        textureBuffer[(row + y) * textureWidth + col + x] =
            fontFace->glyph->bitmap.buffer[y * fontFace->glyph->bitmap.width + x];
      }
    }

    Glyph* glyph = &gameResourceManager->fontData->glyphs[glyphIdx];
    glyph->textureCoords = {col, row};
    glyph->size = 
    { 
      (int)fontFace->glyph->bitmap.width, 
      (int)fontFace->glyph->bitmap.rows
    };
    glyph->advance = 
    {
      (float)(fontFace->glyph->advance.x >> 6), 
      (float)(fontFace->glyph->advance.y >> 6)
    };
    glyph->offset =
    {
      (float)fontFace->glyph->bitmap_left,
      (float)fontFace->glyph->bitmap_top,
    };

    col += fontFace->glyph->bitmap.width + padding;
  }

  FT_Done_Face(fontFace);
  FT_Done_FreeType(fontLibrary);

  // Upload OpenGL Texture
  {
    glGenTextures(1, (GLuint*)&gameResourceManager->fontAtlasID);
    glActiveTexture(GL_TEXTURE1); // Bound to binding = 1, see quad.frag
    glBindTexture(GL_TEXTURE_2D, gameResourceManager->fontAtlasID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, textureWidth, textureWidth, 0, 
                 GL_RED, GL_UNSIGNED_BYTE, (char*)textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
}
