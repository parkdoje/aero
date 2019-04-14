#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/i2c.h"

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
		//error
		return -1;
	}
	return 0;
}

int i2c_read_byte(int fd, int addr)
{
	union i2c_smbus_data data;
	if( i2c_access(fd, I2C_SMBUS_READ, addr, I2C_SMBUS_BYTE_DATA, &data))
		return -1;
	
	return data.byte & 0xFF;
}
int i2c_read_word(int fd, int addr)
{
	union i2c_smbus_data data;

	if (i2c_access(fd, I2C_SMBUS_READ, addr, I2C_SMBUS_WORD_DATA, &data))
		return -1;
	return data.word & 0xFFFF;
}
int i2c_read_block(int fd, int addr, uint8_t* buffer)
{
	union i2c_smbus_data data;

	int len = i2c_access(fd, I2C_SMBUS_READ, addr, I2C_SMBUS_BLOCK_DATA, &data);
	memcpy(buffer, &(data.block) + sizeof(uint8_t), len);

	return len;
}

int i2c_write_byte(int fd, int addr, uint8_t val)
{
	union i2c_smbus_data data;
	data.byte = val;

	return i2c_access(fd, I2C_SMBUS_WRITE, addr, I2C_SMBUS_BYTE_DATA, &data);
}

int i2c_write_word(int fd, int addr, uint16_t val)
{
	union i2c_smbus_data data;
	data.word = val;

	return i2c_access(fd, I2C_SMBUS_WRITE, addr, I2C_SMBUS_WORD_DATA, &data);
}

int i2c_write_block(int fd, int addr, uint8_t* buffer, size_t size)
{
	union i2c_smbus_data data;
	memcpy(data.block + sizeof(uint8_t), buffer, size);
	data.block[0] = size;

	return i2c_access(fd, I2C_SMBUS_WRITE, addr, I2C_SMBUS_BLOCK_DATA, &data);
}




	
	
	


