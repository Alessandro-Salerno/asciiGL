#include "../src/asciigl.h"
#include "../atk/utils.h"
#include <math.h>
#include <time.h>


int main()
{
    srand(time(NULL));
    framebuffer buffer = Framebuffer(110, 28);

    for (int i = 0; i < buffer->size; i++)
        buffer->texture[i] = '+';

    atkInit(buffer);

    int y = 12;
    int prev = y;

    while (true)
    {
        for (int i = 0; i < buffer->size; i++)
            buffer->colorbuffer[i] = 0;

        for (int i = 0; i < buffer->size; i++)
            buffer->texture[i] = 219;

        prev = y;

        for (int x = 0; x < 110; x++)
        {
            if (y == 0)
                y += 1;
            
            else if (y == 25)
                y -= 1;

            for (int i = 0; i < 2 && y < 25; i++)
                y += rand() % 2;

            for (int i = 0; i < 2 && y > 0; i++)
                y -= rand() % 2;

            aglSetCell(buffer, x, y, 219, 118);

            aglSwapBuffers(buffer);
            atkWaitMills(16);
        }
        
        y = rand() % 20;
    }

    aglEndContext(buffer);
}