#include "comm_device.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <stdint.h>









int open_device(const char* device_name);
int set_address(int fd, int addr);//need check
static inline int i2c_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data* data);//need check

int i2c_read_byte(int fd, int addr); // return 8bit data 
int i2c_read_word(int fd, int addr); // return 16bit data

int i2c_write_byte(int fd, int addr, uint8_t data);
int i2c_write_word(int fd, int addr, uint16_t data);
int i2c_write_block(int fd, int addr, uint8_t* buffer, size_t size);

 








