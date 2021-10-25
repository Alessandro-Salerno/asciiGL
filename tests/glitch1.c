#include "../src/asciigl.h"
#include "../atk/utils.h"


int main()
{
    framebuffer buffer = Framebuffer(110, 28);

    for (int i = 0; i < buffer->size; i++)
        buffer->texture[i] = '+';

    atkInit(buffer);

    color col = 0;
    int dir = 1;

    while (true)
    {
        for (int y = 0; y < buffer->height; y++)
        {
            for (int x = 0; x < buffer->width; x++)
            {
                if (col == 255) dir = -10;
                if (col == 0)   dir = 10;

                aglSetCell(buffer, x, y, 219, col);
                col += dir;
            }
        }

        aglSwapBuffers(buffer);
    }

    atkEnd(buffer);
}
