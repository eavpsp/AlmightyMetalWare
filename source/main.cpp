#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>
#include "debug/debug.h"
#include <json.hpp>  
#include <ScriptCallbacks.h>


/*
/Things
Create Debug Logger (Done)
Batch Rendering (Needs system but understand how to do it)
Create Mesh System using blender + unity or just blender(Done)
Add nullptr checks to all funcs
setup threads for game , physics, audio, input, and render (maybe)
metadata for materials and other game objects ofc
shaders to manage batching
set max buffer size
proper camera controls
use arrays for static objects
custom z-lib compression for game data
create scene object that stores level metadata bg color and skybox textures
*/



/*
Todo:
Finish Lights - Done
Fix Camera - Done
Fix Texture Loading - Done
UI - Font - Done
UI - Icons - WIP
Primitive Shape Library - Done
Batch Render Lights 
Static Objects - Done
Textures - Normals, Spec, Roughness, AA
Dynamic Objects -> Animation System
Skybox - Done
Colors - Red, Green, Blue, White, Yellow, Black, Orange, Purple
Animation system - Animation Controller
Physics system - bullet or homemade
Particle system - 
Audio system
Input system - Detailed
Video system
Framebuffers
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
