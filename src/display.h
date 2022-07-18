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


#ifndef ASCIIGL_DISPLAY_H
#define ASCIIGL_DISPLAY_H

    #include <stdio.h>

    #include "mathf.h"
    #include "console.h"
    #include "framebuffer.h"


    void aglDrawIndex(framebuffer_t buffer, unsigned int index) {
        #ifndef NO_REFRESH_OPTIMIZATION
            if (buffer->texture[index].update)
        #endif
                printf(
                    "\033[38;5;%dm\033[48;5;%dm%lc",
                    buffer->texture[index].tint.fgcolor,
                    buffer->texture[index].tint.bgcolor,
                    buffer->texture[index].content
                );
    }
    
    void aglDrawCell(framebuffer_t buffer, coord x, coord y) {
        consoleMoveCursor(x, y);
        aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
    }

    void aglEndDraw(framebuffer_t buffer) {
        unsigned int i;
        for (i = 0; i < buffer->size; i++)
            buffer->texture[i].update = false;
    }

    void aglDrawFramebuffer(framebuffer_t buffer) {
        coord x, y;
        for (y = 0; y < buffer->height; y++) {
            if (y) printf("\n");
            for (x = 0; x < buffer->width; x++)
                aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
        }

        aglEndDraw(buffer);
    }

    void aglSwapBuffers(framebuffer_t buffer) {
        coord x, y;
        for (y = 0; y < buffer->height; y++)
            for (x = 0; x < buffer->width; x++)
                aglDrawCell(buffer, x, y);

        aglEndDraw(buffer);
    }

    void aglSetCell(framebuffer_t buffer, coord x, coord y, pixel content, color_t fgcolor, color_t bgcolor) {
        unsigned int idx = aglTranslateCoordinates(buffer, x, y);
        
        buffer->texture[idx].update        = !(buffer->texture[idx].content == content && buffer->texture[idx].tint.fgcolor == fgcolor && buffer->texture[idx].tint.bgcolor == bgcolor);
        buffer->texture[idx].content       = content;
        buffer->texture[idx].tint.fgcolor  = fgcolor;
        buffer->texture[idx].tint.bgcolor  = bgcolor;
    }

    void aglClear(framebuffer_t buffer, pixel chr, color_t fgcolor, color_t bgcolor) {
        coord x, y;
        for (y = 0; y < buffer->height; y++)
            for (x = 0; x < buffer->width; x++)
                aglSetCell(buffer, x, y, chr, fgcolor, bgcolor);
    }

#endif
