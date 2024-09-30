#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>
#include "debug/debug.h"
#include <json.hpp>  

/*
///TODO
Create Debug Logger (Done)
Batch Rendering (Needs system but understand how to do it)
Create Mesh System using blender + unity or just blender(Done)
Add nullptr checks to all funcs
//setup threads for game , physics, audio, input, and render
//metadata for materials and other game objects ofc
//font system
//texture atlas
//shaders to manage batching
//set max buffer size
*/
//
int main(int argc, char* argv[])
{
    romfsInit();
    debugLogInit();
    //init GM
    GameManager *gameManager = &GameManager::getGameManager();

  
   
    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);

  
    // Main game loop
    //while(appletMainLoop())
    while (gameManager->Running())
    {
        //Run
       gameManager->runGameLoop();
        // Get and process input
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus)
            break;
        if(kDown & HidNpadButton_Left)
        {
            gameManager->_renderSystem->mainCamera->position = gameManager->_renderSystem->mainCamera->position + glm::vec3(10.0f,0.0f,0.0f);
        }
        if(kDown & HidNpadButton_Right)
        {
            gameManager->_renderSystem->mainCamera->position = gameManager->_renderSystem->mainCamera->position + glm::vec3(-10.0f,0.0f,0.0f);
        }
        if(kDown & HidNpadButton_Up)
        {
            gameManager->_renderSystem->mainCamera->position = gameManager->_renderSystem->mainCamera->position + glm::vec3(0.0f,10.0f,0.0f);
        }
        if(kDown & HidNpadButton_Down)
        {
            gameManager->_renderSystem->mainCamera->position = gameManager->_renderSystem->mainCamera->position + glm::vec3(0.0f,-10.0f,0.0f);
        }
        
    }
    romfsExit();
    gameManager->destroyGameManager();
    return EXIT_SUCCESS;
}
