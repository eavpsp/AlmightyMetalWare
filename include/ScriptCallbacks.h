#ifndef SCRIPTCALLBACKS_H
#define SCRIPTCALLBACKS_H
constexpr int TARGET_FPS = 60;
constexpr double UPDATE_TICK_DELAY = 1.0 / TARGET_FPS;

#include <vector>
#include <algorithm>
#include <ShaderMaterialInterface.h>
#include <GameObject.h>
#include "../debug/debug.h"

extern std::vector<GameObject *> *GameObjects;
extern std::vector<EngineObject *> *GraphicsObjects;
extern std::vector<ViewCamera *> *CameraObjects;

class EngineCallBacks
{
    private:
    double get_detla_time(){
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
        lastTime = currentTime;
        return deltaTime;
    }
    float updateTicks = 0;
  
    float _deltaTime;
    public:
        float interpolatedTickTime = (float)(updateTicks/ UPDATE_TICK_DELAY);
        float GetInterpolatedTickTime()
        {
            return interpolatedTickTime;
        }
      
        EngineCallBacks()
        {
           _deltaTime = UPDATE_TICK_DELAY;
          
        };
        ~EngineCallBacks(){};
        
        
        static GameObject *InstantiateGameObject(Material *mat, glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, GameModel *gameModel);
 
        void RunGraphicsCallbacks() 
        {
           
                for (auto& obj : *GraphicsObjects)
                {
                    obj->onDraw();
                }
            
            
        };
       void RunUpdateCallbacks() 
        {
            updateTicks += _deltaTime;
           

           if(updateTicks >= UPDATE_TICK_DELAY)
           {
                updateTicks -= UPDATE_TICK_DELAY;
                    RunUpdateCameraCallbacks();
               
                    for(int i = 0; i < GameObjects->size(); i++)
                    {
                        GameObject* obj = dynamic_cast<GameObject*>(GameObjects->at(i));
                        if (obj != nullptr) 
                        {
                            obj->onUpdate(); // This will call TestObj::onUpdate() if obj is a TestObj
                        }
                    
                    }
                    RunGraphicsCallbacks();
            }
               
        };
       
         void RunUpdateCameraCallbacks() 
        {
            
                for(int i = 0; i < CameraObjects->size(); i++)
                {
                    if (CameraObjects->at(i) != nullptr) 
                    {
                        CameraObjects->at(i)->onUpdate();
                    }
                   
                }
            
            
        };
};


#endif // SCRIPTCALLBACKS_H
