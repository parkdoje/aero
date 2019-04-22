#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/i2c.h"



i2c_dev_t* init_i2c(i2c_dev_t* self, const char* device_name)
{
	int fd = open_device(device_name);
	if(fd < 0) 
		return NULL;

	comm_device_t* super = &self->super;

	super->read_byte = i2c_read_byte;
	super->read_nbyte = NULL;

	super->write_byte = i2c_write_byte;
	super->write_nbyte = NULL;



	
}

int open_device(const char* device_name)
{
	int fd;
	fd = open(device_name, O_RDWR);
	if(fd < 0)
	{
		return -1; 
	}
	if( check_functions(fd) != 0)
		return -1;
	return fd;
}

static int check_functions(int fd)
{
	unsigned long funcs;
	int func_list[7] = { I2C_FUNC_SMBUS_QUICK, I2C_FUNC_SMBUS_READ_BYTE, I2C_FUNC_SMBUS_WRITE_BYTE,
						I2C_FUNC_SMBUS_READ_BYTE_DATA, I2C_FUNC_SMBUS_WRITE_BYTE_DATA, I2C_FUNC_SMBUS_READ_WORD_DATA,
						I2C_FUNC_SMBUS_WRITE_WORD_DATA 
						};
	if(ioctl(fd, I2C_FUNCS, &funcs) < 0) // get the functions
		return -1;
	for(int i = 0; i < 7; i++)
	{
		if(!(funcs & func_list[i])) // check all functions are usable
			return -1;
		printf("%d is ok!\n", i);
	}

	return 0;
}


static inline int i2c_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data* data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = rw;
	args.command = command;
	args.size = size;
	args.data = data;
	return ioctl(fd, I2C_SMBUS, &args);
}

static int set_address(int fd, int addr)
{
	if (ioctl(fd, I2C_SLAVE, addr) < 0)
	{
		return -1;
	}
	return 0;
}

int i2c_read_byte(comm_device_t* self)
{
	union i2c_smbus_data data;
	if( i2c_access(self->fd, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
		return -1;
	return data.byte & 0xFF;
}

int i2c_write_byte(comm_device_t* self, uint8_t value)
{
	union i2c_smbus_data data;
	data.byte = value;

	return i2c_access(self->fd, I2C_SMBUS_WRITE, value, I2C_SMBUS_BYTE, NULL);
}

int i2c_read_byte_reg(comm_device_t* self, uint8_t reg)
{
	union i2c_smbus_data data;
	if(i2c_access(self->fd, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
		return -1;
	return data.byte & 0xFF;
}

int i2c_read_nbyte_reg(comm_device_t* self, uint8_t reg, size_t len, uint8_t* buffer)
{
	union i2c_smbus_data data;
	if (len != 2)
		return -1;

	if(i2c_access(self->fd, I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
		return -1;
	memcpy(buffer, &data.word, 2);
	return 2;
}

int i2c_write_byte_reg(comm_device_t* self, uint8_t reg, uint8_t data)
{
	union i2c_smbus_data packet;

	packet.byte = data;

	return i2c_access(self->fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &packet);
}

int i2c_write_nbyte_reg(comm_device_t* self, uint8_t reg, size_t len, uint8_t* buffer)
{
	union i2c_smbus_data packet; 

	memcpy(&(packet.block)+ sizeof(uint8_t), buffer, len);
	packet.block[0] = len;

}





	
	
	


