#include "Texture.h"
#include <ResourceManager.h>
#include "../debug/debug.h"

 
/**
 * \brief Texture constructor
 * \param path Path to the image file
 *
 * Reads image data from file located at \p path and creates a texture
 * object from it. The texture object is created with linear filtering
 * and clamping to edge for both S and T coordinates.
 *
 * \warning The texture object is created with a single mipmap level.
 *          If you need multiple mipmap levels, you should use
 *          glGenerateMipmap() function after binding the texture.
 *          Additionally, the texture object is created with a single
 *          sample. If you need multisampled textures, you should use
 *          glTexImage2DMultisample() function.
 */
extern ResourceManager *gameResourceManager;
MW_Texture::MW_Texture(const char* path, int slot) : filePath(path),  _textureID(0), _width(0), _height(0), _bpp(0)
{
    debugLog("Texture: %s\n", path);
    stbi_set_flip_vertically_on_load(true);
    _localBuffer = stbi_load(path, &_width, &_height, &_bpp, 4);
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    if(_localBuffer)
    {
        stbi_image_free(_localBuffer);
    }
    debugLog("Texture loaded: %s\n", path);

    
}
//
MW_Texture::~MW_Texture()
{
    glDeleteTextures(1, &_textureID);
}

void MW_Texture::Bind(unsigned int slot)
{

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    
}


void MW_Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);

}
