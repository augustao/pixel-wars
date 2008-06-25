# test makefile

CC=gcc
CXX=g++
CFLAGS=-Wall `sdl-config --cflags` -O3
FILES=src/glSDL.c src/main.cpp src/timer.cpp src/GS_memory.cpp src/text_manager.cpp src/audio.cpp 
TARGET=main
LIBS=`sdl-config --libs` -lstdc++ -lGL -lSDL_image -lSDL_mixer -lSDL_ttf

all:
	$(CXX) $(CFLAGS) $(FILES) -o $(TARGET) $(LIBS)
