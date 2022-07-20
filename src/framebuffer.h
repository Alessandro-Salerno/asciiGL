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


#ifndef ASCIIGL_FRAMEBUFFER_H
#define ASCIIGL_FRAMEBUFFER_H

    #include <stdlib.h>
    #include "types.h"


    struct _Framebuffer {
        unsigned int     width; 
        unsigned int     height; 
                 size_t  size;

                 cell_t* texture;
                 char*   printbuff;
    };

    typedef struct _Framebuffer* framebuffer_t;


    framebuffer_t aglNewFramebuffer(unsigned int width, unsigned int height) {
        framebuffer_t buffer = (framebuffer_t)(malloc(sizeof(struct _Framebuffer)));

        buffer->width        = width;
        buffer->height       = height;
        buffer->size         = width * height;
        buffer->texture      = (cell_t*)(malloc(sizeof(cell_t) * buffer->size));
        buffer->printbuff    = (char*)(malloc(buffer->size * 7));

        extern void _InitializeCell(cell_t* c, pixel_t content, rawcolor_t fgcolor, rawcolor_t bgcolor);
               int  i;

        for (i = 0; i < buffer->size; i++)
            _InitializeCell(&buffer->texture[i], ' ', 255, 0);

        return buffer;
    }

    void aglDeleteaglNewFramebuffer(framebuffer_t buffer) {
        free(buffer->texture);
        free(buffer->printbuff);
        free(buffer);
    }

    void aglResizeaglNewFramebuffer(framebuffer_t buffer, unsigned int new_width, unsigned int new_height) {
        aglDeleteaglNewFramebuffer(buffer);
        buffer = aglNewFramebuffer(new_width, new_height);
    }

    framebuffer_t aglCloneaglNewFramebuffer(framebuffer_t buffer) {
        framebuffer_t new_buffer  = aglNewFramebuffer(buffer->width, buffer->height);
                     *new_buffer  = *buffer;

        return new_buffer;
    }

#endif
