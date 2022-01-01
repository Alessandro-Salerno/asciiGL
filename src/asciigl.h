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


#ifndef ASCIIGL_H
#define ASCIIGL_H

    #include <stdio.h>
    #include <stdlib.h>

    #include "types.h"
    #include "console.h"
    #include "framebuffer.h"
    #include "mathf.h"
    #include "display.h"

    #define AGL_EMPTY_CHAR ' '


    void aglInitContext(framebuffer buffer)
    {
        consoleClearScreen();
        consoleHideCursor();
        consoleMoveCursor(0, 0);
        setvbuf(stdout, buffer->printbuff, _IOFBF, buffer->size * 7);
        
        aglDrawFramebuffer(buffer);
    }

    void aglEndContext()
    {
        consoleClearScreen();
        consoleRestoreCursorPosition();
        consoleShowCursor();
    }

#endif
