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
	exit(-1);
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
		return -1;

	tcgetattr(fd, &options);
	cfmakeraw(&options);
	cfsetispeed(&options, baud);
	cfsetospeed(&options, baud);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;

	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	options.c_lflag &= ~(ICANON | ECHO | ECHOE| ISIG);
	options.c_oflag &= ~OPOST;
	
	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 0;

	tcsetattr(fd, TCSANOW, &options);

	ioctl (fd, TIOCMGET, &stat);

	stat |= TIOCM_DTR;
	stat |= TIOCM_RTS;
	ioctl(fd, TIOCMSET, &stat);
	return fd;
}


int serial_read(int fd, int addr UNUSED)
{
	int received;
	read(fd, &received,1);
	return received;
}

int serial_nread(int fd, int addr, int count, char* buffer)
{
	int received = read(fd, (void*)buffer, count);
	return received;
}

void serial_write(int fd, int addr, char data)
{
	write(fd, &data, 1);
}

void serial_nwrite(int fd, int addr, int count, char* data)
{
	write(fd, data, count);
}

void data_flush(int fd)
{
	tcflush(fd, TCIOFLUSH);
}
