#ifndef GAMEFONT_H
#define GAMEFONT_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>




struct Glyph
{
    glm::vec2 offset;
    glm::vec2 advance;
    glm::vec2 textureCoords;
    glm::vec2 size;

};

void LoadFont(const char* filePath, int fontSize);
struct FontData
{
    FontData(){};
    ~FontData(){}
    int fontHeight;
    Glyph glyphs[127];
};





#endif // GAMEFONT_H
