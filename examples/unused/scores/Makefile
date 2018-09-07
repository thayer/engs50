# Makefile for 'scores' example
#
# David Kotz, April 2016

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
LIBS =

test: scores1 scores2
	@echo ==== scores1 ====
	./scores1 < games.txt
	@echo ==== scores2 ====
	./scores2 < games.txt
	@echo ====  ====

scores1: scores1.o reader.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

scores2: scores2.o reader.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

scores1.o: reader.h
scores2.o: reader.h
reader.o: reader.h

clean:
	rm -f *~
	rm -f *.o
	rm -f scores1 scores2
