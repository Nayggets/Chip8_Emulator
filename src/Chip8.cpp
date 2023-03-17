#include "Chip8.hpp"
#include "SDL2/SDL.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>


Chip8::Chip8()
{
    m_chip_keyboard = std::make_unique<Chip8Keyboard>();
    m_chip_memory = std::make_unique<Chip8Memory>();
    m_chip_register = std::make_unique<Chip8Register>();
    m_chip_screen = std::make_unique<Chip8Screen>();
    m_stack = std::make_unique<Chip8Stack>();

}

Chip8::~Chip8()
{
}

void Chip8::run(char* code,int size)
{

    chip8_load_instruction(code,size);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(EMULATOR_WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,CHIP8_HEIGHT *CHIP8_WINDOW_MULTIPLIER,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    bool m_quit = true;
    while(m_quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    m_quit = false;
                break;

                case SDL_KEYDOWN:
                {
                    char key = event.key.keysym.sym;
                    int vkey = m_chip_keyboard->chip8_keyboard_map(key);
                    if (vkey != -1)
                    {
                        m_chip_keyboard->chip8_keyboard_down(vkey);
                    }
                }
                break;

                case SDL_KEYUP:
                {

                    char key = event.key.keysym.sym;
                    int vkey = m_chip_keyboard->chip8_keyboard_map(key);
                    if (vkey != -1)
                    {
                        m_chip_keyboard->chip8_keyboard_up(vkey);
                    }
                }
                break;
            };

        }
        SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        for(int x = 0 ; x < CHIP8_WIDTH ;x++){
            for(int y = 0 ; y < CHIP8_HEIGHT ; y++){
                if(m_chip_screen->chip8_screen_is_set(x,y))
                {
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer,&r);
                }
 
            }
        }

        SDL_RenderPresent(renderer);

        if(m_delay_timer > 0)
        {
            usleep(800);
            m_delay_timer--;
        }

        if(m_sound_timer > 0)
        {
            std::cout << "\a" << std::endl;
            m_sound_timer = 0;
        }

        unsigned short opcode = m_chip_memory->chip8_memory_get_short(m_PC);
        m_PC += 2;
        chip8_do_instruction(opcode);

    }
    SDL_DestroyWindow(window);
    return;
}



void Chip8::chip8_load_instruction(char* buf,int size)
{
    if(size + CHIP8_PROGRAM_ADDRESS >=  CHIP8_MEMORY_SIZE)
    {
        std::cerr << "Program to big to load" << std::endl;
        exit(-1);
    }
    m_chip_memory->fillMemory(buf,size,CHIP8_PROGRAM_ADDRESS);
    m_PC = CHIP8_PROGRAM_ADDRESS;
}


void Chip8::chip8_do_instruction(unsigned short opcode)
{
    switch(opcode)
    {

        //Clear The Screen
        case 0x00E0:
            m_chip_screen->chip8_screen_clear();
            break;
        // Return into a subroutine
        case 0x00EE:
            m_PC = m_stack->chip8_stack_pop();
            break;
        default:
            chip8_do_extended_instruction(opcode);
        
    }
}

char Chip8::chip8_wait_for_key_press()
{
    SDL_Event event;
    char c = 0;
    bool a = false;
    while(!a)
    {
        while(SDL_WaitEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                c = event.key.keysym.sym;
                c = m_chip_keyboard->chip8_keyboard_map(c);
                a = true;
                break;
            }


        }
    }


    return c;

}


void Chip8::chip8_do_extended_0xF000_instruction(unsigned short opcode)
{
    unsigned char x = (opcode >> 8) & 0x000f;
    switch(opcode & 0x00FF)
    {
        case 0x07:
        {
            (*m_chip_register)[x] = m_delay_timer;
        }
        break;
        case 0x0A:
        {
            char pressed_key = chip8_wait_for_key_press();
            (*m_chip_register)[x] = pressed_key;
        }
        break;
        case 0x15:
        {
            m_delay_timer = (*m_chip_register)[x];
        }
        break;
        case 0x18:
        {
            m_sound_timer =  (*m_chip_register)[x];
        }
        break;
        case 0x1e:
        {
            (*m_chip_register).set_i((*m_chip_register).get_i() + (*m_chip_register)[x]);
        }
        break;
        case 0x29:
        {
            (*m_chip_register).set_i((*m_chip_register)[x] * CHIP8_DEFAULT_SPRITE_HEIGHT);
        }
        break;
        case 0x33:
            {
                unsigned char hundreds = (*m_chip_register)[x]/100;
                unsigned char tens = (*m_chip_register)[x]/10 % 10;
                unsigned char units = (*m_chip_register)[x] % 10;
                chip8_memory_set((*m_chip_register).get_i(),hundreds);
                chip8_memory_set((*m_chip_register).get_i()+1,tens);
                chip8_memory_set((*m_chip_register).get_i()+2,units);


            }
        break;
        case 0x55:
            {
                for(int i = 0; i <= x ; i++){
                    chip8_memory_set((*m_chip_register).get_i()+i,(*m_chip_register)[i]);
                }
            }
        break;
        case 0x65:
            {
                for(int i = 0 ; i <= x; i++){
                    (*m_chip_register)[i] = chip8_memory_get((*m_chip_register).get_i()+i);
                }
            }
        break;
    }
}

