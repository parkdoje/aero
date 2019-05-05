#include <stdio.h>
#include <stdlib.h>
#include "../include/i2c.h"
#include "../include/mpu9250.h"

int main()
{
    i2c_dev_t* i2c = init_i2c("/dev/something");
    mpu9250_t* mpu = init_mpu9250(i2c, 100);

    read_accel_data(mpu);
    return 0;
}