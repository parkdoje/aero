CC = gcc

SRCS = serial.c i2c.c list.c
LIBS = -lpthread

TARGET = rocket

.SUFFIXES : .c .o

all: serial.o i2c.o 


serial.o: serial.c
	$(CC) $(CFLAGS)-o serial.o serial.c

i2c.o : i2c.c
	$(CC) $CFLAGS -o i2c.o i2c.c 



