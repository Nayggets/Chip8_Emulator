#include "Chip8.hpp"
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("You must provide a file to load\n");
        return -1;
    }

    const char* filename = argv[1];
    printf("The filename to load is: %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        printf("Failed to open the file");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char buf[size];
    int res = fread(buf, size, 1, f);
    if (res != 1)
    {
        printf("Failed to read from file");
        return -1;
    }

    for(int i = 0 ; i < size ; i = i +2){
        std::cout << std::hex << (short) ((unsigned char)buf[i] << 8 | (unsigned char)buf[i+1])  << std::endl;
    }


    Chip8 chip8{};
    chip8.run(buf,size);
    
}