#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdint.h>

enum comm_type 
{
	I2C, 
	UART,
	SERIAL_USB,
	NON
};

struct comm_device
{
    int fd;
	enum comm_type type;

    pthread_mutex_t comm_lock;

	int (*open_comm)();
	void (*close_comm)(struct comm_device*);
	void (*data_flush)(int);

	int (*read_byte)(int fd);
	int (*read_nbyte)(int fd, size_t size);

	int (*read_byte_reg)(int fd, int addr);
	int (*read_nbyte_reg)(int fd, int addr, int size, uint8_t* buffer);

	void (*write_byte)(int fd, int addr, uint8_t data);
	void (*write_nbyte)(int fd, int addr, int count, uint8_t* buffer);
};
	
