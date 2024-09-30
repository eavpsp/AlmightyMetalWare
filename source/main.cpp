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
//proper camera controls
//multiple vao buffers
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
        u32 kHeld = padGetButtons(&pad);
        if (kDown & HidNpadButton_Plus)
            break;
            gameManager->_renderSystem->mainCamera->Inputs(kHeld);
            gameManager->_renderSystem->mainCamera->updateMatrix(45.0f, 0.1f, 100.0f);
        
        }
    romfsExit();
    gameManager->destroyGameManager();
    return EXIT_SUCCESS;
}
