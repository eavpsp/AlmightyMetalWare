#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <EngineObject.h>
#include <ShaderMaterialInterface.h>
#include "MeshData.h"
#include "GameModel.h"
/**
 * @file GameObject.h
 * @brief This class is an extension of the EngineObject class. It adds additional functionality that is specific to objects in the game world.
 * @details GameObjects can have children, a parent, and they can draw their own models. This class is used to create objects that are a bit more complex than the standard EngineObject.
 */
class GameObject : public EngineObject
{
    private:
        GameObject *parent = nullptr;
        std::vector<GameObject*> children;

    public:
        //base model data
        Material *material;
        GameModel *objectModel;
        ///
        void DrawObjectModel();
        void AddChild(GameObject *child);
        GameObject *GetChild(int index);
        int GetChildrenCount();
        void SetParent(GameObject *i_parent);
        GameObject *GetParent();
         void onUpdate();
         void onDraw();
         void onInit();
         void onDestroy();
        GameObject(Material *i_mat, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, GameModel *gameModel);
        virtual ~GameObject();
    };





#endif // GAMEOBJECT_H
