#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <RenderSystem.h>
#include <time.h>

class GameManager
{
    private:
        bool _running;
        GameManager(bool running);
        ~GameManager();
    public:
 


    void renderLoop();
    void runGameLoop();
    void SceneInit();
    void GameLoop();
    bool Running();
    RenderSystem *_renderSystem;
    ResourceManager *_resourceManager;
    static GameManager& getGameManager();
    static void destroyGameManager();
};


#endif