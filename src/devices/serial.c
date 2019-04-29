#include "../include/serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../lib/debug.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>



serial_dev_t* init_serial(char* serial_name, int baudrate)
{
	comm_device_t* super = malloc(sizeof(serial_dev_t));
	serial_dev_t* self = (serial_dev_t*)super;

	super->fd = serial_open(serial_name, baudrate);
	super->type = UART;
	super->comm_lock =(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

	super->read_byte = serial_read;
	super->read_nbyte = serial_nread;

	super->write_byte = serial_write;
	super->write_nbyte = serial_nwrite;

	self->data_flush =data_flush;

	return 0;
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


int serial_read(serial_dev_t* self)
{
	int received;
	read(self->super.fd, &received, 1);
	return received;
}

int serial_nread(serial_dev_t* self, size_t len, uint8_t* buffer)
{
	int received = read(self->super.fd, (void*)buffer, len);
	return received;
}

void serial_write(serial_dev_t* self, uint8_t data)
{
	write(self->super.fd, &data, 1);
}

void serial_nwrite(serial_dev_t* self, size_t len, uint8_t* buffer)
{
	write(self->super.fd, buffer, len);
}

void data_flush(serial_dev_t* self)
{
	tcflush(self->super.fd, TCIOFLUSH);
}
