#ifndef ENGINE_H
#define ENGINE_H

    #include "../src/asciigl.h"
    #include "../atk/colors.h"
    #include "../atk/utils.h"

    typedef               char   int8;
    typedef unsigned      char   uint8;
    typedef               short  int16;
    typedef unsigned      short  uint16;
    typedef               int    int32;
    typedef unsigned      int    uint32;
    typedef          long int    int64;
    typedef unsigned long int    uint64;
    typedef               float  decimal32;
    typedef               double decimal64;


    namespace BasicEngine
    {
        template <typename T>
        class Vector
        {
            // Private variable declaration
            private:
                uint64 _Size;
                T*     _Array;
                uint64 _Length;

            // Public variable declarations
            public:
                uint64 size;
                uint64 len;

            // Private method definitions
            private:
                void _Update(uint64 size, uint64 length)
                {
                    this->_Size   = size;
                    this->_Length = length;

                    this->size = this->_Size;
                    this->len  = this->_Length;
                }

                void _Resize(uint64 size)
                {
                    this->_Array = (T*)(realloc(this->_Array, size * sizeof(T)));
                    this->_Update(size, this->_Length);
                }

            // Public method definitions
            public:
                Vector()
                {
                    this->_Update(32, 0);
                    this->_Array  = (T*)(malloc(this->_Size * sizeof(T)));
                }

                Vector(uint64 size)
                {
                    this->_Update(size, 0);
                    this->_Array  = (T*)(malloc(this->_Size * sizeof(T)));
                }

                void Push(T item)
                {
                    if (this->_Length + 1 == this->_Size)
                        this->_Resize(this->_Size * 2);

                    this->_Array[this->_Length] = item;
                    this->_Update(this->_Size, this->_Length + 1);
                }

                void Pop(uint64 index)
                {
                    for (uint64 i = index; i < this->_Length - 1; i++)
                        this->_Array[i] = this->_Array[i + 1];

                    this->_Array[this->_Length - 1] = NULL;
                    this->_Update(this->_Size, this->_Length - 1);
                }

                void Clear()
                {
                    for (uint64 i = 0; i < this->_Length; i++)
                        this->_Array[i] = NULL;

                    this->_Update(this->_Size, 0);
                }

                T Get(uint64 index)
                {
                    return this->_Array[index];
                }

                void Set(uint64 index, T item)
                {
                    this->_Array[index] = item;
                }
        };


        class Clock
        {
            // Private variable declarations
            private:
                Vector<void (*)(framebuffer)> _RenderingFunctions;

            // Public method definitions
            public:
                void ScheduleFunction(void (*function)(framebuffer))
                {
                    this->_RenderingFunctions.Push(function);
                }

                void Run()
                {
                    // Set the window title
                    atkSetWindowTitle("Basic Engine v1.0 - Small Game");

                    // Creates a new framebuffer using ATK
                    framebuffer buffer = atkSetup();

                    // Clears and draws the buffer
                    aglClear(buffer, AGL_EMPTY_CHAR, Black, Black);
                    atkInit(buffer);

                    // Main loop
                    while (true)
                    {
                        // Cals every scheduled function
                        for (uint64 i = 0; i < this->_RenderingFunctions.len; i++)
                            this->_RenderingFunctions.Get(i)(buffer);

                        // Draws the frame
                        aglSwapBuffers(buffer);
                    }

                    // Terminates the asciiGL session
                    atkEnd(buffer);
                }
        };
    }

#endif
