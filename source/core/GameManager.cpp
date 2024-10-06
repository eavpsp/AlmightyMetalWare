#include <GameManager.h>
#include "../debug/debug.h"
#include <objMesh.h>
#include <UserInterface.h>
ResourceManager *gameResourceManager;
RenderSystem *gameRenderSystem;
Thread GameThread, RenderThread, AudioThread;

GameManager::GameManager(bool running) : _running{running}, _renderSystem{&RenderSystem::getRenderSystem()}, _resourceManager{&ResourceManager::getResourceManager()} 
{}

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
    //_renderSystem->RenderLights();

    //update to use resoucrce manager stored vao batches
    glClearColor(_resourceManager->_gameScene->sceneColor.x, _resourceManager->_gameScene->sceneColor.y, _resourceManager->_gameScene->sceneColor.z, _resourceManager->_gameScene->sceneColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     //UI SCOPE
    {
        //Negative Bullet = Postive OpenGL in Y direction
        //move in postive open gl to move in negative bullet
        _resourceManager->_gameFont->RenderTextFormat("obj 1 pos: %f %f %f", 
        glm::vec2(0.0f, 0.0f), 1.0f, glm::vec3(1,1,1),
         _resourceManager->gameObjects->at(0)->position.x, -_resourceManager->gameObjects->at(0)->position.y, _resourceManager->gameObjects->at(0)->position.z);
       
        _resourceManager->_gameFont->RenderTextFormat("obj 2 pos: %f %f %f", 
        glm::vec2(0.0f, 50.0f), 1.0f, glm::vec3(1,1,1),
        _resourceManager->gameObjects->at(1)->position.x, -_resourceManager->gameObjects->at(1)->position.y, _resourceManager->gameObjects->at(1)->position.z);
       
        _resourceManager->_gameFont->RenderTextFormat("cam pos: %f %f %f", 
        glm::vec2(0.0f, 100.0f), 1.0f, glm::vec3(1,1,1),
         _renderSystem->mainCamera->position.x, _renderSystem->mainCamera->position.y, _renderSystem->mainCamera->position.z);

    }
    //ONLY DRAWS HERE
    for (int i = 0; i < _resourceManager->gameObjects->size(); i++)
    {
        _resourceManager->gameObjects->at(i)->UpdateMesh();
        //skybox
       
    }
   // _resourceManager->_gameScene->skybox->RenderSkybox();
        
     _renderSystem->SwapBuffers();
        
    
}

bool GameManager::Running(){
     return _running;
}

