#include <GameManager.h>


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
           printf("\x1b[16;25HError Creating Window!");
       }
        gladLoadGL();
        gameManager->_resourceManager->initResourceManager();
        gameManager->_renderSystem->initRenderSystem();
             printf("\x1b[16;25HMade GameManager!");
    }
    return *gameManager;
}

void GameManager::destroyGameManager()
{
        GameManager *gameManager = &getGameManager();

        if(gameManager != nullptr)
        {
            printf("\x1b[16;20HDestroyed GameManager!");
            delete gameManager;

        }
    }

void GameManager::runGameLoop()
{
    _renderSystem->render(_resourceManager->getVertexBufferArray()->at(0));
}

bool GameManager::Running(){
     return _running;
}

