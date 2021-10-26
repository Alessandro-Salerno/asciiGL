#include "../src/asciigl.h"
#include "../atk/utils.h"
#include <math.h>
#include <time.h>


int main()
{
    int y = 12;
    srand(time(NULL));

    framebuffer buffer = atkSetup();
    atkClear(buffer, '+', 255);
    atkInit(buffer);

    while (true)
    {
        atkClear(buffer, 219, 0);

        for (int x = 0; x < buffer->width; x++)
        {
            atkAutoResize(buffer);

            if (y == 0)
                y += 1;
            
            else if (y == buffer->height - 3)
                y -= 1;

            for (int i = 0; i < 2 && y < buffer->height - 3; i++)
                y += rand() % 2;

            for (int i = 0; i < 2 && y > 0; i++)
                y -= rand() % 2;

            aglSetCell(buffer, x, y, 219, 118);
            aglSwapBuffers(buffer);
            atkWaitMills(16);
        }
        
        y = rand() % buffer->height - 10;
    }

    atkEnd(buffer);
}
