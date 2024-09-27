#include "Texture.h"
#include "stb_image.h"

 
Texture::Texture(std::string& path) : filePath(path),  _textureID(0), _width(0), _height(0), _bpp(0)
{

    stbi_set_flip_vertically_on_load(true);
    _localBuffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 4);
    glGenTextures(1, &_textureID);
    glBindBuffer(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
    glBindBuffer(GL_TEXTURE_2D, 0);
    if(_localBuffer)
    {
        stbi_image_free(_localBuffer);
    }
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &_textureID);
}

void Texture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindBuffer(GL_TEXTURE_2D, _textureID);

}


void Texture::UnBind()
{
    glBindBuffer(GL_TEXTURE_2D, 0);

}
