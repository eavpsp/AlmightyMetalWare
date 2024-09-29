#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>
#include "debug/debug.h"


/*
///TODO
Create Debug Logger (Done)
Batch Rendering
Create Mesh System using blender + unity or just blender
Add nullptr checks to all funcs
//setup threads for game , physics, audio, input, and render
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
        
    }
    romfsExit();
    gameManager->destroyGameManager();
    return EXIT_SUCCESS;
}
