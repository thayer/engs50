# Makefile for UDP socket examples
#
# David Kotz, May 2016

PROGS = udpclient udpserver
LIBS = 
LLIBS = 

FLAGS = # 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

all: $(PROGS)

########### udpclient ##################
udpclient: udpclient.o file.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

udpclient.o: file.h

########### udpserver #################
udpserver: udpserver.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

udpserver.o: 

clean:
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS) 
