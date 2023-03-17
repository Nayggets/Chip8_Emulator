
#include "Chip8Register.hpp"
Chip8Register::Chip8Register()
{
    
}
Chip8Register::~Chip8Register()
{

}


unsigned char& Chip8Register::operator[](int index)
{
    if(index >= CHIP8_TOTAL_DATA_REGISTERS){
        std::cerr << "Segmentation fault" << std::endl;
        exit(-1);
    }
    return m_v[index];
}

void Chip8Register::set_i(unsigned short i)
{
    m_i = i;
} 


unsigned short Chip8Register::get_i()
{
    return m_i;
}
