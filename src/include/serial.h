#pragma once
#include "comm_device.h"
#include "../lib/attr.h"
#include <termios.h>


typedef struct 
{
    comm_device_t super;
    speed_t baud;

    void (*data_flush)(struct serial_dev_t* self);
}serial_dev_t;


int serial_open(const char*, int);
void close_serial(struct comm_device*);

void data_flush(serial_dev_t* self);

int serial_read(serial_dev_t* self);
int serial_nread(serial_dev_t* self, size_t len, uint8_t* buffer);

void serial_write(serial_dev_t* self, uint8_t data);
void serial_nwrite(serial_dev_t* self, size_t len, uint8_t* buffer);














