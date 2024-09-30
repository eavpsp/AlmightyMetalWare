#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <EngineObject.h>
#include <ShaderMaterialInterface.h>
#include "MeshData.h"
#include "GameModel.h"
class GameObject : public EngineObject
{
    
    public:
        //base model data
        ShaderMaterialInterface *_shaderInterface;
        GameModel *objectModel;
        GameObject(ShaderMaterialInterface *i_shaderInterface, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, GameModel &gameModel);
        ~GameObject();
    };





#endif // GAMEOBJECT_H
