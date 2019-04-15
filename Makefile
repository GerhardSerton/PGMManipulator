#Makefile
#Pieter Gerhard Serton
#27/03/19

CC=g++

Driver: Image.o Driver.o
	$(CC) -o Driver Driver.o Image.o

Driver.o: Driver.cpp
	$(CC) -c -o Driver.o Driver.cpp

Image.o: Image.cpp
	$(CC) -c -o Image.o Image.cpp

clean:
	@rm -f *.o

debug: Image.o Driver.o
	$(CC) -g Driver.cpp Image.cpp -o debug
