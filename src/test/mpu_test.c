#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/i2c.h"
#include "../include/mpu9250.h"

int main()
{
    i2c_dev_t* i2c = init_i2c("/dev/i2c-1");
    mpu9250_t* mpu = init_mpu9250(i2c, 0);
    data_t acc;
    data_t gy;
    while(1)
    {
        read_accel_data(mpu, &acc);
        read_gyro_data(mpu, &gy);
        printf("acc: %f, %f, %f\t", acc.x, acc.y, acc.z);
        printf("gyro: %f, %f, %f\n ", gy.x, gy.y, gy.z);
        usleep(100* 1000);
    }
    return 0;
}