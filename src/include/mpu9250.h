#include "sensor.h"
#include "i2c.h"
#include <stdbool.h>

#define MPU9250_ADDR 0x68
#define GYRO 1
#define ACCEL 2


typedef struct data
{
    int type;
    float x, y, z;
    struct timespec ts;
    struct list_elem elem;
}data_t;

typedef struct mpu9250
{/*singleton object!*/
    sensor_t super;
    float accel_res, gyro_res;

}mpu9250_t;


mpu9250_t* init_mpu9250(i2c_dev_t* i2c, uint8_t sample_rate, uint8_t accel_scale, uint16_t gyro_scale);
struct list_elem* read_buffer(mpu9250_t* self);
void write_buffer(mpu9250_t* self, struct list_elem* elem);

//controller will handle the packaging to mavlink
void read_accel_data(mpu9250_t* self, data_t* data);
void read_gyro_data(mpu9250_t* self, data_t* data);

