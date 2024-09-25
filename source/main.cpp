#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <GameManager.h>



//-----------------------------------------------------------------------------
// nxlink support
//-----------------------------------------------------------------------------

#ifndef ENABLE_NXLINK
#define TRACE(fmt,...) ((void)0)
#else
#include <unistd.h>
#define TRACE(fmt,...) printf("%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__)

static int s_nxlinkSock = -1;

static void initNxLink()
{
    if (R_FAILED(socketInitializeDefault()))
        return;

    s_nxlinkSock = nxlinkStdio();
    if (s_nxlinkSock >= 0)
        TRACE("printf output now goes to nxlink server");
    else
        socketExit();
}

static void deinitNxLink()
{
    if (s_nxlinkSock >= 0)
    {
        close(s_nxlinkSock);
        socketExit();
        s_nxlinkSock = -1;
    }
}

extern "C" void userAppInit()
{
    initNxLink();
}

extern "C" void userAppExit()
{
    deinitNxLink();
}

#endif

int main(int argc, char* argv[])
{
    romfsInit();
   
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
