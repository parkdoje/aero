

#include "../include/mpu9250.h"
#include "../include/mpu9250_reg.h"
#include "../lib/debug.h"
#include "../lib/list.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Accelerometer and gyroscope self test; check calibration wrt factory settings
void self_test(mpu9250_t* self, float* destination) // Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
{
    uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
    uint8_t selfTest[6];
    int32_t gAvg[3] = {0}, aAvg[3] = {0}, aSTAvg[3] = {0}, gSTAvg[3] = {0};
    float factoryTrim[6];
    uint8_t FS = 0;
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;
    
    uint8_t sample_rate = i2c->read_byte_reg(i2c, SMPLRT_DIV);
    uint8_t config = i2c->read_byte_reg(i2c, CONFIG);
    uint8_t gyro_config = i2c->read_byte_reg(i2c, GYRO_CONFIG);
    uint8_t accel_config_1 = i2c->read_byte_reg(i2c, ACCEL_CONFIG_1);
    uint8_t accel_config_2 = i2c->read_byte_reg(i2c, ACCEL_CONFIG_2);
    
    i2c->write_byte_reg(i2c, SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
    i2c->write_byte_reg(i2c, CONFIG, 0x02);
    i2c->write_byte_reg(i2c, GYRO_CONFIG, 0x00);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_2, 0x02);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_1, 0x00);

    for(int i = 0; i < 200; i++) 
    {  // get average current values of gyro and acclerometer
    
        aAvg[0] = (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_XOUT_L));
        aAvg[1] = (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_YOUT_L));
        aAvg[2] = (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_ZOUT_L));
        
        
        gAvg[0] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_XOUT_L));
        gAvg[1] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_YOUT_L));
        gAvg[2] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_ZOUT_L));
    }
    
    for (int i =0; i < 3; i++) 
    {  // Get average of 200 values and store as average current readings
        aAvg[i] /= 200;
        gAvg[i] /= 200;
    }
    
    // Configure the accelerometer for self-test
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_1, 0xE0);//enable self test 
    i2c->write_byte_reg(i2c, GYRO_CONFIG, 0xE0);// enable self test

    usleep(25 * 1000); // wati for 25 ms

    for(int i = 0; i < 200; i++) 
    {  // get average self-test values of gyro and acclerometer
        aSTAvg[0] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_XOUT_L));  // Turn the MSB and LSB into a signed 16-bit value
        aSTAvg[1] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_YOUT_L));
        aSTAvg[2] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_ZOUT_L)); 

        gSTAvg[0] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_XOUT_L)); // Turn the MSB and LSB into a signed 16-bit value
        gSTAvg[1] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_YOUT_L)); 
        gSTAvg[2] += (int16_t)((int16_t)i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_ZOUT_L));
    }
    
    for (int i =0; i < 3; i++) 
    {  // Get average of 200 values and store as average self-test readings
        aSTAvg[i] /= 200;
        gSTAvg[i] /= 200;
    } 

    //restore original settings

    i2c->write_byte_reg(i2c, ACCEL_CONFIG_1, accel_config_1);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_2, accel_config_2);
    i2c->write_byte_reg(i2c, SMPLRT_DIV, sample_rate);
    i2c->write_byte_reg(i2c, CONFIG, config);
    i2c->write_byte_reg(i2c, GYRO_CONFIG, gyro_config);

    usleep(25 * 1000);  // Delay a while to let the device stabilize
    
    // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg

    selfTest[0] = i2c->read_byte_reg(i2c, SELF_TEST_X_ACCEL); // X-axis accel self-test results
    selfTest[1] = i2c->read_byte_reg(i2c, SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
    selfTest[2] = i2c->read_byte_reg(i2c, SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
    selfTest[3] = i2c->read_byte_reg(i2c, SELF_TEST_X_GYRO);  // X-axis gyro self-test results
    selfTest[4] = i2c->read_byte_reg(i2c, SELF_TEST_Y_GYRO);  // Y-axis gyro self-test results
    selfTest[5] = i2c->read_byte_reg(i2c, SELF_TEST_Z_GYRO);  // Z-axis gyro self-test results

    // Retrieve factory self-test value from self-test code reads
    factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); 
    factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) ));
    factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) ));
    factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) ));
    factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) ));
    factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) ));
    
    // Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
    // To get percent, must multiply by 100
    for (int i = 0; i < 3; i++) 
    {
        destination[i]   = 100.0f*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i] - 100.0f;   // Report percent differences
        destination[i+3] = 100.0f*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3] - 100.0f; // Report percent differences
    }
}


