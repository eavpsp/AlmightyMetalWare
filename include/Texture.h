#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdlib.h>
#include <glad/glad.h>
#include <string>
#include <stb_image.h>
class MW_Texture
{
    private:
        GLuint _textureID;
        std::string filePath;
        unsigned char* _localBuffer;
        int _width;
        int _height;
        int _bpp;

    public:
        MW_Texture(const char* path, int slot = 0);
        ~MW_Texture();

        void Bind(unsigned int slot = 0);
        void UnBind();

        inline int GetWidth() { return _width; }
        inline int GetHeight() { return _height; }
};
#endif