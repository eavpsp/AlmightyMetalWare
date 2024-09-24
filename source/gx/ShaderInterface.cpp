#include <ShaderInterface.h>


char *ShaderInterface::loadTextFromFile(char *file)
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
    return GLuint();
}

GLint ShaderInterface::get_aPositionVertex()
{
    return _aPositionVertex;
}

GLint ShaderInterface::get_uColor()
{
    return _uColor;
}

ShaderInterface::ShaderInterface(char *VS, char *FS)
{
    _vertexShaderString = loadTextFromFile(VS);
    _fragmentShaderString = loadTextFromFile(FS);
    shader = new ShaderLoader(_vertexShaderString, _fragmentShaderString);//gives an ID and if var doesnt exist returns -1
    _aPositionVertex = glGetAttribLocation(shader ->getProgramHandle(), "aPositionVertex");
    _uColor = glGetUniformLocation(shader ->getProgramHandle(), "uColor");
}

ShaderInterface::~ShaderInterface()
{
    delete shader;
}
