#include "sensor.h"
#include "i2c.h"
#include "mpu9250_reg.h"
#include <stdbool.h>



typedef struct
{/*singleton object!*/
    sensor_t super;
    bool GYRO_INIT, ACCEL_INIT;
    float accel_factor, gyro_factor;
}mpu9250_t;

bool init_mpu9250(mpu9250_t* IMU, uint8_t acc_scale, uint8_t gy_scale, uint8_t sample_rate);


static bool accel_test();
static bool gyro_test();

static void set_accel_test(uint8_t flag);
static void set_gyro_test(uint8_t flag);

void set_gyro_offset(uint16_t offset_x, uint16_t offset_y, uint16_t offset_z);
void set_accel_offset(uint16_t offset_x, uint16_t offset_y, uint16_t offset_z_);


typedef struct 
{

}accel_data_t;

typedef struct
{

}gyro_data_t;
