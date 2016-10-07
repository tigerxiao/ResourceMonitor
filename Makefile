CFLAGS=-s -unaligned_access -Wall -Wno-implicit-function-declaration -O3 -Wl,--hash-style=sysv
LDFLAGS=-lpthread -lrt

COMMON:=$(wildcard ./*.c)
TARGET:=$(COMMON:.c=.o)

CC = gcc

all: clean test
	$(RM) *.o 

test: $(TARGET) 
	$(CC) $^ -o $@ $(LDFLAGS) -lm

clean:
	$(RM) *.o test
