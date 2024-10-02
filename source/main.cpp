#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>
#include "debug/debug.h"
#include <json.hpp>  
#include <ScriptCallbacks.h>
#define THREAD_STACK_SIZE_Min 0x1000
#define THREAD_STACK_SIZE_Max 0x80000
#define THREAD_STACK_SIZE 0x4000
#define THREAD_STACK_SIZE_FOUR 0x1000

/*
///Things
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
//use arrays for static objects
custom z-lib compression for game data
*/
//////

//////
/*
Todo:
Finish Lights
Batch Render Lights, Static Objects, Textures, Dynamic Objects, Skybox, Colors 
Animation system
Add Skybox
UI - Font
UI - Icons
Physics system
Audio system
Input system - Detailed
Video system
Post Processing

//THREADS
GAME -> Game Manager , Engine Objects, Physics, Input
Render -> Render System, Draw Calls, Batchinng
*/

EngineCallBacks *engineCallBacks;
std::vector<GameObject *> *GameObjects;
std::vector<EngineObject *> *GraphicsObjects;
GameManager *gameManager;

void initSystem()
{
    debugLog("System Starting...");

    romfsInit();
    debugLogInit();
    //init callbacks 
    GameObjects = new std::vector<GameObject *>();
    GraphicsObjects = new std::vector<EngineObject *>();
    engineCallBacks = new EngineCallBacks();
    
}

void EngineMain()
{
    debugLog("Engine Starting...");
      //init GM
    gameManager = &GameManager::getGameManager();
    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);
    debugLog("Objects Alive: %d", GameObjects->size());

    // Main game loop
    //while(appletMainLoop())
    while (gameManager->Running())
    {
        //Run
    
        gameManager->runGameLoop();
        gameManager->renderLoop();
        //Run Update Callbacks
        engineCallBacks->RunUpdateCallbacks(gameManager->Running());
        // Get and process input
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        gameManager->_renderSystem->mainCamera->Inputs(kHeld);
        gameManager->_renderSystem->mainCamera->updateMatrix(45.0f, 0.1f, 100.0f);
        if (kDown & HidNpadButton_Plus)
            break;

    }
    debugLog("Game Stopped....");

    romfsExit();
    gameManager->destroyGameManager();
}
int main(int argc, char* argv[])
{
    initSystem();
    EngineMain();
    appletExit();
    debugLog("Exiting....");
    return EXIT_SUCCESS;
    
}
