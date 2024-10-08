#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>
#include "debug/debug.h"
#include <json.hpp>  
#include <ScriptCallbacks.h>
#include <EnginePhysics.h>


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
component script
has parent gameobject
get component
add component
gameobject child positions and a matrix data
on init callback //called before update in main loop, ran once per game object
-Text only menus for now-
selction options
change text color when hilighted
--
-Demo Levels
Plane and Sphere

UI overlays
Textures and font data
*/



/*
Todo:
DONE
Finish Lights - Done
Fix Camera - Done
Fix Texture Loading - Done
UI - Font - Done
Primitive Shape Library - Done
Static Objects - Done
Skybox - Done (Breaks Text rendering)
Colors - Red, Green, Blue, White, Yellow, Black, Orange, Purple - Done
Physics system - bullet engine integration - Done


WIP
UI - Icons - WIP
Input system - Detailed
Animation system - Done  Animation Controller
    Loads Multiple OBJ files and stores them as keyframes
    Dynamic VBO gets updated based on current frame and animation


NS
Particle system (Dynamic Batched Software Particles)- 
    each obj will hold vertex data
    push vertex data to one buffer
    update each individual particle data per frame
Audio system (MP3, OGG Playback)- SDL Audio
Video system (MP4 Playback)- MPV

Batch Render Lights -
Textures - Normals, Spec, Roughness, AA, View Culling -
Framebuffers -
Post Processing -


FUTURE
Skeletal Animation -

//THREADS
GAME -> Game Manager , Engine Objects, Physics, Input
Render -> Render System, Draw Calls, Batchinng
*/

EngineCallBacks *engineCallBacks;
std::vector<GameObject *> *GameObjects;
std::vector<EngineObject *> *GraphicsObjects;
std::vector<ViewCamera *> *CameraObjects;
GameManager *gameManager;
EnginePhysics *enginePhysics;


void initSystem()
{   
    romfsInit();
    debugLogInit();
    debugLog("romFS Init");
    debugLog("System Starting...");
    enginePhysics = new EnginePhysics();
    debugLog("Engine Physics Init");
    //init callbacks 
    GameObjects = new std::vector<GameObject *>();
    GraphicsObjects = new std::vector<EngineObject *>();
    CameraObjects = new std::vector<ViewCamera *>();
    engineCallBacks = new EngineCallBacks();
    debugLog("Engine Callbacks Init");

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
    //while()
    while (gameManager->Running())
    {
        //Run
        enginePhysics->DoPhysicsSimulation();
    
        gameManager->runGameLoop();
        gameManager->renderLoop();
        //Run Update Callbacks
        engineCallBacks->RunUpdateCallbacks();
        
        // Get and process input
        padUpdate(&pad);
        u32 kDown = padGetButtonsDown(&pad);
        u32 kHeld = padGetButtons(&pad);
        gameManager->_renderSystem->mainCamera->Inputs(kHeld);
        if (kDown & HidNpadButton_Plus)
            break;

    }
    //while(!gameManager->Running() && gameManger->GamePaused() or menu)
    //alternate loop to pause game
    debugLog("Game Stopped....");
    romfsExit();
    gameManager->destroyGameManager();
}

int main(int argc, char* argv[])
{
    initSystem();
   
    EngineMain();
    //need a backup 
    debugLog("Exiting....");
    appletExit();
    return EXIT_SUCCESS;
    
}