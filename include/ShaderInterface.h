#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <ShaderLoader.h>
#include <glad/glad.h>  // glad library (OpenGL loader)

class ShaderInterface
{
    private:
    GLint _aPositionVertex;
    GLint _uColor;
    ShaderLoader *shader;
    char *_vertexShaderString;
    char *_fragmentShaderString;
    char *loadTextFromFile(const char *file);
    public:
    GLuint getProgramHandle();
    GLint get_aPositionVertex();
    GLint get_uColor();


    ShaderInterface(const char *VS, const char *FS);
    ~ShaderInterface();

};
