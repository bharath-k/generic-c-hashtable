#
# Makefile
# TODO: This isn't a well written make file. Please rewrite.
#

EXTRACFLAGS=
EXTRALDFLAGS=
APR_LIBS:=$(shell apr-1-config --link-ld)
INCDIR= -I.
LIBDIR=/usr/lib64
LIBS=-L$(LIBDIR) $(APR_LIBS) $(EXTRALDFLAGS)
OPTFLAGS=-g
CFLAGS=$(OPTFLAGS) $(INCDIR) $(EXTRACFLAGS)
CC=gcc
all: main.o generichash.o
	$(CC) --std=c99  -o main main.o generichash.o -Wl,-rpath,.:/usr/lib64 $(LIBS)
main.o: main.c
	$(CC) $(INCDIR) -g -O -c main.c
generichash.o: generichash.c
	$(CC) $(INCDIR) -g -O -c generichash.c
clean:
	/bin/rm -f $(PROGS) *.o *.out core main
dos2unix:
	/usr/bin/dos2unix *.c include/*.h Makefile
