/***********************************************************************
                          asciiGL Toolkit
               Copyright 2021 asciiGL Toolkit contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************/

#ifndef ATK_UTILS_H
#define ATK_UTILS_H

    #include "../src/asciigl.h"
    #include <stdlib.h>

    #ifdef _WIN32
        #include <windows.h>
        #include <signal.h>
    #else
        #include <unistd.h>
    #endif


    // Wait n. milliseconds
    void atkWaitMills(unsigned int mills)
    {
        #ifdef _WIN32
            Sleep(mills);
        #else
            sleep(mills/1000);
        #endif
    }

    // Reset console, cursor and exit
    void atkEndProgram()
    {
        consoleClearScreen();
        consoleRestoreCursorPosition();
        consoleShowCursor();
        exit(0);
    }

    // Call 'ResetConsole' when CTRL-C is pressed
    void atkInitInterrupt()
    {
        signal(SIGINT, atkEndProgram);
    }

    // Init framebuffer and event listener
    void atkInit(framebuffer buffer)
    {
        aglInitContext(buffer);
        atkInitInterrupt();
    }

    // Terminates everything
    void atkEnd(framebuffer buffer)
    {
        aglEndContext(buffer);
        atkEndProgram();
    }

#endif
