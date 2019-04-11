#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum comm_type 
{
	I2C, 
	UART,
	SERIAL,
	NON
};

struct comm_device
{
	enum comm_type type;
	int fd;
	int (*open_comm)();
	void (*close_comm)(struct comm_device*);

	void (*data_flush)(int);

	int (*read_byte)(int, int);
	int (*read_nbyte)(int, int, int, char*);

	void (*write_byte)(int, int, char);
	void (*write_nbyte)(int, int, int, char*);
};
	
