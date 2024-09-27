#include <ShaderInterface.h>
#include "../debug/debug.h"

char *ShaderInterface::loadTextFromFile(const char *file)
{
    FILE *currentFile = fopen(file, "rt");
    fseek(currentFile, 0, SEEK_END);
    int count = (int)ftell(currentFile);
    rewind(currentFile);

    char *data = (char *)malloc(sizeof(char)* (count +1));
    count = (int)fread(data, sizeof(char), count, currentFile);
    data[count] = '\0';

    return data;
}

GLuint ShaderInterface::getProgramHandle()
{
    return shader->getProgramHandle();
}


GLint ShaderInterface::get_aPositionVertex()
{
    return _aPositionVertex;
}

GLint ShaderInterface::get_uColor()
{
    return _uColor;
}

void ShaderInterface::Bind() const
{
    glUseProgram(shader->getProgramHandle());
}
void ShaderInterface::UnBind() const
{
    glUseProgram(0);
}
void ShaderInterface::SetUniform4F(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
 int ShaderInterface::GetUniformLocation(const std::string &name)
{
    int location = glGetUniformLocation(shader->getProgramHandle(), name.c_str());
    if (location == -1)
    {
        debugLog("Uniform %s not found", name.c_str());
    }
    return location;
}
ShaderInterface::ShaderInterface(const char *VS, const char *FS)
{
    _vertexShaderString = loadTextFromFile(VS);
    _fragmentShaderString = loadTextFromFile(FS);
    shader = new ShaderLoader(_vertexShaderString, _fragmentShaderString);//gives an ID and if var doesnt exist returns -1
  }

ShaderInterface::~ShaderInterface()
{
    delete shader;
}
