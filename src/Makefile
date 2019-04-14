CC = gcc

SRCS = serial.c
OBJS = $(SRCS:%.c=$.o)
LIBS = -lpthread

TARGET = rocket

.SUFFIXES : .c .o

all: $(TARGET)

depend:
		gccmakedep $(SRCS)

$(TARGET) : $(OBJS)
		$(CC) -o $@ $(OBJS)


serial.o: serial.h serial.c
	gcc -o serial.o serial.c

