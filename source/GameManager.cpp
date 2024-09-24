#include <GameManager.h>


GameManager::~GameManager()
{
    _renderSystem->destroyRenderSystem();
}

GameManager& GameManager::getGameManager()
{
    static GameManager *gameManager = nullptr;
        

    if(gameManager == nullptr){

        gameManager = new GameManager(true);
     //  if (!gameManager->_renderSystem->initEgl(nwindowGetDefault()))
           // printf("\x1b[16;25HError Creating Window!");
        
        // Load OpenGL routines using glad
       // gladLoadGL();
        printf("\x1b[16;25HMade GameManager!");

    }

    return *gameManager;
}

void GameManager::destroyGameManager(){
        GameManager *gameManager = &getGameManager();

        if(gameManager != nullptr){
            printf("\x1b[16;20HDestroyed GameManager!");
            delete gameManager;

        }
    }

void GameManager::runGameLoop()
{
            
    //_renderSystem->render();
}

bool GameManager::Running(){
     return _running;
}

