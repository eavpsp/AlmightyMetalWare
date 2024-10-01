#ifndef SCRIPTCALLBACKS_H
#define SCRIPTCALLBACKS_H

#include <vector>
#include <algorithm>
#include <ShaderMaterialInterface.h>
#include <GameObject.h>
#include "../debug/debug.h"
extern std::vector<GameObject *> *GameObjects;
extern std::vector<EngineObject *> *GraphicsObjects;
class EngineCallBacks
{
    public:
        EngineCallBacks()
        {};
        ~EngineCallBacks(){};
        
        
        static GameObject *InstantiateGameObject(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, GameModel *gameModel);
 
        void RunGraphicsCallbacks(bool isRunning) 
        {
            if (!isRunning) 
            {
                for (auto& obj : *GraphicsObjects)
                {
                    obj->onDraw();
                }
            }
            
        };
       void RunUpdateCallbacks(bool isRunning) 
        {
            if (isRunning) 
            {
                for(int i = 0; i < GameObjects->size(); i++)
                {
                    GameObject* obj = dynamic_cast<GameObject*>(GameObjects->at(i));
                    if (obj != nullptr) 
                    {
                        obj->onUpdate(); // This will call TestObj::onUpdate() if obj is a TestObj
                    }
                   
                }
            }
            
        };
};


#endif // SCRIPTCALLBACKS_H
