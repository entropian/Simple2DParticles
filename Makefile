CC=g++
LFLAGS = -lGL -lGLEW -lglfw -lGLU -lpthread 
CFLAGS = -std=c++11 -c

OS = $(shell uname)

all:
		$(CC) -g -o test main.cpp canvas.cpp $(LFLAGS)
