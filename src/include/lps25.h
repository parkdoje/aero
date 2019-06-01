// include files
#pragma once
#include "sensor.h"
#include "i2c.h"
#include <stdint.h>
#include <sys/types.h>

typedef struct _lps25
{
    sensor_t super;

    void (*read_baro_data)(struct _lps25* self, data_t* buf);

} lps25_t;

lps25_t* init_lps25(i2c_dev_t* i2c, int sample_rate);//인수 추가 가능

struct list_elem* read_buffer(lps25_t* self);
void write_buffer(lps25_t* self);// data types pointer
void read_pressure(lps25_t* self, data_t* buf);
void read_temp(lps25_t* self,  data_t* buf);
void read_baro_data(lps25_t* self, data_t* dest);
