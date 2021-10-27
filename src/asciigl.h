/***********************************************************************
                                     asciiGL
                        Copyright 2021 Alessandro Salerno

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
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define AGL_EMPTY_CHAR ' '
    
    
    #pragma region CONSOLE
        void consoleMoveCursor(int x, int y)
        {
            printf("\033[%d;%dH", y, x);
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
    #pragma endregion


    #pragma region FRAMEBUFFER
        typedef unsigned char pixel; 
        typedef unsigned int coord;
        typedef unsigned char color_t; 

        typedef struct
        {
            color_t fgcolor;
            color_t bgcolor;
        } color;

        typedef struct
        {
            pixel content;
            color tint;
            bool  update;
            bool  uptint; 
        } cell;

        static void _InitializeCell(cell* c, pixel content, color_t fgcolor, color_t bgcolor)
        {
            c->content = content;
            c->tint    = (color) { .fgcolor = fgcolor, .bgcolor = bgcolor };
            c->update  = true;
            c->uptint  = true;
        }

        typedef struct
        {
            unsigned int    width; 
            unsigned int    height; 
                     size_t size;

            cell*           texture;
            char*           printbuff;
        } _Framebuffer;

        typedef _Framebuffer* framebuffer;

        framebuffer Framebuffer(unsigned int width, unsigned int height)
        {
            framebuffer buffer    = (framebuffer)(malloc(sizeof(_Framebuffer)));

            buffer->width     = width;
            buffer->height    = height;
            buffer->size      = width * height;

            buffer->texture   = (cell*)(malloc(sizeof(cell) * buffer->size));
            buffer->printbuff = (char*)(malloc(buffer->size * 7));

            for (int i = 0 ; i < buffer->size; i++)
                _InitializeCell(&buffer->texture[i], ' ', 255, 0);

            return buffer;
        }
    #pragma endregion


    #pragma region ASCIIGL_FUNCTIONS
        int aglTranslateCoordinates(framebuffer buffer, coord x, coord y)
        {
            return y * buffer->width + x;
        }

        void aglDrawIndex(framebuffer buffer, unsigned int index)
        {
            if (buffer->texture[index].uptint)
                printf("\033[38;5;%dm\033[48;5;%dm", buffer->texture[index].tint.fgcolor, buffer->texture[index].tint.bgcolor);

            printf("%lc", buffer->texture[index].content);
        }
        
        void aglDrawCell(framebuffer buffer, coord x, coord y)
        {
            consoleMoveCursor(x, y);
            aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
        }

        void aglDrawFramebuffer(framebuffer buffer)
        {
            for (coord y = 0; y < buffer->height; y++)
            {
                for (coord x = 0; x < buffer->width; x++)
                    aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));

                printf("\n");
            }
        }

        void aglSwapBuffers(framebuffer buffer)
        {
            for (coord y = 0; y < buffer->height; y++)
            {
                for (coord x = 0; x < buffer->width; x++)
                {
                    unsigned int index = aglTranslateCoordinates(buffer, x, y);

                    if (buffer->texture[index].update | buffer->texture[index].uptint)
                        aglDrawCell(buffer, x, y);
                }
            }
        }

        void aglResizeFramebuffer(framebuffer buffer, unsigned int new_width, unsigned int new_height)
        {
            unsigned int idx      = buffer->size; 

            buffer->width         = new_width;
            buffer->height        = new_height;
            buffer->size          = new_width * new_height;

            buffer->texture       = (cell*)(realloc(buffer->texture, buffer->size * sizeof(cell)));
            buffer->printbuff     = (char*)(realloc(buffer->printbuff, buffer->size * 7));

            for (int i = idx ; i < buffer->size; i++)
                _InitializeCell(&buffer->texture[i], ' ', 255, 0);
        }

        void aglSetCell(framebuffer buffer, coord x, coord y, pixel content, color_t fgcolor, color_t bgcolor)
        {
            unsigned int idx = aglTranslateCoordinates(buffer, x, y);
            
            buffer->texture[idx].content       = content;
            buffer->texture[idx].tint.fgcolor  = fgcolor;
            buffer->texture[idx].tint.bgcolor  = bgcolor;
        }

        void aglInitContext(framebuffer buffer)
        {
            consoleClearScreen();
            consoleHideCursor();
            setvbuf(stdout, buffer->printbuff, _IOFBF, buffer->size * 7);
            aglDrawFramebuffer(buffer);
        }

        void aglEndContext(framebuffer buffer)
        {
            free(buffer->texture);
            free(buffer->printbuff);
            free(buffer);
        }
    #pragma endregion


#endif
