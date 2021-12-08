#define EXPERIMENTAL_FEATURES

// Includes all the necessary libraries
#include "../src/asciigl.h"
#include "../atk/utils.h"


int main()
{
    // Sets the window title to "Baisc Program - asciiGL" 
    atkSetWindowTitle("Baisc Program - asciiGL");

    // Creates and initializes a framebuffer to use as asciiGL context
    framebuffer buffer = atkSetup();
    atkInit(buffer);
    
    // Game loop
    while (true)
    {
        // End the program if th ESCAPE ky is pressed
        if (atkGetKeyState(0x1B))
            atkEnd(buffer);

        // Checks if the window needs to b resized, resizes it if true, and jumps back the the start of the loop
        if (atkAutoResize(buffer))
            continue;

        // Paints the ntire buffer blue
        aglClear(buffer, AGL_EMPTY_CHAR, Blue, Blue);
        
        // Draws the changs on the screen
        aglSwapBuffers(buffer);
    }

    // Ends the program if the loop is exited
    atkEnd(buffer);
}
