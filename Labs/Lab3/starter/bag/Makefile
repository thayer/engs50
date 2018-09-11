# Makefile for 'bag' module
#
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016

PROG = bagtest
OBJS = bagtest.o bag.o ../common/readlinep.o ../common/memory.o 
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

bagtest.o: bag.h ../common/readlinep.h
bag.o: bag.h
readline.o: ../common/readlinep.h

.PHONY: test stocks clean

test: $(PROG) stocks
	./$(PROG) < stocks

stocks:
	 curl 'http://download.finance.yahoo.com/d/quotes.csv?s=NKE,AAPL,MCD,TWTR,IBM,YHOO,ORCL,GOOG,MSFT,NFLX,FB&f=spl1v&e=.csv' > stocks

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
