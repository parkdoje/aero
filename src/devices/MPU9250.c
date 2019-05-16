#include "../include/mpu9250.h"
#include "../include/mpu9250_reg.h"
#include "../lib/debug.h"
#include "../lib/list.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


// Accelerometer and xoscope self test; check calibration wrt factory settings
bool self_test(mpu9250_t* self)
{
    i2c_dev_t* i2c = self->super.comm;

    float a_sample[3] = {0.0}, g_sample[3] = {0.0}, a_st[3] = {0.0}, g_st[3] = {0.0}, a_str[3] = {0.0}, g_str[3] = {0.0};
    float ast_val[3], gst_val[3], a_res[3] , g_res[3];
    ASSERT(i2c->set_addr(i2c, self->super.device_addr) > -1);
    uint8_t ast_data[3], gst_data[3];
    
    uint8_t sample_rate, config, gyro_config, accel_conf1, accel_conf2;

    sample_rate = i2c->read_byte_reg(i2c, SMPLRT_DIV);
    config = i2c->read_byte_reg(i2c, CONFIG);
    gyro_config = i2c->read_byte_reg(i2c, GYRO_CONFIG);
    accel_conf1 = i2c->read_byte_reg(i2c, ACCEL_CONFIG_1);
    accel_conf2 = i2c->read_byte_reg(i2c, ACCEL_CONFIG_2);

    i2c->write_bit_reg(i2c, CONFIG, 2, 3, 2, false);
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 2, 3, 2, false);
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 4, 2, 0b00, false);
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_1, 4, 3, 0b00, false);

    for(int i = 0; i < 200; i++)
    {
        a_sample[0] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_XOUT_L)));
        a_sample[1] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_YOUT_L)));
        a_sample[2] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_ZOUT_L)));

        g_sample[0] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_XOUT_L)));
        g_sample[1] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_YOUT_L)));
        g_sample[2] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_ZOUT_L)));
    }
    
    for(int i = 0; i < 3; i++)
    {
        a_sample[i] /= 200.0;
        g_sample[i] /= 200.0;
    }

    i2c->write_bit_reg(i2c, ACCEL_CONFIG_1, 7, 3, 0b111, false);
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 7, 3, 0b111, false);



    usleep(40*1000);

    for(int i = 0; i < 200; i++)
    {
        a_st[0] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_XOUT_L)));
        a_st[1] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_YOUT_L)));
        a_st[2] += (float)((int16_t)(i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 |i2c->read_byte_reg(i2c, ACCEL_ZOUT_L)));

        g_st[0] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_XOUT_L)));
        g_st[1] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_YOUT_L)));
        g_st[2] += (float)((int16_t)(i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 |i2c->read_byte_reg(i2c, GYRO_ZOUT_L)));
    }

     for(int i = 0; i < 3; i++)
    {
        a_st[i] /= 200.0;
        g_st[i] /= 200.0;
    }

    for(int i = 0; i < 3; i++)
    {
        a_str[i] = a_st[i] - a_sample[i];
        g_str[i] = g_st[i] - g_sample[i];
    }

    i2c->write_bit_reg(i2c, ACCEL_CONFIG_1, 7, 3, 0b000, false);
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 7, 3, 0b000, false);

    ast_data[0] = i2c->read_byte_reg(i2c, SELF_TEST_X_ACCEL);
    ast_data[1] = i2c->read_byte_reg(i2c, SELF_TEST_Y_ACCEL);
    ast_data[2] = i2c->read_byte_reg(i2c, SELF_TEST_Z_ACCEL);

    gst_data[0] = i2c->read_byte_reg(i2c, SELF_TEST_X_GYRO);
    gst_data[1] = i2c->read_byte_reg(i2c, SELF_TEST_Y_GYRO);
    gst_data[2] = i2c->read_byte_reg(i2c, SELF_TEST_Z_GYRO);

    for(int i = 0; i < 3; i++)
    {
        ast_val[i] = (float)(2620.0) * powf(1.01, ast_data[i] - 1);
        gst_val[i] = (float)(2620.0) * powf(1.01, gst_data[i] - 1);
    }

    for(int i = 0; i < 3; i++)
    {
        a_res[i] = a_str[i] / ast_val[i];
        g_res[i] = g_str[i] / gst_val[i];
    }
    for (int i = 0;i < 3; i++)
    {
        if(a_res[i] < 0.5 || a_res[i] >1.5)
            return false;
        if(g_res[i] < 0.5)
            return false;
        printf("%d th  percentage is : a: %f g: %f \n", a_res[i] *100.0, g_res[i] * 100.0);
    }

    i2c->write_byte_reg(i2c, SMPLRT_DIV, sample_rate);
    i2c->write_byte_reg(i2c, CONFIG, config);
    i2c->write_byte_reg(i2c, GYRO_CONFIG, gyro_config);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_1, accel_conf1);
    i2c->write_byte_reg(i2c, ACCEL_CONFIG_2, accel_conf2);
    return true;
}



