CC=g++
CFLAGS=-std=c++11 -Wall
OUTPUTNAME=Producer_Consumer1

all: Pro3P1
	g++ -std=c++11 Pro3P1.o  -pthread -o $(OUTPUTNAME)
Pro3P1: Pro3P1.cpp
	$(CC) $(CFLAGS) -c Pro3P1.cpp
clean:
	rm *.o
	rm $(OUTPUTNAME)