CC=g++
CFLAGS=-I

hellomake: image.o utility2.o mainTest.o
	$(CC) -o main image.cpp utility2.cpp mainTest.cpp -I.
