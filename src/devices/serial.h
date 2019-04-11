#include "comm_device.h"
#include "../lib/attr.h"

int init_serial(struct comm_device*, char*, int);

int serial_open(const char*, int);
int open_serial();
void close_serial(struct comm_device*);

void data_flush(int fd);

int serial_read(int fd, int addr UNUSED);
int serial_nread(int fd, int addr UNUSED, int count, char* buffer);

void serial_write(int fd, int addr UNUSED, char data);
void serial_nwrite(int fd, int addr UNUSED, int count, char* buffer);














