#include "../src/asciigl.h"
#include "../atk/colors.h"
#include "../atk/utils.h"


int main()
{
    framebuffer buffer = atkSetup();
    aglClear(buffer, AGL_EMPTY_CHAR, White, White);
    atkInit(buffer);
    
    while (true)
    {
        aglClear(buffer, AGL_EMPTY_CHAR, White, White);
        aglSwapBuffers(buffer);
    }

    atkEnd(buffer);
}
