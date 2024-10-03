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
        ShaderMaterialInterface *shader;
    };

    struct GameFontMaterial : public Material
    {
        bool operator==(GameFontMaterial other)
        {
            return fontColor == other.fontColor;
        }
        glm::vec4 fontColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        void UpdateProjectionShader(glm::mat4 projMtx)
        {
            shader->SetUniform4F("aColor", fontColor.x, fontColor.y, fontColor.z, fontColor.w);
            shader->SetUniformMat4F("projection", projMtx);
        };

        GameFontMaterial() 
        {
            name = "Game Font Material";
            ShaderInterface *font_shader = new ShaderInterface("romfs:/gameFonts/GameFontShader.vs", "romfs:/gameFonts/GameFontShader.fs");
            shader = new ShaderMaterialInterface();
            shader->SetUpShader(name, font_shader);
        };
        ~GameFontMaterial(){};
    };
    //struct ColorMaterial : public Material; //Create color only mats

    struct LightObjectMaterials : public Material //TEMPORARY
    {
        public :
            glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("model", modelMtx);
            };

            LightObjectMaterials() 
            {
                name = "Light Object Material";
                ShaderInterface *light_obj_shader = new ShaderInterface("romfs:/shaders/LightObjectShader.vs", "romfs:/shaders/LightObjectShader.fs");
                shader = new ShaderMaterialInterface();
                shader->SetUpShader(name, light_obj_shader);
            };
            ~LightObjectMaterials(){};
    };

    struct LitMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("model", modelMtx);
            };
            LitMaterial() 
            {
                name = "Lit Material";
                ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SimpleLightShader.vs", "romfs:/shaders/SimpleLightShader.fs");
                shader = new ShaderMaterialInterface();
                shader->SetUpShader(name, light_shader);
            };
            ~LitMaterial(){};
    };
 
    struct DirectionalLightMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("model", modelMtx);
            };
            void SetLightDirection(glm::vec3 ligtDir)
            {
                shader->SetUniform3F("u_LightDir", ligtDir.x, ligtDir.y, ligtDir.z);
            }
            DirectionalLightMaterial() 
            {
                name = "Directional Light Material";
                ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/DirectionalLight.vs", "romfs:/shaders/DirectionalLight.fs");
                shader = new ShaderMaterialInterface();
                shader->SetUpShader(name, light_shader);
            };
            ~DirectionalLightMaterial(){};
    };
    struct PointLightMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("model", modelMtx);
            };
            //color function
            void SetLightColor(glm::vec4 lightColor)
            {
                shader->SetUniform4F("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
            }
            //light controls
            void SetLightData(float a, float b)
            {
                shader->SetUniform1f("aVal", a);
                shader->SetUniform1f("bVal", b);
            }
            PointLightMaterial() 
            {
                name = "Point Light Material";
                ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/PointLight.vs", "romfs:/shaders/PointLight.fs");
                shader = new ShaderMaterialInterface();
                shader->SetUpShader(name, light_shader);
            };
            ~PointLightMaterial(){};
    };
    struct SpotLightMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("model", modelMtx);
            };
            //color function
            void SetLightColor(glm::vec4 lightColor)
            {
                shader->SetUniform4F("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
            }
            //light controls
            void SetLightDirection(glm::vec3 ligtDir)
            {
                shader->SetUniform3F("u_LightDir", ligtDir.x, ligtDir.y, ligtDir.z);
            }
            void SetConeSize(float inner, float outer)
            {
                shader->SetUniform1f("innerCone", inner);
                shader->SetUniform1f("outerCone", outer);

            }
            SpotLightMaterial()
            {
                  name = "Spot Light Material";
                  ShaderInterface *light_shader = new ShaderInterface("romfs:/shaders/SpotLight.vs", "romfs:/shaders/SpotLight.fs");
                  shader = new ShaderMaterialInterface();
                  shader->SetUpShader(name, light_shader);  
            };
            ~SpotLightMaterial(){};
    };
    
    struct ImageMaterial : public Material
    {
        public:
            void UpdateModelShader(glm::mat4 modelMtx)
            {
                shader->SetUniformMat4F("u_ModelViewMatrix", modelMtx);
            };
            ImageMaterial() 
            {
                name = "Image Material";
                ShaderInterface *color_shader = new ShaderInterface("romfs:/shaders/ColorShader.vs", "romfs:/shaders/FragmentShader.fs");
                shader = new ShaderMaterialInterface();
                shader->SetUpShader(name, color_shader);
            };
            ~ImageMaterial(){};
    };



#endif // SHADERMATERIALINTERFACE_H
