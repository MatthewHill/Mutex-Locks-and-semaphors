CC=g++
CFLAGS=-std=c++11 -Wall
OUTPUTNAME=producer_consumer2

all: Pro3P1
	g++ -std=c++11 Pro3P2.o -pthread -o $(OUTPUTNAME)
Pro3P1: Pro3P2.cpp
	$(CC) $(CFLAGS) -c Pro3P2.cpp
clean:
	rm *.o
	rm $(OUTPUTNAME)