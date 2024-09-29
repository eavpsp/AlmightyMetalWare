#ifndef SHADERMATERIALINTERFACE_H
#define SHADERMATERIALINTERFACE_H

#include <string>
#include <vector>
#include <ShaderInterface.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//must have the uniforms based on the shader, therefore this must be a template class and for each shader, a material must be associated with it
//we know uniforms are identified by name, therefore having a vector the uniforms can be indexed by name
//create a custom list struct that finds, stores, and returns data

//create constructor that stores the shader uniforms into the material it creates
struct ShaderMaterialInterface
{
    private:
       
        ShaderInterface *_shaderInterface;//shader handler
       
    public:
        std::string name;//shader name
        void SetUpShader(std::string name, ShaderInterface *_shaderInterface);
        ShaderInterface* getShaderInterface();
        //set uniforms
        void SetUniform4F(const std::string &name, float v0, float v1, float v2, float v3);
        void SetUniform1f(const std::string &name, float value);
        void SetUniform1i(const std::string &name, int value);
        void SetUniformMat4F(const std::string &name, glm::mat4& matrix);
        void SetUniform3F(const std::string &name, float v0, float v1, float v2);
        int GetUniformLocation(const std::string &name);
        ShaderMaterialInterface(){};
        ~ShaderMaterialInterface();
    
};

struct LightMaterial : public ShaderMaterialInterface
{
    public:
        GLint loc_mdlvMtx, loc_projMtx;
        GLint loc_lightPos, loc_ambient, loc_diffuse, loc_specular;
        LightMaterial(){};
        ~LightMaterial(){};
};

struct ColorMaterial : public ShaderMaterialInterface
{
    public:
        GLint aColor, aVertexPosition;
        ColorMaterial(){};
        ~ColorMaterial(){};
};

#endif // SHADERMATERIALINTERFACE_H
