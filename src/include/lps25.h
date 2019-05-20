// include files
#include "sensor.h"
#include "i2c.h"

typedef struct _lps25
{
    sensor_t super;



} lps25_t;

lps25_t* init_lps25(i2c_dev_t* i2c);//인수 추가 가능

struct list_elem* read_buffer(lps25_t* self);
void write_buffer(lps25_t* self);// data types pointer
void read_pressure(lps25_t* self);
void read_tempeature(lps25_t* self);
