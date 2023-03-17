#pragma once
#include <cstring>

#include "config.hpp"
class Chip8Memory
{

    public:
        Chip8Memory();
        ~Chip8Memory();

        unsigned char& operator[](int);
        unsigned short chip8_memory_get_short(int index);
        void fillMemory(const char* data,int size,int address);
    private:
        unsigned char* m_memory;

};