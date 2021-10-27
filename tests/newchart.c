#include "../src/asciigl.h"
#include "../atk/colors.h"
#include "../atk/utils.h"
#include <math.h>
#include <time.h>


int main()
{
    atkSetWindowTitle("Chart Generator - asciiGL");

    coord y = 12;
    srand(time(NULL));

    framebuffer buffer = atkSetup();
    atkClear(buffer, '+', Black, Black);
    atkInit(buffer);

    while (true)
    {
        atkClear(buffer, AGL_EMPTY_CHAR, Black, Black);

        for (coord x = 0; x < buffer->width; x++)
        {
            if (atkAutoResize(buffer))
                break;

            if      (y == 0)                  y += 1;
            else if (y == buffer->height - 3) y -= 1;

            for (int i = 0; i < 2 && y < buffer->height - 3; i++)
                y += rand() % 2;

            for (int i = 0; i < 2 && y > 0; i++)
                y -= rand() % 2;

            aglSetCell(buffer, x, y, AGL_EMPTY_CHAR, 118, 118);
            aglSwapBuffers(buffer);
            atkWaitMills(16);
        }
        
        y = rand() % (buffer->height - 10);
    }

    atkEnd(buffer);
}
