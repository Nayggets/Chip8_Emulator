#include "config.hpp"
class Chip8Keyboard
{
    public:
    Chip8Keyboard();
    ~Chip8Keyboard();
    int chip8_keyboard_map(char key);
    void chip8_keyboard_down(unsigned char key);
    void chip8_keyboard_up(unsigned char key);
    bool chip8_keyboard_is_down(unsigned char key);
    private:
        bool m_keyboard[CHIP8_TOTAL_KEYS];
        char m_keyboard_map[CHIP8_TOTAL_KEYS];
};