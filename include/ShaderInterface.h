#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
#include <ShaderLoader.h>
#include <glad/glad.h>  // glad library (OpenGL loader)
#include <string>

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
    //uniform types
    GLint get_aPositionVertex();
    GLint get_uColor();

    void Bind() const;
    void UnBind() const;
    //set uniforms
    void SetUniform4F(const std::string &name, float v0, float v1, float v2, float v3);
    int GetUniformLocation(const std::string &name);

    ShaderInterface(const char *VS, const char *FS);
    ~ShaderInterface();

};
