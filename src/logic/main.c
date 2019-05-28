#include "../include/i2c.h"
#include "../include/mpu9250.h"
#include "../include/serial.h"
#include "../include/lps25.h"
#include "../include/controller.h"
#include "../include/communication.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>



mpu9250_t* imu = NULL;
i2c_dev_t* i2c = NULL;
serial_dev_t* uart1 = NULL;//for wireless 
serial_dev_t* uart2 = NULL;//for gps
ctrl_t* ctrl = NULL;
rfdev_t* rf = NULL;


void init_devices()
{
    i2c = init_i2c("/dev/somthing");
    uart1 = init_serial("/dev/something", 115200);
    uart2 = init_serial("/dev/s", 115200);
    imu = init_mpu9250(i2c, 1000, 8, 250);
    ctrl = init_ctrl(
            (sensor_t*){imu, NULL, NULL}
            );
    rf = init_rf_comm(uart1, uart1->super.type);
    return;    
}

void start_device()
{
}

int main()
{

}
