/***********************************************************************
                                     asciiGL
                   Copyright 2021 - 2022 Alessandro Salerno

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


#ifndef ASCIIGL_CONSOLE_H
#define ASCIIGL_CONSOLE_H

    #include <stdio.h>


    void consoleMoveCursor(int x, int y)
    {
        printf("\033[%d;%dH", y + 1, x + 1);
    }

    void consoleRestoreCursorPosition()
    {
        printf("\033[k");
    }

    void consoleHideCursor()
    {
        printf("\e[?25l");
    }

    void consoleShowCursor()
    {
        printf("\e[?25h");
    }

    void consoleClearScreen()
    {
        printf("\033c");
    }

#endif
