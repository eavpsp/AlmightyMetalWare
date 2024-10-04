#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <EngineObject.h>
#include <ShaderMaterialInterface.h>
#include "MeshData.h"
#include "GameModel.h"
#include "MeshRender.h"

/**
 * @file GameObject.h
 * @brief This class is an extension of the EngineObject class. It adds additional functionality that is specific to objects in the game world.
 * @details GameObjects can have children, a parent, and they can draw their own models. This class is used to create objects that are a bit more complex than the standard EngineObject.
 * used as a template for all objects to inherit from. Registers to script callbacks to manage update ticks and drawing calls
 */
class GameObject : public EngineObject
{
    private:
        GameObject *parent = nullptr;
        std::vector<GameObject*> children;
        void onInit() override;
        void onDestroy() override;

    public:
        //base model data
        Material *material;
        MeshRender *objectModel;
        void DrawGLTF();
        void DrawMesh();
        void DrawOBJ();
        void UpdateOBJ();
        void UpdateMesh();
        ///
        template <typename T>
        static T* InstantiateGameObject(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject")
        {
            if (!std::is_base_of<EngineObject, T>::value) {
                // Error: T is not a derived class of EngineObject
                return nullptr;
            }
                T *newObject =  new T();
                //add callback
                newObject->material = mat;
                newObject->position = _position;
                newObject->rotation = _rotation;
                newObject->scale = _scale;
                newObject->objectModel = gameModel;
                newObject->transform = glm::mat4(1.0f);

                newObject->name = _name;
               
                newObject->onInit();
                return newObject;
        }
        void UpdateGLTF();
        void AddChild(GameObject *child);
        GameObject *GetChild(int index);
        int GetChildrenCount();
        void SetParent(GameObject *i_parent);
        GameObject *GetParent();
        void RegisterObject();
        void onUpdate() override;
        void onDraw() override;
        GameObject();
        virtual ~GameObject();
        //Draw Primatives
        static GameObject* CreateSphere(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject_Sphere");
        static GameObject* CreateCube(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject_Cube");
        static GameObject* CreateCylinder(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject_Cylinder");
        static GameObject* CreateCone(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject_Cone");
        static GameObject* CreateTorus(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, MeshRender *gameModel, std::string _name = "GameObject_Torus");

    };






#endif // GAMEOBJECT_H
