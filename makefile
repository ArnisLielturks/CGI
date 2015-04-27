#Compiler to use
CC=g++

all:
	$(CC) *.cpp -lfcgi++ -lfcgi -o main.o
clean:
	rm *.o
