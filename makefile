# Archivo: makefile

CC = g++
FLAGS = -W -Wall -g -pedantic

all: ejec clear

ejec: main.o Cmdline.o ArrayDouble.o Error.o Package.o Red.o Utils.o
	$(CC) $(FLAGS) -o ejec main.o Cmdline.o ArrayDouble.o Error.o Package.o Red.o Utils.o

main.o: main.cpp Cmdline.hpp Red.hpp Utils.hpp Error.hpp
	$(CC) $(FLAGS) -o main.o -c main.cpp

Cmdline.o: Cmdline.cpp Cmdline.hpp
	$(CC) $(FLAGS) -o Cmdline.o -c Cmdline.cpp

ArrayDouble.o: ArrayDouble.cpp ArrayDouble.hpp
	$(CC) $(FLAGS) -o ArrayDouble.o -c ArrayDouble.cpp

Error.o: Error.cpp Error.hpp
	$(CC) $(FLAGS) -o Error.o -c Error.cpp

Package.o: Package.cpp Package.hpp
	$(CC) $(FLAGS) -o Package.o -c Package.cpp

Red.o: Red.cpp Red.hpp Package.hpp ArrayDouble.hpp
	$(CC) $(FLAGS) -o Red.o -c Red.cpp

Utils.o: Utils.cpp Utils.hpp Red.hpp Error.hpp Package.hpp
	$(CC) $(FLAGS) -o Utils.o -c Utils.cpp



clear:
	rm *.o


