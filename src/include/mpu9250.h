#include "sensor.h"
#include "i2c.h"
#include <stdbool.h>

#define MPU9250_ADDR 0x68

typedef struct
{/*singleton object!*/
    sensor_t super;
    bool GYRO_INIT, ACCEL_INIT;
    float accel_res, gyro_res;

}mpu9250_t;



mpu9250_t* init_mpu9250(i2c_dev_t* i2c, uint8_t sample_rate);

void read_accel_data(mpu9250_t* self);
void read_gyro_data(mpu9250_t* self);

typedef struct 
{
    float a_x;
    float a_y;
    float a_z;
    time_t stamp;
}accel_data_t;

typedef struct
{
    float g_x;
    float g_y;
    float g_z;
    time_t stamp;
}gyro_data_t;
