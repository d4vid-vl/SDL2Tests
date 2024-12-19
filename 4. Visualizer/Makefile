BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)
HEADER_FILES = $(wildcard src/headers/*.cpp)
OBJ_NAME = jogo
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.8/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib/
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g
LINKER_FLAGS = -lsdl2 -lsdl2_image

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(HEADER_FILES) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
