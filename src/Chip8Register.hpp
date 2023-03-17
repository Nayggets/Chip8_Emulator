#pragma once
#include "config.hpp"
class Chip8Register
{
    public:
        Chip8Register();
        ~Chip8Register();
        unsigned char& operator[](int);
        void set_i(unsigned short i);
        unsigned short get_i();
    private:
        unsigned char m_v[CHIP8_TOTAL_DATA_REGISTERS];
        unsigned short m_i;
};