void Chip8::chip8_do_extended_0x8000_instruction(unsigned short opcode)
{
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char final_four_bits = opcode & 0x000f;
    unsigned short tmp = 0;
    switch(final_four_bits){
        //vx = vy
        case 0x00:
        {
            (*m_chip_register)[x] = (*m_chip_register)[y];
            break;
        }
        // VX = Vx | Vy
        case 0x01:
        {
            (*m_chip_register)[x] = (*m_chip_register)[x] | (*m_chip_register)[y];
            break;
        }
        // VX = VX & VY
        case 0x02:
        {
            (*m_chip_register)[x] =  (*m_chip_register)[x] & (*m_chip_register)[y];
            break;
        }
        // VX = VX XOR VY
        case 0x03:
        {
            (*m_chip_register)[x] = (*m_chip_register)[x] ^ (*m_chip_register)[y];
            break;
        }
        // VX = VX + VY SET VF = CARRY
        case 0x04:
        {
            tmp = (*m_chip_register)[x] + (*m_chip_register)[y];
            (*m_chip_register)[0x0f] = 0;
            if(tmp > 0xff)
            {
                (*m_chip_register)[0x0f] = 1;
            }
            (*m_chip_register)[x] = tmp;
            break;
        }
        case 0x05:
        {
            (*m_chip_register)[0x0f] = 0;
            if((*m_chip_register)[x] > (*m_chip_register)[y])
            {
                (*m_chip_register)[0x0f] = 1;
            }
            (*m_chip_register)[x] = (*m_chip_register)[x] - (*m_chip_register)[y];
            break;
        }

        // SHR VX (VY)
        case 0x06:
        {
            (*m_chip_register)[0x0f] = (*m_chip_register)[x] & 0x01;
            (*m_chip_register)[x] /= 2;
            break;
        }

        case 0x07:
        {
            (*m_chip_register)[0x0f] = (*m_chip_register)[y] > (*m_chip_register)[x];
            (*m_chip_register)[x] = (*m_chip_register)[y] - (*m_chip_register)[x]; 
            break;
        }

        case 0x0E:
        {
            (*m_chip_register)[0x0f] = (*m_chip_register)[x] & 0b10000000;
             (*m_chip_register)[x] = (*m_chip_register)[x] * 2;
            break;
        }



    }
}

void Chip8::chip8_do_extended_instruction(unsigned short opcode)
{
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    unsigned char n = opcode & 0x000f;
    switch(opcode & 0xf000)
    {
        //jump
        case 0x1000:
        {
            m_PC = nnn;
            break;
        }
        //call 
        case 0x2000:
        {
            m_stack->chip8_stack_push(m_PC);
            m_PC = nnn;
            break;
        }
        //SE
        case 0x3000:
        {
            if((*m_chip_register)[x] == kk){
                m_PC += 2;
            }
            break;
        }
        //SNE
        case 0x4000:
        {
            if((*m_chip_register)[x] != kk){
                m_PC += 2;
            }
            break;
        }
        case 0x5000:
        {
            if((*m_chip_register)[x] == ((*m_chip_register)[y])){
                m_PC += 2;
            }
            break;
        }
        case 0x6000:
        {
            (*m_chip_register)[x] = kk;
            break;
        }
        case 0x7000:
        {
            (*m_chip_register)[x] = (*m_chip_register)[x] + kk;
            break;
        }
        case 0x8000:
        {
            chip8_do_extended_0x8000_instruction(opcode);
            break;
        }
        case 0x9000:
        {
            if((*m_chip_register)[x] != (*m_chip_register)[y]){
                m_PC += 2;
            }
            break;
        }
        case 0xA000:
        {
            (*m_chip_register).set_i(nnn);
            break;
        }
        case 0xB000:
        {
            m_PC = nnn + (*m_chip_register)[0x00];
            break;
        }
        case 0xC000:
        {
            srand(clock());
            (*m_chip_register)[x] = (rand() % 255) & kk;
            break;
        }
        case 0xD000:
        {
            const char* sprite = (const char*) &(*m_chip_memory)[m_chip_register->get_i()];
            (*m_chip_register)[0x0f] =  m_chip_screen->chip8_screen_draw_sprite((*m_chip_register)[x],(*m_chip_register)[y],sprite, n);
            break;
        }  
        case 0xE000:   
        {
            switch(opcode & 0x00ff)
            {
                case 0x9e:
                {
                    if(m_chip_keyboard->chip8_keyboard_is_down((*m_chip_register)[x])){
                        m_PC += 2;
                    }
                    break;
                }


                case 0xa1:
                {
                    if(!m_chip_keyboard->chip8_keyboard_is_down((*m_chip_register)[x])){
                        m_PC += 2;
                    }
                    break;
                }

            }
            break;
        }
        case 0xF000:
        {
            chip8_do_extended_0xF000_instruction(opcode);
            break;
        }

    }
}


void Chip8::chip8_memory_set(int index, unsigned char val)
{
    (*m_chip_memory)[index] = val;    
}

unsigned char Chip8::chip8_memory_get(int index)
{
    return (*m_chip_memory)[index];
}