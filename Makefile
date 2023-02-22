CC=gcc
AR=ar
TARGET=output
CFLAGS= -Wall -pedantic -Wextra

all: prog.o ringbuf.o
	$(CC) $(CFLAGS) prog.o ringbuf.o -o $(TARGET)

prog.o: prog.c
	$(CC) $(CFLAGS) -c prog.c

ringbuf.a: ringbuf.o
	$(AR) rc $@ $^

ringbuf.o: ringbuf.c ringbuf.h
	$(CC) $(CFLAGS) -c ringbuf.c

clean:
	rm -f *.c *.a $(TARGET)

