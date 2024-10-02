#include <GameManager.h>
#include "../debug/debug.h"
ResourceManager *gameResourceManager;
Thread GameThread, RenderThread, AudioThread;

GameManager::GameManager(bool running) : _running{running}, _renderSystem{&RenderSystem::getRenderSystem()}, _resourceManager{&ResourceManager::getResourceManager()} 
{
    
}

GameManager::~GameManager()
{
    _resourceManager->destroyResourceManager();

    _renderSystem->destroyRenderSystem();
}
GameManager& GameManager::getGameManager()
{
    static GameManager *gameManager = nullptr;
    if(gameManager == nullptr)
    {
        gameManager = new GameManager(true);
        if (!gameManager->_renderSystem->initEgl(nwindowGetDefault()))
        {
            debugLog("\x1b[16;25HError Creating Window!");
        }
        gladLoadGL();
        gameResourceManager = gameManager->_resourceManager;
        gameManager->_renderSystem->initRenderSystem(*(gameManager->_resourceManager));//pass in resource manager
        gameManager->_resourceManager->initResourceManager();
      
        debugLog("Made Game Manager!");
    }
    return *gameManager;
}

void GameManager::destroyGameManager()
{
        GameManager *gameManager = &getGameManager();

        if(gameManager != nullptr)
        {
            debugLog("\x1b[16;20HDestroyed GameManager!");
            delete gameManager;

        }
    }

void GameManager::runGameLoop()
{
    
}

void GameManager::renderLoop()
{
    //update to use resoucrce manager stored vao batches
    while(_running)
    {
            for (int i = 0; i < _resourceManager->gameObjects->size(); i++)
        {
            /* code */
            _renderSystem->render(_resourceManager->gameObjects->at(i));
        }
    }
     
        
    
}

bool GameManager::Running(){
     return _running;
}

