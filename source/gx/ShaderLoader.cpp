#include "ShaderLoader.h"

GLuint ShaderLoader::compileShader(GLenum targetShader, const char *source)
{
    GLuint shaderHandle = glCreateShader(targetShader); //get the shader handle from the target
    glShaderSource(shaderHandle, 1, &source, NULL);
    glCompileShader(shaderHandle);
    return shaderHandle;
}

GLuint ShaderLoader::getProgramHandle()
{
    return _programHandle;
}

ShaderLoader::ShaderLoader(const char *sourceVs, const char *sourceFS)
{
    //create the shader program
    _programHandle = glCreateProgram();
    //compile vertex and fragment shaders seperately
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, sourceVs);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, sourceFS);
    //attach them to the shader program
    glAttachShader(_programHandle, vertexShader);
    glAttachShader(_programHandle, fragmentShader);

    glLinkProgram(_programHandle);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderLoader::~ShaderLoader()
{
    glDeleteProgram(_programHandle);
}
