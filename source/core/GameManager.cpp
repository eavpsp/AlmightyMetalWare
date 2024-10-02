#include <GameManager.h>
#include "../debug/debug.h"
#include <objMesh.h>
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
    //_renderSystem->render(_resourceManager->gameObjects->at(0));//
    // _renderSystem->render(_resourceManager->gameObjects->at(0));
}
bool didRun;
ObjMesh *objMesh;
Material *litMat;
glm::mat4 transform = glm::mat4(1.0f);
glm::vec3 position = glm::vec3(5.0f, 0.0f, 0.0f);
void GameManager::renderLoop()
{
    if(!didRun)
    {
        MeshCreateInfo *info = new MeshCreateInfo(); //create MeshCreateInfo"romfs:/cube0001.obj"
        info->filename = "romfs:/owl/owl.obj";
        info->preTransform = transform;
        objMesh = new ObjMesh(info);
        litMat = new Material();
        litMat->shader = new ShaderMaterialInterface();
        litMat->shader->SetUpShader("Cube Shader", new ShaderInterface("romfs:/shaders/OBJ_Shader.vs", "romfs:/shaders/OBJ_Shader.fs"));
        transform = glm::translate(transform, position);
        didRun = true;
    }
    //Run Shader updats outside of glcler calls
    
    objMesh->UpdateMesh(litMat, transform, glm::quat(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f), _renderSystem->mainCamera);

    //update to use resoucrce manager stored vao batches
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < _resourceManager->gameObjects->size(); i++)
    {
        /* code */
        _renderSystem->render(_resourceManager->gameObjects->at(i));
        //_renderSystem->RenderLights();
    }
    objMesh->Draw();
     _renderSystem->SwapBuffers();
        
    
}

bool GameManager::Running(){
     return _running;
}

