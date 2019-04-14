#include "comm_device.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <stdint.h>



int open_device(const char* device_name);
static int check_functions(int fd);
static int set_address(int fd, int addr);
static inline int i2c_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data* data);

int i2c_read_byte(int fd, int addr); // return 8bit data 
int i2c_read_word(int fd, int addr); // return 16bit data
int i2c_read_block(int fd, int addr, uint8_t* buffer);

int i2c_write_byte(int, int, uint8_t);
int i2c_write_word(int, int, uint16_t);
int i2c_write_block(int fd, int addr, uint8_t* buffer, size_t size);

 








