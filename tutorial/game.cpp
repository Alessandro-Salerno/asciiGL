#include "../tutorial/engine.hpp"


// tint is a global variable that holds the color of the next pixel
color_t tint = 0;

// Draws one cell
void DrawCell(framebuffer buffer, coord x, coord y)
{
    aglSetCell(buffer, x, y, AGL_EMPTY_CHAR, tint, tint);
    tint++;
}

// Draw is a function of type void that is called by the engine's scheduler and renders the frame
void Draw(framebuffer buffer)
{
    if (atkAutoResize(buffer))
        return;

    atkClear(buffer, AGL_EMPTY_CHAR, White, White);
    
    for (uint64 y = 0; y < buffer->height; y++)
        for (uint64 x = 0; x < buffer->width; x++)
            if (x % 2 == 0)
                DrawCell(buffer, x, y);

    atkWaitMills(16);
}


int main()
{
    // Creates an instance of the Engine class
    Engine engine;

    // Adds the rendering function to the engine's list of scheduled functions
    engine.ScheduleFunction(Draw);

    // Calls the engine's initialization method
    engine.Run();

    return 0;
}
