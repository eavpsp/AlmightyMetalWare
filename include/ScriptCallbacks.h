#ifndef SCRIPTCALLBACKS_H
#define SCRIPTCALLBACKS_H

#include <vector>
#include <EngineObject.h>
#include <algorithm>

class EngineCallBacks
{
    public:
        EngineCallBacks(){};
        ~EngineCallBacks(){};
        std::vector<EngineObject *> *GameObjects;
        
        
       
};

class GraphicsCallbacks
{
    public:
            GraphicsCallbacks(){};
            ~GraphicsCallbacks(){};
            std::vector<EngineObject *> GameObjects;
            
            
                void RegisterObjectCallback(EngineObject *callback) 
                {
                    GameObjects.push_back(callback);
                };
                void UnregisterObjectCallback(EngineObject *callback) 
                {
                    auto it = std::remove(GameObjects.begin(), GameObjects.end(), callback);
                    if (it != GameObjects.end())
                        GameObjects.erase(it, GameObjects.end());
                };
                void RunCallbacks(bool isRunning) 
                {
                    if (!isRunning) 
                    {
                        for (auto& obj : GameObjects)
                        {
                            obj->onDraw();
                        }
                    }
                    
                };
};
class PhysicsCallbacks;
class AudioCallbacks;
class InputCallbacks;

#endif // SCRIPTCALLBACKS_H
