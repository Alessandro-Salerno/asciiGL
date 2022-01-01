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


#ifndef ASCIIGL_MATHF_H
#define ASCIIGL_MATHF_H

    #include "framebuffer.h"


    int aglTranslateCoordinates(framebuffer buffer, coord x, coord y)
    {
        return y * buffer->width + x;
    }

#endif
