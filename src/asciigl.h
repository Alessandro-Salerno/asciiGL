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
        typedef struct
        {
            unsigned char* colorbuffer; 
            unsigned char* previouscolor; 

                     char* texture;
                     char* previoustex;
                     char* printbuff;

                     int   width;
                     int   height;
                     int   size;
        } _Framebuffer;

        typedef _Framebuffer* framebuffer;
        typedef unsigned char color;

        framebuffer Framebuffer(int width, int height)
        {
            framebuffer buffer    = (framebuffer)(malloc(sizeof(_Framebuffer)));

            buffer->width         = width;
            buffer->height        = height;
            buffer->size          = width * height;

            buffer->texture       = (char*)(malloc(buffer->size));
            buffer->previoustex   = (char*)(malloc(buffer->size));
            buffer->printbuff     = (char*)(malloc(buffer->size * 5));
            buffer->colorbuffer   = (unsigned char*)(malloc(buffer->size));
            buffer->previouscolor = (unsigned char*)(malloc(buffer->size));
            
            for (int i = 0; i < buffer->size; i++)
            {
                buffer->texture[i]       = ' ';
                buffer->previoustex[i]   = ' ';
                buffer->colorbuffer[i]   = 0;
                buffer->previouscolor[i] = 0;
            }

            return buffer;
        }
    #pragma endregion


    #pragma region ASCIIGL_FUNCTIONS
        int aglTranslateCoordinates(framebuffer buffer, int x, int y)
        {
            return y * buffer->width + x;
        }

        void aglDrawIndex(framebuffer buffer, int index)
        {
            if (buffer->colorbuffer[index] != buffer->colorbuffer[index - 1])
                printf("\033[38;5;%dm", buffer->colorbuffer[index]);

            printf("%c", buffer->texture[index]);
        }

        void aglDrawCell(framebuffer buffer, int x, int y)
        {
            consoleMoveCursor(x, y);
            aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));
        }

        void aglEndDraw(framebuffer buffer)
        {
            for (int i = 0; i < buffer->size; i++)
            {
                buffer->previoustex[i] = buffer->texture[i];
                buffer->previouscolor[i] = buffer->colorbuffer[i];
            }
        }

        void aglDrawFramebuffer(framebuffer buffer)
        {
            for (int y = 0; y < buffer->height; y++)
            {
                for (int x = 0; x < buffer->width; x++)
                    aglDrawIndex(buffer, aglTranslateCoordinates(buffer, x, y));

                printf("\n");
            }

            aglEndDraw(buffer);
        }

        void aglSwapBuffers(framebuffer buffer)
        {
            for (int y = 0; y < buffer->height; y++)
            {
                for (int x = 0; x < buffer->width; x++)
                {
                    int index = aglTranslateCoordinates(buffer, x, y);

                    if (buffer->texture[index] != buffer->previouscolor[index] || buffer->colorbuffer[index] != buffer->previouscolor[index])
                    {
                        aglDrawCell(buffer, x, y);
                        
                        if (index + 1 != buffer->size)
                            aglDrawIndex(buffer, index + 1);
                        else
                            aglDrawIndex(buffer, index);
                    }
                }
            }

            aglEndDraw(buffer);
        }

        void aglResizeFramebuffer(framebuffer buffer, int new_width, int new_height)
        {
            buffer->width         = new_width;
            buffer->height        = new_height;
            buffer->size          = new_width * new_height;

            buffer->texture       = (char*)(realloc(buffer->texture, buffer->size));
            buffer->previoustex   = (char*)(realloc(buffer->previoustex, buffer->size));
            buffer->colorbuffer   = (unsigned char*)(realloc(buffer->colorbuffer, buffer->size));
            buffer->previouscolor = (unsigned char*)(realloc(buffer->previouscolor, buffer->size));
        }

        void aglSetCell(framebuffer buffer, int x, int y, char content, color clr)
        {
            buffer->texture[aglTranslateCoordinates(buffer, x, y)] = content;
            buffer->colorbuffer[aglTranslateCoordinates(buffer, x, y)] = clr; 
        }

        void aglInitContext(framebuffer buffer)
        {
            consoleClearScreen();
            consoleHideCursor();

            setvbuf(stdout, buffer->printbuff, _IOFBF, buffer->size * 5);

            aglDrawFramebuffer(buffer);
        }

        void aglEndContext(framebuffer buffer)
        {
            free(buffer->texture);
            free(buffer->previoustex);
            free(buffer->colorbuffer);
            free(buffer->previouscolor);
            free(buffer);

            consoleClearScreen();
            consoleRestoreCursorPosition();
            consoleShowCursor();
        }
    #pragma endregion

#endif
