#include "../src/asciigl.h"

typedef struct
{
    int x;
    int y;
} star;


int main()
{
    framebuffer buffer = Framebuffer(110, 28);
    star stars[10];

    for (int i = 0; i < 10; i++)
    {
        stars[i].x = i * 10;
        stars[i].y = i;
    }

    for (int i = 0; i < buffer->size; i++)
        buffer->texture[i] = '+';

    aglInitContext(buffer);

    while (true)
    {
        for (int i = 0; i < buffer->size; i++)
            buffer->colorbuffer[i] = 17;

        for (int i = 0; i < buffer->size; i++)
            buffer->texture[i] = 219;

        for (int i = 0; i < 10; i++)
        {
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 5; y++)
                {
                    aglSetCell(buffer, x + stars[i].x, y + stars[i].y, 219, 220 + i);
                }
            }

            if (stars[i].y < 20)
                stars[i].y++;
            else
                stars[i].y = i;
        }

        aglSwapBuffers(buffer);
        wait_mills(16);
    }

    aglEndContext(buffer);
}
