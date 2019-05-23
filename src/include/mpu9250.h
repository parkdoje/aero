#include "sensor.h"
#include "i2c.h"
#include <stdbool.h>

#define MPU9250_ADDR 0x68
#define GYRO 1
#define ACCEL 2




typedef struct mpu9250
{/*singleton object!*/
    sensor_t super;
    float accel_res, gyro_res;
    void (*read_accel_data)(mpu9250_t* self, data_t* data);
    void (*read_gyro_data)(mpu9250_t* self, data_t* data);

}mpu9250_t;


mpu9250_t* init_mpu9250(i2c_dev_t* i2c, uint8_t sample_rate, uint8_t accel_scale, uint16_t gyro_scale);

//controller will handle the packaging to mavlink
void read_accel_data(mpu9250_t* self, data_t* data);
void read_gyro_data(mpu9250_t* self, data_t* data);

