# asciiGL

asciiGL (ASCII Graphics Library) is a free and open-source console graphics library.
It is compatible with all operating systems and terminals that support ANSI Escape Sequences, these include WT (The new Windows Terminal), the macOS Terminal and most Linux terminals.

## Setup

Setting up asciiGL is very easy, just paste this code at the beginning of your main source file
```c
#include "src/asciigl.h"
#include "atk/utils.h"
```

Optionally, you can also specify flags before the include statements
```c
#define EXPERIMENTAL_FEATURES /* Allows experimental features such as keyboard input in atk and legacy mode */
#define NO_REFRESH_OPTIMIZATION /* Disables rendering optimizations */
```

If this doesn't work for you, try adding `../` at the start of every path.
You can then build an executable using a modern C/C++ Compiler (Like GCC), older compilers may not support some frequently used expressions. 
You can also use other languages by writing a wrapper, this can be done, in the case of a language like Python, with a C Extension written with Cython.
To showcase asciiGL'ss features, I built a paint program in C++, you can find it here: https://github.com/tzyvoski/ASCIIPaint
