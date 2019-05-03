

#include "../include/mpu9250.h"
#include "../include/mpu9250_reg.h"
#include "../lib/debug.h"
#include "../lib/list.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void calc_n_set_bias(mpu9250_t* self)
{
    i2c_dev_t* i2c = self->super.comm;
    ASSERT(i2c != NULL);
    ASSERT(i2c->super.type == I2C);

    i2c->write_byte_reg(i2c, INT_ENABLE, 0x00);
    i2c->write_byte_reg(i2c, FIFO_EN, 0x00);
    i2c->write_byte_reg(i2c, PWR_MGMT_1, 0x00);
    i2c->write_byte_reg(i2c, I2C_MST_CTRL, 0x00);
    i2c->write_byte_reg(i2c, USER_CTRL, 0x00);
    i2c->write_byte_reg(i2c, USER_CTRL, 0x0c);

    usleep(15 * 1000);

    i2c->write_byte_reg(i2c, CONFIG, 0x01); //set LPF to 188hz
    i2c->write_byte_reg(i2c, SMPLRT_DIV, 0x00); // set sample rate to 1kHz
    i2c->write_byte_reg(i2c, GYRO_CONFIG, 0x00);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_1, 0x00);

    uint16_t gyrosensitivity  = 131;   // = 131 LSB/degrees/se
    uint16_t accelsensitivity = 16384;  // = 16384 LSB/g
    uint16_t fifo_count = 0, packet_count = 0; 

    i2c->write_byte_reg(i2c, USER_CTRL, 0x40);   // Enable FIFO  
    i2c->write_byte_reg(i2c, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in MPU-9150)

    usleep(40 * 1000);

    i2c->write_byte_reg(i2c, FIFO_EN, 0x00);
    i2c->read_nbyte_reg(i2c, FIFO_COUNTH, 2, &fifo_count);
    
    packet_count = fifo_count / 12;

    int16_t gyro_temp[3];
    int32_t accel_bias[3], gyro_bias[3];

    uint8_t data[12];

    for(int i = 0; i < packet_count; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            data[j] = i2c->read_byte_reg(i2c, FIFO_R_W);
        }
        gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
        gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
        gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;
        gyro_bias[0]  += (int32_t) gyro_temp[0];
        gyro_bias[1]  += (int32_t) gyro_temp[1];
        gyro_bias[2]  += (int32_t) gyro_temp[2];
    }
  
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;

    // Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
    data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
    data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
    data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
    data[3] = (-gyro_bias[1]/4)       & 0xFF;
    data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
    data[5] = (-gyro_bias[2]/4)       & 0xFF;

    i2c->write_byte_reg(i2c, XG_OFFSET_H, data[0]);
    i2c->write_byte_reg(i2c, XG_OFFSET_L, data[1]);
    i2c->write_byte_reg(i2c, YG_OFFSET_H, data[2]);
    i2c->write_byte_reg(i2c, YG_OFFSET_L, data[3]);
    i2c->write_byte_reg(i2c, ZG_OFFSET_H, data[4]);
    i2c->write_byte_reg(i2c, ZG_OFFSET_L, data[5]);
    //need test
}


void _init_mpu9250(mpu9250_t* self)
{
    comm_device_t* com = self->super.comm;
    ASSERT(com != NULL);
    ASSERT(com->type == I2C);

    i2c_dev_t* i2c = (i2c_dev_t*)com;

    if (i2c->set_addr(i2c, self->super.device_addr) != 0)
        return; // need panic!
  // now we are ready to send data to mpu9254!

  //check we are really commnuicate with mpu9250
    if (i2c->read_byte_reg(i2c, WHO_AM_I) != 0x71)
        return;

    i2c->write_bit_reg(i2c, CONFIG, 5, 3, 0x00);// set no fsync
    i2c->write_bit_reg(i2c, CONFIG, 2, 3, 0);// set  dlpf for gyro 

    i2c->write_bit_reg(i2c, PWR_MGMT_1, 6, 1, 0);// disable sleep mode 
    i2c->write_bit_reg(i2c, PWR_MGMT_1, 2, 3, 1);// set clock source to x axis gyro

    i2c->write_bit_reg(i2c, GYRO_CONFIG, 4, 2, 0); // set gyro range +- 250 deg
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 1, 2, 0); // enable lpf

    i2c->write_bit_reg(i2c, ACCEL_CONFIG_1, 4, 2, 1);// set accel range +- 4g
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 1, 2, 0);// enable low pass filter 
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 2, 3, 0);// set bandwidth at 218hz, and sample rate 1kHz 

}

mpu9250_t* init_mpu9250(i2c_dev_t* i2c, uint8_t sample_rate)
{
    mpu9250_t* self = malloc(sizeof(mpu9250_t));
    sensor_t* super = &self->super;

    list_init(&super->buffer_head);
    super->comm = i2c;
    super->sensor_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    super->rate = sample_rate;
    super->device_addr = MPU9250_ADDR;

    self->accel_factor = 8192;
    self->gyro_factor = 131;

    _init_mpu9250(self);

    return self;
}

void read_accel_data(mpu9250_t* self)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;
    if (i2c->set_addr(i2c, self->super.device_addr) < 0)
        return; // panic!!

    int16_t acc[3];
    acc[0] |= (i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_XOUT_L));
    acc[1] |= (i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_YOUT_L));
    acc[2] |= (i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_ZOUT_L));

    printf("%d %d %d", acc[0], acc[1], acc[2]);

}