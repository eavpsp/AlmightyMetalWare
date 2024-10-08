#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <EngineObject.h>
#include <ShaderMaterialInterface.h>
#include "MeshData.h"
#include "GameModel.h"
#include "MeshRender.h"


/**
 * @class GameComponent
 * @brief This is the base class for all game components.
 * @details This class is the base class for all game components. It provides a common interface for all components to inherit from and implement. The interface includes a method to update the component and a method to set the parent object of the component.
 */
class GameComponent
{
    public:
        GameObject* parentObject;
        virtual void OnUpdate() = 0;
        void SetParentObject(GameObject* obj) { parentObject = obj; }
        bool isActive = true;
        virtual void ComponentAddedCallback() = 0;
        GameComponent(){};
        virtual ~GameComponent() {}
};

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
        bool renderMesh = true;
        bool hasAnimator = false;
        bool hasParticleFX = false;

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
                newObject->position = _position;//flipped y to work with BulletPhysics and OpenGL
                newObject->rotation = _rotation;
                newObject->scale = glm::vec3(_scale.x, -_scale.y, _scale.z);//flipped y to work with BulletPhysics and OpenGL
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
        std::vector<GameComponent *> components;
        void AddComponent(GameComponent *component)
        {
            components.push_back(component);
            component->SetParentObject(this);
            component->ComponentAddedCallback();
        };
        void UpdateComponents()
        {
            for (int i = 0; i < components.size(); i++)
            {
                components.at(i)->OnUpdate();
            }
        }
        
        void RemoveComponent(GameComponent *component)
        {
            for (int i = 0; i < components.size(); i++)
            {
                if (components[i] == component)
                {
                    components.erase(components.begin() + i);
                    break;
                }
            }
        };
        template<typename T>
        T *GetComponent()
        {
            for (int i = 0; i < components.size(); i++)
            {
                if (dynamic_cast<T*>(components[i]))
                {
                    return dynamic_cast<T*>(components[i]);
                }
            }
            return nullptr;
        }
        
        GameObject();
        virtual ~GameObject();
        //Draw Primatives
        static GameObject* CreateSphere(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Sphere");
        static GameObject* CreateCube(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Cube");
        static GameObject* CreateCylinder(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Cylinder");
        static GameObject* CreateCone(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Cone");
        static GameObject* CreateTorus(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Torus");
        static GameObject* CreateCapsule(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale,  std::string _name = "GameObject_Capsule");

    };

 




#endif // GAMEOBJECT_H
