#include "../src/asciigl.h"


int main()
{
    framebuffer buffer = Framebuffer(110, 28);

    for (int i = 0; i < buffer->size; i++)
        buffer->texture[i] = '+';

    aglInitContext(buffer);

    color col = 16;
    int dir = 1;
    int x = 0;
    int y = 0;
    int prev = col;
    color col2 = 0;
    int dir2;

    for (int y = 0; y < buffer->height; y++)
        {
            for (int x = 0; x < buffer->width; x++)
            {
                if (col == 21) dir = -1;
                if (col == 16)  dir = 1;

                aglSetCell(buffer, x, y, 219, col);
                col += dir;
            }
        }

        for (int y = 0; y < buffer->height; y++)
        {
            for (int x = 0; x < buffer->width; x++)
            {
                if (y % 2 == 0)
                {
                    if (col == 221) dir = -2;
                    if (col == 226)  dir = 2;

                    aglSetCell(buffer, x, y, 219, col);
                    col += dir;
                }
            }
        }

    while (true)
    {  
        if (col2 == 255) dir2 = -15;
        if (col2 == 0)  dir2 = 15;
        col2 += dir2;

        if (y >= 0 && y < buffer->height) y++; else y = 0;
        if (x >= 0 && x < buffer->width) x++; else x = 0;

        aglSetCell(buffer, x, y, 219, col2);

        aglSwapBuffers(buffer);
    }

    aglEndContext(buffer);
}
