#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <cstdarg>
char* LogFilePath = "sdmc:/debug.log";

FILE *debugLogFile = nullptr;

void debugLogInit()
{
    debugLogFile = fopen(LogFilePath, "a");
    if (!debugLogFile)
    {
        printf("Failed to open log file at %s\n", LogFilePath);
    }
}

void debugLog(char* fmt, ...)
{
    if (!debugLogFile)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    vfprintf(debugLogFile, fmt, args);
    va_end(args);
    fprintf(debugLogFile, "\n");
    fflush(debugLogFile);
}

void debugLogCleanup()
{
    if (debugLogFile)
    {
        fclose(debugLogFile);
        debugLogFile = nullptr;
    }
}
