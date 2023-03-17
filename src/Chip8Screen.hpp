#include "config.hpp"
class Chip8Screen
{
    public:
        Chip8Screen();
        ~Chip8Screen();
        void chip8_screen_set(int x,int y);
        bool chip8_screen_is_set(int x, int y);
        bool chip8_screen_draw_sprite(int x, int y, const char* sprite, int num);
        void chip8_screen_clear();
    private:
        bool m_screen[CHIP8_HEIGHT][CHIP8_WIDTH];
};