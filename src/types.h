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


#ifndef ASCIIGL_TYPES_H
#define ASCIIGL_TYPES_H

    #include <stdbool.h>


    typedef unsigned char pixel;
    typedef unsigned char color_t; 
    typedef unsigned int  coord;

    typedef struct color
    {
        color_t fgcolor;
        color_t bgcolor;
    } color;

    typedef struct cell
    {
        pixel content;
        color tint;
        bool  update; 
    } cell;

    static void _InitializeCell(cell* c, pixel content, color_t fgcolor, color_t bgcolor)
    {
        c->content = content;
        c->tint    = (color) { .fgcolor = fgcolor, .bgcolor = bgcolor };
        c->update  = true;
    }

#endif
