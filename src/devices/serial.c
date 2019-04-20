#include "../include/serial.h"
#include <stdio.h>
#include <stdlib.h>
#include "../lib/debug.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>



int init_serial(struct comm_device* self, char* serial_name, int baudrate)
{
	self->fd = serial_open(serial_name, baudrate);

	self->read_byte = serial_read;
	self->read_nbyte = serial_nread;
	
	self->write_byte = serial_write;
	self->write_nbyte = serial_nwrite;

	self->data_flush = data_flush;
	
	self->close_comm = close_serial;
	self->open_comm = open_serial;
	return 0;
}
int open_serial()
{
	printf("unimplemented function call! exit!\n");
	exit(1);
}
void close_serial(struct comm_device* self)
{
	close(self->fd);
	free(self);
	self = NULL;
}

int serial_open(const char* name, int baudrate)
{
	struct termios options;
	speed_t baud;
	int stat, fd;
	
	switch(baudrate)
	{
		case 9600: baud = B9600; break;
		case 19200: baud = B19200; break;
		case 38400: baud = B38400; break;
		case 57600: baud = B57600; break;
		case 115200: baud = B115200; break;
		case 230400: baud = B230400; break;
		
		default:
 			return -2;
	}
	fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		printf("fd: %d\n", fd);
		return -1;
	}

	if (tcgetattr(fd, &options) == -1)
	{
        int e = errno;
		printf("failed to get option!\n");
		printf("errno %d from tcgetattr\n", e);
	}

	cfmakeraw(&options);
	cfsetispeed(&options, baud);
	cfsetospeed(&options, baud);

    //set terminal to raw mode 
	options.c_lflag &= ~(ICANON | ECHO | ECHOE| ISIG);
    options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);

	options.c_cflag |= (CLOCAL | CREAD);
	//options.c_cflag &= ~PARENB;
	options.c_cflag &= ~(CSTOPB | CSIZE);
	options.c_cflag |= CS8;

	options.c_oflag &= ~OPOST;


    // set serial io as non blocking mode	
	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 10;

	tcsetattr(fd, TCSANOW, &options);

	ioctl (fd, TIOCMGET, &stat);

	stat |= TIOCM_DTR;
	stat |= TIOCM_RTS;

	ioctl(fd, TIOCMSET, &stat);

    usleep(10000);
	return fd;
}


int serial_read(int fd, int addr UNUSED)
{
	int received;
	read(fd, &received, 1);
	return received;
}

int serial_nread(int fd, int addr UNUSED, int count, uint8_t* buffer)
{
	int received = read(fd, (void*)buffer, count);
	return received;
}

void serial_write(int fd, int addr, uint8_t data)
{
	write(fd, &data, 1);
}

void serial_nwrite(int fd, int addr, int count, uint8_t* data)
{
	write(fd, data, count);
}

void data_flush(int fd)
{
	tcflush(fd, TCIOFLUSH);
}
