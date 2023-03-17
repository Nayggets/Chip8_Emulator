#pragma once

#include "config.hpp"

class Chip8Stack
{

    public:
        Chip8Stack();
        ~Chip8Stack();
        void chip8_stack_push(unsigned short val);
        unsigned short chip8_stack_pop();

    private:
        void chip8_stack_in_bounds();

        unsigned short m_stack[CHIP8_TOTAL_STACK_DEPTH];
        unsigned char m_SP;

};