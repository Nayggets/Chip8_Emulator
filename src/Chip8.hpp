#pragma once

#include "Chip8Memory.hpp"
#include "Chip8Register.hpp"
#include "Chip8Stack.hpp"
#include "Chip8Keyboard.hpp"
#include "Chip8Screen.hpp"
#include <memory>
#include <time.h>
class Chip8
{
public:

    Chip8();
    ~Chip8();
    void chip8_memory_set(int index, unsigned char val);
    unsigned char chip8_memory_get(int index);
    void run(char* code,int size);

    void chip8_do_instruction(unsigned short opcode);
    void chip8_load_instruction(char* buf,int size);
    void chip8_do_extended_instruction(unsigned short opcode);
    void chip8_do_extended_0x8000_instruction(unsigned short opcde);
    void chip8_do_extended_0xF000_instruction(unsigned short opcode);
    char chip8_wait_for_key_press();
private:
    std::unique_ptr<Chip8Memory> m_chip_memory; 
    std::unique_ptr<Chip8Stack> m_stack;
    std::unique_ptr<Chip8Register> m_chip_register;
    std::unique_ptr<Chip8Keyboard> m_chip_keyboard;
    std::unique_ptr<Chip8Screen> m_chip_screen;
    unsigned char m_delay_timer;
    unsigned char m_sound_timer;
    unsigned short m_PC;

};