void _init_mpu9250(mpu9250_t* self, uint8_t sample_rate)
{
    comm_device_t* com = self->super.comm;
    float test_result[6] = {0, 0, 0, 0, 0, 0};
    ASSERT(com != NULL);
    ASSERT(com->type == I2C);

    i2c_dev_t* i2c = (i2c_dev_t*)com;

    if (i2c->set_addr(i2c, self->super.device_addr) != 0)
    {
        printf("failed to set address to %p", self->super.device_addr);
        return;
    }
    // now we are ready to send data to mpu9250!
    i2c->write_bit_reg(i2c, PWR_MGMT_1, 6, 1, 0, false);// disable sleep mode 
    i2c->write_bit_reg(i2c, PWR_MGMT_1, 2, 3, 1, false);// set clock source to x axis gyro

    i2c->write_bit_reg(i2c, CONFIG, 5, 3, 0x00, false);// set no fsync
    i2c->write_bit_reg(i2c, CONFIG, 2, 3, 0, false);// choose lpf bw and rate, at here use bw:250Hz, delay 0.97ms => gyro scope data output rate is almost 1kHz

    i2c->write_byte_reg(i2c, SMPLRT_DIV, sample_rate); // data output rate / 1 + samplerate 

    i2c->write_bit_reg(i2c, GYRO_CONFIG, 4, 2, 0, false); // set gyro range +- 250 deg /s 
    i2c->write_bit_reg(i2c, GYRO_CONFIG, 1, 2, 0b00, false); // choose lpf bw

    i2c->write_bit_reg(i2c, 1, 4, 2, 1, false);// set accel range +- 4g
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 3, 1, 0, false);// use dlpf for accel 
    i2c->write_bit_reg(i2c, ACCEL_CONFIG_2, 2, 3, 0, false); // dlpf rate set as bw = 218Hz, delay = 1.88ms => data output rate is about 200Hza

    usleep(40 * 1000); 
//check we are really commnuicate with mpu9250
    if (i2c->read_byte_reg(i2c, WHO_AM_I) != 0x71)
    {
        printf("device not respond!!\n");
        return;
    }

    ASSERT(self_test(self));

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

static inline void check_conn(mpu9250_t* self)
{
    i2c_dev_t* i2c = self->super.comm;
    ASSERT(i2c->set_addr(i2c, self->super.device_addr) > -1);
    ASSERT(i2c->read_byte_reg(i2c, WHO_AM_I) == 0x71);
}


void read_accel_data(mpu9250_t* self, data_t* data)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;

    check_conn(self);

    int16_t acc[3];
    acc[0] = (int16_t)(i2c->read_byte_reg(i2c, ACCEL_XOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_XOUT_L));
    acc[1] = (int16_t)(i2c->read_byte_reg(i2c, ACCEL_YOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_YOUT_L));
    acc[2] = (int16_t)(i2c->read_byte_reg(i2c, ACCEL_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, ACCEL_ZOUT_L));

    data->x = (float)acc[0] * self->accel_res;
    data->y = (float)acc[1] * self->accel_res;
    data->z = (float)acc[2] * self->accel_res;

}

void read_gyro_data(mpu9250_t* self, data_t* data)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;

    check_conn(self);

    int16_t gy[3];
    gy[0] = (int16_t)(i2c->read_byte_reg(i2c, GYRO_XOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_XOUT_L));
    gy[1] = (int16_t)(i2c->read_byte_reg(i2c, GYRO_YOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_YOUT_L));
    gy[2] = (int16_t)(i2c->read_byte_reg(i2c, GYRO_ZOUT_H) << 8 | i2c->read_byte_reg(i2c, GYRO_ZOUT_L)); 

    data->x = (float)gy[0];
    data->y = (float)gy[1];
    data->z = (float)gy[2];
}

struct list_elem* read_buffer(mpu9250_t* self)
{
    struct list* head = &(self->super.buffer_head);
    int ern = pthread_mutex_trylock(&self->super.sensor_lock);//버퍼가 크기 때문에 조금 지연되어도 상관없음. 지연보다는 다른 기능들의 시간에 맞춘 실행이 더 중요
    if (ern != 0)
        return NULL;
    struct list_elem* elem = list_pop_front(head);
    pthread_mutex_unlock(&self->super.sensor_lock);
    return elem;
    
}

void write_buffer(mpu9250_t* self, data_t* data)
{
    struct list* head = &(self->super.buffer_head);
    int ern = pthread_mutex_lock(&self->super.sensor_lock); // debug purpose
    list_push_back(head, &data->elem);
    pthread_mutex_unlock(&self->super.sensor_lock);
    return;
}
