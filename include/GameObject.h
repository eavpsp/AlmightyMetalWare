#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <EngineObject.h>
#include<ShaderMaterialInterface.h>
class GameObject : public EngineObject
{
    
    public:
        ShaderMaterialInterface *_shaderInterface;
        GameObject(ShaderMaterialInterface *i_shaderInterface, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
        ~GameObject();
    };





#endif // GAMEOBJECT_H
