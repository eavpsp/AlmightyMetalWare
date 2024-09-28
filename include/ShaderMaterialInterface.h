#ifndef SHADERMATERIALINTERFACE_H
#define SHADERMATERIALINTERFACE_H

#include <string>
#include <vector>
#include <ShaderInterface.h>
//must have the uniforms based on the shader, therefore this must be a template class and for each shader, a material must be associated with it
//we know uniforms are identified by name, therefore having a vector the uniforms can be indexed by name
//create a custom list struct that finds, stores, and returns data

//create constructor that stores the shader uniforms into the material it creates
class ShaderMaterialInterface
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
        int GetUniformLocation(const std::string &name);
        ShaderMaterialInterface(){};
        ~ShaderMaterialInterface();
    
};

class LightMaterial : public ShaderMaterialInterface
{
    public:
        GLint loc_mdlvMtx, loc_projMtx;
        GLint loc_lightPos, loc_ambient, loc_diffuse, loc_specular;
        LightMaterial(){};
        ~LightMaterial(){};
};

class ColorMaterial : public ShaderMaterialInterface
{
    public:
        GLint aColor, aVertexPosition;
        ColorMaterial(){};
        ~ColorMaterial(){};
};

#endif // SHADERMATERIALINTERFACE_H
