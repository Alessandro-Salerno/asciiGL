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
    #include "colors.h"
    #include <stdlib.h>

    #ifndef _WIN32
        #include <string.h>
        #include <termios.h>
        #include <fcntl.h>

        static struct termios orig_termios;
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

    // Change window title
    void atkSetWindowTitle(const char* title)
    {
        #ifdef _WIN32
            SetConsoleTitle(title);
        #else
            printf("\033]0;%s\007", title);
        #endif
    }
    
    // Reset console, cursor and exit
    static void atkEndProgram(int signum)
    {
        consoleClearScreen();
        consoleRestoreCursorPosition();
        consoleShowCursor();
        exit(0);
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
                     height = atkGetConsoleHeight();

        return Framebuffer(width, height);
    }

    // Init framebuffer and event listener
    void atkInit(framebuffer buffer)
    {
        #ifdef _WIN32
            system("");
        #else
            #ifdef EXPERIMENTAL_FEATURES
                struct termios new_termios;

                tcgetattr(0, &orig_termios);
                memcpy(&new_termios, &orig_termios, sizeof(new_termios));

                cfmakeraw(&new_termios);
                tcsetattr(0, TCSANOW, &new_termios);
                consoleClearScreen();
            #endif
        #endif

        aglInitContext(buffer);
        signal(SIGINT, atkEndProgram);
    }

    // automatically resizes the framebuffer if the window has been resized
    bool atkAutoResize(framebuffer buffer)
    {
        unsigned int width  = atkGetConsoleWidth(),
                     height = atkGetConsoleHeight();

        if (buffer->width == width && buffer->height == height)
            return false;

        aglResizeFramebuffer(buffer, width, height);
        aglClear(buffer, AGL_EMPTY_CHAR, Black, Black);
        consoleClearScreen();
        consoleHideCursor();
        aglDrawFramebuffer(buffer);
        
        return true;
    }

    // Terminates everything
    void atkEnd(framebuffer buffer)
    {
        aglEndContext(buffer);
        atkEndProgram(0);
    }
    
    // Experimental async input handler
    #if defined (_WIN32) && defined (EXPERIMENTAL_FEATURES)
        short atkGetKeyState(int key)
        {
            return GetAsyncKeyState(key);
        }
    #else
        short atkGetKeyState(int key)
        {
            unsigned char c;
                     int  r;
            
            fcntl(0, F_SETFL, O_NONBLOCK);
            int ret = ((r = read(0, &c, sizeof(c))) < 0) ? r : c;
            fcntl(0, F_SETFL, O_SYNC);
            
            return ret == key;
        }
    #endif

#endif
