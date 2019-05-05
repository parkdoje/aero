#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/i2c.h"
#include "../include/mpu9250.h"

int main()
{
    i2c_dev_t* i2c = init_i2c("/dev/i2c-1");
    mpu9250_t* mpu = init_mpu9250(i2c, 0x04);
    accel_data_t data;
    while(1)
    {
        read_accel_data(mpu, &data);
        printf("%f, %f, %f\n", data.a_x, data.a_y, data.a_z);
        usleep(100* 1000);
    }
    read_accel_data(mpu, &data);
    return 0;
}