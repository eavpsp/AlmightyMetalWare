#include <GameManager.h>
#include "../debug/debug.h"
#include <objMesh.h>
ResourceManager *gameResourceManager;
RenderSystem *gameRenderSystem;
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
        gameRenderSystem = gameManager->_renderSystem;
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
    //_renderSystem->render(_resourceManager->gameObjects->at(0));//
    // _renderSystem->render(_resourceManager->gameObjects->at(0));
}

void GameManager::renderLoop()
{
 
    //Run Shader updats outside of glcler calls
    _renderSystem->RenderLights();

    for (int i = 0; i < _resourceManager->gameObjects->size(); i++)
    {
       
        _renderSystem->render(_resourceManager->gameObjects->at(i));
        _resourceManager->gameObjects->at(i)->UpdateMesh();
       
    }
    //update to use resoucrce manager stored vao batches
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //ONLY DRAWS HERE
    for (int i = 0; i < _resourceManager->gameObjects->size(); i++)
    {
       
       _resourceManager->gameObjects->at(i)->DrawMesh();
        
    }

     _renderSystem->SwapBuffers();
        
    
}

bool GameManager::Running(){
     return _running;
}

