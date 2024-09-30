#include "GameObject.h"

GameObject::GameObject(ShaderMaterialInterface *i_shaderInterface, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, GameModel *gameModel)
{
    _shaderInterface = i_shaderInterface;
    position = _position;
    rotation = _rotation;
    scale = _scale;
    objectModel = gameModel;
    //should init transform as well
    
}
GameObject::~GameObject()
{
   delete objectModel;
   delete _shaderInterface;

}