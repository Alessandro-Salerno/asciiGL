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
        #define _POSIX_SOURCE
        #include <unistd.h>
        #include <sys/ioctl.h>
    #endif


    // Wait n. milliseconds
    void atkWaitMills(unsigned int mills)
    {
        #ifdef _WIN32
            Sleep(mills);
        #else
            usleep(mills * 1000);
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

    // Returns the width of the console
    unsigned int atkGetConsoleWidth()
    {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        #else
            struct winsize size;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
            return size.ws_col;
        #endif
    }

    // Returns the height of the console
    unsigned int atkGetConsoleHeight()
    {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            
            return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        #else
            struct winsize size;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
            return size.ws_row;
        #endif
    }

    // Creates and returns a framebuffer with the same size as the window
    framebuffer atkSetup()
    {
        unsigned int width  = atkGetConsoleWidth(),
                     height = atkGetConsoleHeight() - 1;

        return Framebuffer(width, height);
    }

    // Init framebuffer and event listener
    void atkInit(framebuffer buffer)
    {
        aglInitContext(buffer);
        atkInitInterrupt();
    }

    // automatically resizes the framebuffer if the window has been resized
    void atkAutoResize(framebuffer buffer)
    {
        unsigned int width  = atkGetConsoleWidth(),
                     height = atkGetConsoleHeight() - 1;

        if (buffer->width != width | buffer->height != height)
        {
            aglResizeFramebuffer(buffer, width, height);
            consoleClearScreen();
            aglDrawFramebuffer(buffer);
        }
    }

    // Clears the frame and color buffers
    void atkClear(framebuffer buffer, pixel chr, color_t fgcolor, color_t bgcolor)
    {
        for (coord y = 0; y < buffer->height; y++)
            for (coord x = 0; x < buffer->width; x++)
                aglSetCell(buffer, x, y, chr, fgcolor, bgcolor);
    }

    // Terminates everything
    void atkEnd(framebuffer buffer)
    {
        aglEndContext(buffer);
        atkEndProgram();
    }

#endif
