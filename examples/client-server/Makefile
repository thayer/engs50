# Makefile for socket examples
#
# David Kotz, May 2016

PROGS = inclient inserver
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
inclient: inclient.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

inclient.o: 

########### inserver #################
inserver: inserver.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

inserver.o: 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 
