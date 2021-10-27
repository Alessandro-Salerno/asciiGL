# asciiGL

asciiGL (ASCII Graphics Library) is a free and open-source console graphics library.
It is compatible with all operating systems and terminals that support ANSI Escape Sequences, these include WT (The new Windows Terminal), the macOS Terminal and most Linux terminals.

## Setup

Setting up asciiGL is very easy, just paste this code at the beginning of your main source file
```c
#include "src/asciigl.h"
#include "atk/colors.h"
#include "atk/utils.h"
```

If this doesn't work for you, try adding `../` at the start of every path.
You can then build an executable using a modern C/C++ Compiler (Like GCC), older compilers may not support some expressions frequently used in the code.
You can also use other languages by writing a wrapper, this can be done, in the case of a language like Python, with a C Extension written with Cython.
