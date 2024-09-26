#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>


void debugLog(const char* fmt, ...)
{
    FILE *f = fopen(LogFilePath, "a");
    fprintf(f, fmt);
    fprintf(f, "\n");
    fclose(f);
}