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
        LightMaterial(){};
        ~LightMaterial(){};
};

struct LightObjectMaterial : public ShaderMaterialInterface
{
    public:
        LightObjectMaterial(){};
        ~LightObjectMaterial(){};
};
struct ColorMaterial : public ShaderMaterialInterface
{
    public:
        ColorMaterial(){};
        ~ColorMaterial(){};
};

/*
        glUseProgram(_resourceManager->_engineMaterials.getLightObjectMaterial()->getShaderInterface()->getProgramHandle()); //LIGHT OBJ
        _resourceManager->_engineMaterials.getLightObjectMaterial()->SetUniform4F("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        _resourceManager->_engineMaterials.getLightObjectMaterial()->SetUniformMat4F("model", lightObject);
       //light shader
        glUseProgram(_resourceManager->_engineMaterials.getLightMaterial()->getShaderInterface()->getProgramHandle()); //LIGHT MAT
       //check for texture
        if(_resourceManager->gameObjects->at(0)->objectModel->meshes.at(0).textures.size() != NULL)
        {
            _resourceManager->gameObjects->at(0)->objectModel->meshes.at(0).textures.at(0).Bind(0);
        }
        _resourceManager->_engineMaterials.getLightMaterial()->SetUniformMat4F("model", _resourceManager->gameObjects->at(0)->transform);
        _resourceManager->_engineMaterials.getLightMaterial()->SetUniform4F("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        _resourceManager->_engineMaterials.getLightMaterial()->SetUniform3F("u_LightPos", lightPos.x, lightPos.y, lightPos.z);

*/
//struct material data 
    struct Material
    {
        std::string name;
        ShaderMaterialInterface *materials;
    };

    //struct ColorMaterial : public Material;

    struct LightObjectMaterials : public Material
    {
        public :
            glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                materials->SetUniformMat4F("model", modelMtx);
            };

            LightObjectMaterials() 
            {
                name = "Light Object Material";
                ShaderInterface *light_obj_shader = new ShaderInterface("romfs:/shaders/LightObjectShader.vs", "romfs:/shaders/LightObjectShader.fs");
                materials = new ShaderMaterialInterface();
                materials->SetUpShader(name, light_obj_shader);
            };
            ~LightObjectMaterials(){};
    };

    struct LitMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                materials->SetUniformMat4F("model", modelMtx);
            };
            LitMaterial() 
            {
                name = "Lit Material";
                ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SimpleLightShader.vs", "romfs:/shaders/SimpleLightShader.fs");
                materials = new ShaderMaterialInterface();
                materials->SetUpShader(name, light_shader);
            };
            ~LitMaterial(){};
    };

    struct ImageMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                materials->SetUniformMat4F("u_ModelViewMatrix", modelMtx);
            };
            ImageMaterial() 
            {
                name = "Image Material";
                ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
                materials = new ShaderMaterialInterface();
                materials->SetUpShader(name, color_shader);
            };
            ~ImageMaterial(){};
    };



#endif // SHADERMATERIALINTERFACE_H
