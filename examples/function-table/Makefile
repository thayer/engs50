# Makefile for function-table example
#
# David Kotz, May 2016

PROGS = fntable
LIBS = 
LLIBS = 

FLAGS = # 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### inclient ##################
fntable: fntable.o file.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

fntable.o: file.h
file.o: file.h

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 
