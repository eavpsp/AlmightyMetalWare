#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdlib.h>
#include <glad/glad.h>
#include <string>
class Texture
{
    private:
        GLuint _textureID;
        std::string filePath;
        unsigned char* _localBuffer;
        int _width;
        int _height;
        int _bpp;

    public:
        Texture(std::string& path);
        ~Texture();

        void Bind(unsigned int slot);
        void UnBind();

        inline int GetWidth() { return _width; }
        inline int GetHeight() { return _height; }
};
#endif