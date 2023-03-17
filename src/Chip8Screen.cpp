#include "Chip8Screen.hpp"

static void chip8_screen_check_bounds(int x,int y)
{
    if(x < 0 || y < 0 || (x >= CHIP8_WIDTH || y  >= CHIP8_HEIGHT)){
        std::cerr << "Screen out of bounds" << std::endl;
        exit(-1);
    }
}


Chip8Screen::Chip8Screen()
{
    
}
Chip8Screen::~Chip8Screen()
{

}



bool Chip8Screen::chip8_screen_is_set(int x, int y)
{
    chip8_screen_check_bounds(x,y);
    return m_screen[y][x];
}

void Chip8Screen::chip8_screen_set(int x,int y)
{    
    chip8_screen_check_bounds(x,y);
    m_screen[y][x] = true; 
}

void Chip8Screen::chip8_screen_clear()
{
    for(int i = 0 ; i < CHIP8_HEIGHT ; i++){
        for(int j = 0 ; j < CHIP8_WIDTH ; j++)
        {
            m_screen[i][j] = false;
        }
    }}

bool Chip8Screen::chip8_screen_draw_sprite(int x,int y, const char* sprite, int num)
{
    bool pixel_collision = false;


    for(int i = 0 ; i < num; i++)
    {
        char c = sprite[i];
        for(int j = 0 ; j < 8 ; j++)
        {
            if((c & (0b10000000 >> j)) == 0)
            {
                continue;
            }
            if(m_screen[(i+y) % CHIP8_HEIGHT][(j+x) % CHIP8_WIDTH])
            {
                pixel_collision = true;
            }
            m_screen[(i+y) % CHIP8_HEIGHT][(j+x) % CHIP8_WIDTH] ^= true;
        }
    }
    return pixel_collision;
}