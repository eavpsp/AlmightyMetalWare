#include <GameManager.h>
#include "../debug/debug.h"

GameManager::GameManager(bool running) : _running{running}, _renderSystem{&RenderSystem::getRenderSystem()}, _resourceManager{&ResourceManager::getResourceManager()} {}
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
        gameManager->_renderSystem->initRenderSystem(*(gameManager->_resourceManager));//pass in resource manager
        gameManager->_resourceManager->initResourceManager();
        debugLog("Made GameManager!");
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
    _renderSystem->render(_resourceManager->gameObjects->at(0));
   // _renderSystem->render(_resourceManager->getVertexArray()->at(0));
}

bool GameManager::Running(){
     return _running;
}

