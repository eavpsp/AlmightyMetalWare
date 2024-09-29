#include "ShaderMaterialInterface.h"
#include "../debug/debug.h"
void ShaderMaterialInterface::SetUpShader(std::string name, ShaderInterface *_shaderInterface)
{
    this->name = name;
    this->_shaderInterface = _shaderInterface;

}

ShaderInterface *ShaderMaterialInterface::getShaderInterface()
{
    return _shaderInterface;
}

void ShaderMaterialInterface::SetUniform4F(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
 int ShaderMaterialInterface::GetUniformLocation(const std::string &name)
{
    int location = glGetUniformLocation(_shaderInterface->getProgramHandle(), name.c_str());
    if (location == -1)
    {
        debugLog("Uniform %s not found", name.c_str());
    }
    return location;
}
void ShaderMaterialInterface::SetUniformMat4F(const std::string &name, glm::mat4 &matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,&matrix[0][0]);
}
void ShaderMaterialInterface::SetUniform1f(const std::string &name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}
void ShaderMaterialInterface::SetUniform1i(const std::string &name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}
ShaderMaterialInterface::~ShaderMaterialInterface()
{
    delete _shaderInterface;

   
    delete &name;
}

