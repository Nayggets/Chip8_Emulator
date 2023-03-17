#include "Chip8Keyboard.hpp"
#include "SDL2/SDL.h"

    Chip8Keyboard::Chip8Keyboard()
    {
        m_keyboard_map[0] = SDLK_0;
        m_keyboard_map[1] = SDLK_1;
        m_keyboard_map[2] = SDLK_2;
        m_keyboard_map[3] = SDLK_3;
        m_keyboard_map[4] = SDLK_4;
        m_keyboard_map[5] = SDLK_5;
        m_keyboard_map[6] = SDLK_6;
        m_keyboard_map[7] = SDLK_7;
        m_keyboard_map[8] = SDLK_8;
        m_keyboard_map[9] = SDLK_9;
        m_keyboard_map[10] = SDLK_a;
        m_keyboard_map[11] = SDLK_b;
        m_keyboard_map[12] = SDLK_c;
        m_keyboard_map[13] = SDLK_d;
        m_keyboard_map[14] = SDLK_e;
        m_keyboard_map[15] = SDLK_f;

    }
    Chip8Keyboard::~Chip8Keyboard()
    {

    }

    static void chip8_keyboard_is_in_bounds(char key)
    {
        if(key < 0 || key >= CHIP8_TOTAL_KEYS)
        {
            std::cerr << "Keyboard not in bound" << std::endl;
            
        }
    }



    int Chip8Keyboard::chip8_keyboard_map(char key)
    {
        for(int i = 0 ; i < CHIP8_TOTAL_KEYS ; i++){
            if(m_keyboard_map[i] == key)
            {
                return i;
            }
        }
        return -1;
    }
    void Chip8Keyboard::chip8_keyboard_down(unsigned char key)
    {
        m_keyboard[key] = true;
    }
    void Chip8Keyboard::chip8_keyboard_up(unsigned char key)
    {
        m_keyboard[key] =  false;
    }
    bool Chip8Keyboard::chip8_keyboard_is_down(unsigned char key)
    {
        return m_keyboard[key];
    }