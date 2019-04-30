#include "../include/mpu9250.h"
#include "../lib/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void _init_mpu9250(mpu9250_t* self)
{


}


mpu9250_t* init_mpu9250(i2c_dev_t* i2c ,uint8_t acc_scale, uint8_t gy_scale, uint8_t sample_rate)
{
    mpu9250_t* self = malloc(sizeof(mpu9250_t));
    sensor_t* super = &self->super;

    list_init(&super->buffer_head);
    super->comm = i2c;
    super->sensor_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    super->rate = sample_rate;
    super->device_addr = MPU9250_ADDR;

    self->accel_factor = acc_scale;
    self->gyro_factor = gy_scale;

}

