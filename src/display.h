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


    void aglDrawIndex(framebuffer buffer, unsigned int index)
    {
        #ifndef NO_REFRESH_OPTIMIZATION
            if (buffer->texture[index].update)
        #endif
        {
            printf(
                "\033[38;5;%dm\033[48;5;%dm",
                buffer->texture[index].tint.fgcolor,
                buffer->texture[index].tint.bgcolor
            );

            printf("%lc", buffer->texture[index].content);
        }
    }
    
    void aglDrawCell(framebuffer buffer, coord x, coord y)
    {
        consoleMoveCursor(x, y);
        aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
    }

    void aglEndDraw(framebuffer buffer)
    {
        register unsigned int i;
        for (i = 0; i < buffer->size; i++)
            buffer->texture[i].update = false;
    }

    void aglDrawFramebuffer(framebuffer buffer)
    {
        register coord x, y;
        for (y = 0; y < buffer->height; y++)
        {
            (y != 0) ? printf("\n") : 0;

            for (x = 0; x < buffer->width; x++)
                aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
        }

        aglEndDraw(buffer);
    }

    void aglSwapBuffers(framebuffer buffer)
    {
        register coord x, y;
        for (y = 0; y < buffer->height; y++)
            for (x = 0; x < buffer->width; x++)
                aglDrawCell(buffer, x, y);

        aglEndDraw(buffer);
    }

    void aglSetCell(framebuffer buffer, coord x, coord y, pixel content, color_t fgcolor, color_t bgcolor)
    {
        unsigned int idx = aglTranslateCoordinates(buffer, x, y);
        
        buffer->texture[idx].update        = !(buffer->texture[idx].content == content && buffer->texture[idx].tint.fgcolor == fgcolor && buffer->texture[idx].tint.bgcolor == bgcolor);
        buffer->texture[idx].content       = content;
        buffer->texture[idx].tint.fgcolor  = fgcolor;
        buffer->texture[idx].tint.bgcolor  = bgcolor;
    }

    void aglClear(framebuffer buffer, pixel chr, color_t fgcolor, color_t bgcolor)
    {
        register coord x, y;
        for (y = 0; y < buffer->height; y++)
            for (x = 0; x < buffer->width; x++)
                aglSetCell(buffer, x, y, chr, fgcolor, bgcolor);
    }

#endif
