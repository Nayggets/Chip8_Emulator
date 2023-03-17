CXX = g++
LANG_STD = -std=c++2a
COMPILE_FLAGS = -g -O3 -Os
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
APP_NAME = 8_Chip
SRC_FILES = src/*.cpp

build:
	$(CXX)	$(LANG_STD) $(COMPILE_FLAGS) $(SRC_FILES) $(LDFLAGS) -o $(APP_NAME)


test:
	$(CXX)	$(LANG_STD) $(COMPILE_FLAGS) ./src/mainTest.cpp ./src/Chip8Keyboard.cpp ./src/Chip8Keyboard.hpp $(LDFLAGS) -o $(APP_NAME)


clean:
	rm 8_Chip

run:
	make
	./8_Chip

run_without_build:
	./8_Chip