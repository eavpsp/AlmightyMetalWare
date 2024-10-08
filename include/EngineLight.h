#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "ShaderMaterialInterface.h"
//outline the base light class then all the other light variants
//will have an engine object parent
//will have a shader material
//used to render light objects

class EngineLight
{
    private:
        std::string name;

    public:
        glm::vec3 position, scale;
        glm::quat rotation;
        glm::mat4 transform;
        Material *light_Material;
        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);//Define colors and shapes in seperate script

        void SetLightColor(glm::vec4 lightColor)
        {
            this->lightColor = lightColor;
            PointLightMaterial *pointLightMaterial = (PointLightMaterial *)this->light_Material;
            pointLightMaterial->SetLightColor(lightColor);
        };
        std::string GetName()
        {
            return name;
        }
        EngineLight()
        {
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
            glm::quat rotation = glm::quat();
            transform = glm::mat4(1.0f);
            transform = glm::translate(transform, position);
            transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::scale(transform, scale);
            name = "Light Object";
            light_Material = new PointLightMaterial();
            SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//default light color

        };
        virtual ~EngineLight(){};
};
class PointLight : public EngineLight
{
    private:
        float a, b;
    public:
        void UpdateLightIntensity(float a, float b)
        {
            this->a = a;
            this->b = b;
            PointLightMaterial *pointLightMaterial = (PointLightMaterial *)this->light_Material;
            pointLightMaterial->SetLightData(a, b);
        };
       
        PointLight()
        {
            light_Material = new PointLightMaterial();
            UpdateLightIntensity(3.0f,0.7f);
        };
        ~PointLight(){};

};

class SpotLight : public EngineLight
{
    private:
        float innerConeAngle, outerConeAngle;
        glm::vec3 lightDir;
    public:
        void UpdateLightCone(float innerConeAngle, float outerConeAngle)
        {
            this->innerConeAngle = innerConeAngle;
            this->outerConeAngle = outerConeAngle;
            SpotLightMaterial *spotLightMaterial = (SpotLightMaterial *)this->light_Material;
            spotLightMaterial->SetConeSize(innerConeAngle, outerConeAngle);
        };

       void SetLightDirection(glm::vec3 lightDir)
       {
           this->lightDir = lightDir;
           SpotLightMaterial *spotLightMaterial = (SpotLightMaterial *)this->light_Material;
           spotLightMaterial->SetLightDirection(lightDir);
       }
        SpotLight()
        {
            light_Material = new SpotLightMaterial();
            UpdateLightCone(0.90f, 0.95f);
            SetLightDirection(glm::vec3(0.0f, -1.0f, 0.0f));
        };
        ~SpotLight(){};
};

class DirectionalLight : public EngineLight
{   
    private:
        glm::vec3 lightDir;
    public:

        void SetLightDirection(glm::vec3 lightDir)
        {
            this->lightDir = lightDir;
            DirectionalLightMaterial *directionalLightMaterial = (DirectionalLightMaterial *)this->light_Material;
            directionalLightMaterial->SetLightDirection(lightDir);
        };
        DirectionalLight()
        {
            light_Material = new DirectionalLightMaterial();
            SetLightDirection(glm::vec3(1.0f, 1.0f, 0.0f));
        };
        ~DirectionalLight(){};
};

#endif // ENGINE_LIGHT_H
