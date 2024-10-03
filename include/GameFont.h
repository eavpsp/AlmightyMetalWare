#ifndef GAMEFONT_H
#define GAMEFONT_H

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <string>
#include <vector>
#include <VertexArray.h>
#include <ShaderMaterialInterface.h>
#include <ft2build.h>
#include FT_FREETYPE_H
struct Character 
{
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class GameFont
{
     public:
        FT_Library ft;
        FT_Face face;
        GLuint texture;
        GLuint VAO, VBO;
        int size;
        std::map<char, Character> Characters;
        glm::mat4 mdlvMtx;
        void LoadFont(const char* filePath, int fontSize);
        void RenderText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
        template <typename... Args>
        void draw_format_ui_text(char* format, glm::vec2 pos, float scale, glm::vec3 color, Args... args)
        {
        char* text = format_text(format, args...);
            RenderText(text, pos, scale, color);
        }
        GameFont(const char* filePath, int fontSize)
        {
            LoadFont(filePath, fontSize);
        };
        ~GameFont();
};





#endif // GAMEFONT_H