void _init_mpu9250(mpu9250_t* self, uint8_t sample_rate)
{
    comm_device_t* com = self->super.comm;
    float test_result[6] = {0, 0, 0, 0, 0, 0};
    ASSERT(com != NULL);
    ASSERT(com->type == I2C);

    i2c_dev_t* i2c = (i2c_dev_t*)com;

    if (i2c->set_addr(i2c, self->super.device_addr) != 0)
        return; // need panic!
    // now we are ready to send data to mpu9250!
    i2c->write_bit_reg(i2c, PWR_MGMT_1, 6, 1, 0);// disable sleep mode 
    i2c->write_bit_reg(i2c, PWR_MGMT_1, 2, 3, 1);// set clock source to x axis gyro

    usleep(40 * 1000);
    //check we are really commnuicate with mpu9250
    if (i2c->read_byte_reg(i2c, WHO_AM_I) != 0x71)
        return;

    self_test(self, &test_result);
    printf("self test data percentage\n");
    printf("ax  ay  az  gx  gy  gz\n");
    for(int i = 0; i < 6; i++)
    {
        printf("%f, ", test_result[i]);
    }
    printf("\n");
    


    i2c->write_bit_reg(i2c, CONFIG, 5, 3, 0x00);// set no fsync
    i2c->write_bit_reg(i2c, CONFIG, 2, 3, 0);// choose lpf bw and rate, at here use bw:250Hz, delay 0.97ms => gyro scope data output rate is almost 1kHz

    i2c->write_byte_reg(i2c, SMPLRT_DIV, sample_rate); // data output rate / 1 + samplerate 

    i2c->write_bit_reg(i2c, GYRO_CONFIG, 4, 2, 0); // set gyro range +- 250 deg /s 
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 1, 2, 0b00); // choose lpf bw

    i2c->write_bit_reg(i2c, ACCEL_CONFIG_1, 4, 2, 1);// set accel range +- 4g
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 3, 1, 0);// use dlpf for accel 
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 2, 3, 0); // dlpf rate set as bw = 218Hz, delay = 1.88ms => data output rate is about 200Hz
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
    
    self->accel_res = 4.0 / 32768.0f; /* need change*/
    self->gyro_res = 250.0 / 32768.0f;

    _init_mpu9250(self, sample_rate);

    return self;
}

void read_accel_data(mpu9250_t* self, accel_data_t* data)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;

    if(i2c->dev_addr != self->super.device_addr)
        ASSERT(i2c->set_addr(i2c, self->super.device_addr) > -1);

    int16_t acc[3];
    acc[0] = (i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_XOUT_L));
    acc[1] = (i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_YOUT_L));
    acc[2] = (i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_ZOUT_L));
    data->a_x = (float)acc[0]*self->accel_res;
    data->a_y = (float)acc[1]*self->accel_res;
    data->a_z = (float)acc[2]*self->accel_res;

}

void read_gyro_data(mpu9250_t* self, gyro_data_t* data)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;
    if(i2c->dev_addr != self->super.device_addr)
        ASSERT(i2c->set_addr(i2c, self->super.device_addr) > -1);

    int16_t gy[3];
    gy[0] = (i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_XOUT_L));
    gy[1] = (i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_YOUT_L));
    gy[2] = (i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_ZOUT_L));
    data->g_x = (float)gy[0]*self->gyro_res;
    data->g_y = (float)gy[1]*self->gyro_res;
    data->g_z = (float)gy[2]*self->gyro_res;
}