#pragma once

#include <string>
#include <iostream>
static std::string EMULATOR_WINDOW_TITLE = "Chip8 Emulator";
static const int CHIP8_MEMORY_SIZE = 4096;
static const char CHIP8_WIDTH = 64;
static const char CHIP8_HEIGHT = 32;
static const char CHIP8_WINDOW_MULTIPLIER = 10;
static const char CHIP8_TOTAL_DATA_REGISTERS = 16;
static const char CHIP8_TOTAL_STACK_DEPTH = 16;
static const char CHIP8_TOTAL_KEYS = 16;
static const char CHIP8_CHARACTER_SET_LOAD_ADDRESS = 0x00;
static const int CHIP8_PROGRAM_ADDRESS = 0x200;
static const int CHIP8_DEFAULT_SPRITE_HEIGHT = 5;