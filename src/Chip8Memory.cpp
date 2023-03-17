#include "Chip8Memory.hpp"

static const unsigned char chip8_default_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xf0, 0x10, 0xf0, 0x80, 0xf0,
    0xf0, 0x10, 0xf0, 0x10, 0xf0,
    0x90, 0x90, 0xf0, 0x10, 0x10,
    0xf0, 0x80, 0xf0, 0x10, 0xf0,
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    0xf0, 0x10, 0x20, 0x40, 0x40,
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    0xf0, 0x80, 0xf0, 0x80, 0xf0, 
    0xf0, 0x80, 0xf0, 0x80, 0x80
};

Chip8Memory::Chip8Memory()
{
    m_memory = new unsigned char[CHIP8_MEMORY_SIZE];   
    for(int i = 0 ; i < 4096 ; i++)
    {
        m_memory[i] = 0x00;
    }
    for(int i = 0 ; i < 80 ; i++){
        m_memory[i] = chip8_default_character_set[i];
    }
    
}

Chip8Memory::~Chip8Memory()
{
    free(m_memory);
}

void Chip8Memory::fillMemory(const char* data,int size,int address)
{
    for(size_t i = 0; i < size; i++){
        m_memory[i+address] = (unsigned char)data[i];
    }
}

unsigned short Chip8Memory::chip8_memory_get_short(int index)
{
    if(index >= CHIP8_MEMORY_SIZE)
    {
        std::cerr << "Program ended " << std::endl;
        exit(-1);
    }
    unsigned char byte = m_memory[index];
    unsigned char byte2 = m_memory[index+1];

    return byte << 8 | byte2;
}

unsigned char& Chip8Memory::operator[](int index)
{
    if(index >= CHIP8_MEMORY_SIZE){
        std::cerr << "Segmentation fault" << std::endl;
        exit(-1);
    }
    return m_memory[index];
}

