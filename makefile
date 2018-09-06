# Archivo: makefile

CC = g++
FLAGS = -W -Wall -g -pedantic

all: ejec clear

ejec: main.o Cmdline.o 
	$(CC) $(FLAGS) -o ejec main.o Cmdline.o 

main.o: main.cpp Cmdline.hpp
	$(CC) $(FLAGS) -o main.o -c main.cpp

Cmdline.o: Cmdline.cpp Cmdline.hpp
	$(CC) $(FLAGS) -o Cmdline.o -c Cmdline.cpp




clear:
	rm *.o


