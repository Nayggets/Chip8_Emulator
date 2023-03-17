#include "Chip8Stack.hpp"
#include <assert.h>

void Chip8Stack::chip8_stack_in_bounds()
{
    if(m_SP >= CHIP8_TOTAL_STACK_DEPTH){
        std::cerr << "Stack out of bounds" << std::endl;
        exit(-1);
    }

}
Chip8Stack::Chip8Stack()
{
    m_SP = 0;
}
Chip8Stack::~Chip8Stack()
{
    
}
void Chip8Stack::chip8_stack_push(unsigned short val)
{
    m_SP += 1;
    chip8_stack_in_bounds();

    m_stack[m_SP] = val;
}

unsigned short Chip8Stack::chip8_stack_pop()
{
    chip8_stack_in_bounds();
    
    unsigned short result = m_stack[m_SP];
    m_SP -=1;
    return result;
}

