#include "../include/lps25.h"
#include "../include/lps25_reg.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


lps25_t* init_lps25(i2c_dev_t* i2c, int sample_rate)
{
    lps25_t* self = malloc(sizeof(lps25_t));
    sensor_t* super = &self->super;
    super->comm = i2c;
    super->device_addr = LPS25_ADDR;
    self->read_baro_data = read_baro_data;
    switch (sample_rate)
    {
    case 1:
    case 7:
    case 13:
    case 25:
        super->rate = sample_rate;
        break;
    default:
        printf("%d is not a valid sample rate, rate set to 25hz\n", sample_rate);
        super->rate = 25;
        break;
    }
    i2c->set_addr(i2c, LPS25_ADDR);

    if(i2c->read_byte_reg(i2c, WHO_AM_I) != 0xbd)
    {
        printf("!! error\n");
        return NULL;
    }

    i2c->write_bit_reg(i2c, RES_CONF, 3, 2, 0b00, true);
    i2c->write_bit_reg(i2c, RES_CONF, 1, 2, 0b00, true);
    //resolution :avg number for thermal pressure is 8

    i2c->write_bit_reg(i2c, CTRL_1, 7, 1, 0b1, true);
    i2c->write_bit_reg(i2c, CTRL_1, 6, 3, 0b100, true);
    i2c->write_bit_reg(i2c, CTRL_1, 3, 1, 0b0, true);

    i2c->write_bit_reg(i2c, CTRL_2, 3, 1, 0b0, true);
    i2c->write_bit_reg(i2c, CTRL_2, 1, 1, 0b0, true);
}

void read_pressure(lps25_t* self, data_t* buf)
{
    i2c_dev_t* i2c = (i2c_dev_t*)self->super.comm;
    struct timespec ts;
    uint8_t pressure[3] = {0,};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    pressure[0] = i2c->read_byte_reg(i2c, PRES_OUT_XL); //lsb
    pressure[1] = i2c->read_byte_reg(i2c, PRES_OUT_L);// middle
    pressure[2] = i2c->read_byte_reg(i2c, PRES_OUT_H);//msb!

    uint8_t sign_bit = pressure[2] & 0b10000000;
    pressure[2] = pressure[2] & 0b01111111;

    int32_t result;

    result = result & (int32_t)(sign_bit << 24);
    result = (int32_t)((pressure[2] << 16) | (pressure[1] << 8) | (pressure[0]));

    float ret_val = (float)((float)result / 4096.0f);

    buf->ts.tv_sec = ts.tv_sec;
    buf->ts.tv_nsec = ts.tv_nsec;
    buf->type = BARO;
    buf->val[0] = ret_val;
}

void read_temp(lps25_t* self, data_t* buf)
{
    i2c_dev_t* i2c = self->super.comm;
    struct timespec ts;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);
    int16_t result = (int16_t)(i2c->read_byte_reg(i2c,TEMP_OUT_H) << 8 | i2c->read_byte_reg(i2c, TEMP_OUT_L));

    float tmp_out = 42.5f + (float)(result / 480.0f);
    
    buf->ts.tv_nsec = ts.tv_nsec;
    buf->ts.tv_sec = ts.tv_sec;
    buf->type = BARO;
    buf->val[0] = tmp_out;
}

void read_baro_data(lps25_t* self, data_t* dest)
{
    data_t t1, t2;

    read_temp(self, &t1);
    read_pressure(self, &t2);

    dest->type = BARO;
    memcpy(&dest->ts, &t1, sizeof(struct timespec));
    dest->val[0] = t2.val[0];//pressure
    dest->val[1] = t1.val[0];//temp
}