#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../lib/debug.h"
#include "../include/i2c.h"



i2c_dev_t* init_i2c(const char* device_name)
{
	int fd = open_device(device_name);
	if(fd < 0) 
	{
		return NULL;
	}

	comm_device_t* super = (comm_device_t*)malloc(sizeof(i2c_dev_t));
	i2c_dev_t* self = (i2c_dev_t*)super;
	super->fd = fd;
	super->comm_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	super->type = I2C;
	super->read_byte = (
		check_functions(super->fd, I2C_FUNC_SMBUS_READ_BYTE) 
				? i2c_read_byte : NULL);
	super->read_nbyte = NULL;
	super->write_byte = (
		check_functions(super->fd, I2C_FUNC_SMBUS_WRITE_BYTE) 
				? i2c_write_byte : NULL);
	super->write_nbyte = NULL;
	super->close_device = close_device;

	self->dev_addr = 0x00;
	self->read_byte_reg = (
		check_functions(super->fd, I2C_FUNC_SMBUS_READ_BYTE_DATA)
			? i2c_read_byte_reg : NULL);
	self->read_nbyte_reg = (
		check_functions(super->fd, I2C_FUNC_SMBUS_READ_WORD_DATA) 
			? i2c_read_nbyte_reg : NULL);
	self->write_byte_reg = (
		check_functions(super->fd, I2C_FUNC_SMBUS_WRITE_BYTE_DATA) 
			? i2c_write_byte_reg : NULL);
	self->write_nbyte_reg = (
		check_functions(super->fd, I2C_FUNC_SMBUS_WRITE_BLOCK_DATA) 
			? i2c_write_byte_reg : NULL);
	self->set_addr = set_address;
	self->get_addr = get_address;
	self->write_bit_reg = (
		self->write_byte_reg != NULL ? i2c_write_bit_reg : NULL);
	return self;

}

int set_address(i2c_dev_t* self, int addr)
{
	ASSERT(self->super.type == I2C);

 	if(ioctl(self->super.fd, I2C_SLAVE, addr) < 0)
	 	return -1; 
	self->dev_addr = addr;
	return 0;
}
uint8_t get_address(i2c_dev_t* self)
{
	ASSERT(self->super.type = I2C);
	return ((i2c_dev_t*)self)->dev_addr;
}

int open_device(const char* device_name)
{
	int fd;
	fd = open(device_name, O_RDWR);
	if(fd < 0)
	{
		return -1; 
	}
	return fd;
}

int close_device(i2c_dev_t* _self)
{
	ASSERT(_self->super.type = I2C);
	i2c_dev_t* self = (i2c_dev_t*)_self;
	free(self);
}

static int check_functions(int fd, unsigned int func_code)
{
	unsigned long funcs;

	if(ioctl(fd, I2C_FUNCS, &funcs) < 0) // get the functions
		return -1;

	return (func_code & funcs);
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

int i2c_read_byte(i2c_dev_t* self)
{
	
	union i2c_smbus_data data;
	if( i2c_access(self->super.fd, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
		return -1;
	return data.byte & 0xFF;
}

int i2c_write_byte(i2c_dev_t* self, uint8_t value)
{
	union i2c_smbus_data data;
	data.byte = value;

	return i2c_access(self->super.fd, I2C_SMBUS_WRITE, value, I2C_SMBUS_BYTE, NULL);
}

int i2c_read_byte_reg(i2c_dev_t* self, uint8_t reg)
{
	union i2c_smbus_data data;
	if(i2c_access(self->super.fd, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
		return -1;
	return data.byte & 0xFF;
}

int i2c_read_nbyte_reg(i2c_dev_t* self, uint8_t reg, size_t len, uint8_t* buffer)
{
	union i2c_smbus_data data;
	if (len != 2)
		return -1;

	if(i2c_access(self->super.fd, I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
		return -1;
	memcpy(buffer, &data.word, 2);
	return 2;
}

int i2c_write_byte_reg(i2c_dev_t* self, uint8_t reg, uint8_t data)
{
	union i2c_smbus_data packet;

	packet.byte = data;

	return i2c_access(self->super.fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &packet);
}

int i2c_write_nbyte_reg(i2c_dev_t* self, uint8_t reg, size_t len, uint8_t* buffer)
{
	union i2c_smbus_data packet; 
	if(len > I2C_SMBUS_BLOCK_MAX)
		return -1;

	memcpy(&(packet.block)+ sizeof(uint8_t), buffer, len);
	packet.block[0] = len;

	return i2c_access(self->super.fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BLOCK_DATA, &packet);
}

int i2c_write_bit_reg(i2c_dev_t* self, uint8_t reg, uint8_t pos, uint8_t len, uint8_t data)
{
	ASSERT(len <= 8);
	ASSERT(pos < 8);
	uint8_t packet = self->read_byte_reg(self, reg);
	uint8_t mask = ((1 << len) -1) << (pos - len + 1); 
	/* 2**n - 1
	 =
	 ....0 1 	1 	1 	1 ...
	     n n-1	n-2 n-3   ...

	ex 
		1111 1011 = original data 
		0000 0111 = mask
		3 = position 
		3 = len 
		we need to move 3rd bit just 1 time to left 		
	*/

	packet &= ~(mask);
	/*
		ex 
		1111 1011 = original
		~(0000 1110) = mask 
		1111 0001 = ~mask

		orignal & ~mask =
		1111 0001 => erase 3bit !
	*/

	packet |= (data) << (pos - len + 1);
	
	return self->write_byte_reg(self, reg, packet);
}


