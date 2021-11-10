#define EXPERIMENTAL_FEATURES
#define LEGACY_CONSOLE
#define NO_REFRESH_OPTIMIZATION
#include "../src/asciigl.h"
#include "../atk/utils.h"


int main()
{
    system("");
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
