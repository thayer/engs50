# Makefile for 'cs50ds' library
#   Builds and compiles all the data structures into a library.
#
# David Kotz, April 2016, 2017

# our library and the object files we want to include in it
LIB = cs50ds.a
OBJS = bag/bag.o set/set.o counters/counters.o \
	hashtable/hashtable.o hashtable/jhash.o \
  common/readlinep.o

# uncomment the following to turn on verbose memory logging
# (and run `make clean; make` whenever you change this)
# TESTING=-DMEMTEST

# Our compiler and its flags
CC = gcc
MAKE = make TESTING=$(TESTING)
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)

# make the library from the objects - but first make all those
$(LIB): all
	ar cr $@ $(OBJS)

# recursively make in each subdirectory
all:
	$(MAKE) --directory=bag
	$(MAKE) --directory=counters
	$(MAKE) --directory=set
	$(MAKE) --directory=hashtable
	$(MAKE) --directory=common

# 'phony' targets are helpful but do not create any file by that name
.PHONY: clean starter

# for instructor use only
STARTERS=Makefile common bag hashtable/jhash.[ch]
STARTDIR=../../../website/Labs/Lab3/starter
starter: clean
	rsync -ravR --delete $(STARTERS) $(STARTDIR)
	git add $(STARTDIR)

# to clean up all derived files
clean:
	rm -f *~
	rm -f $(LIB)
	make --directory=bag clean
	make --directory=set clean
	make --directory=counters clean
	make --directory=hashtable clean
	make --directory=common clean
