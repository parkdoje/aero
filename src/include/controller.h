#include "i2c.h"
#include "serial.h"
#include "sensor.h"

#define NUMBER_OF_SENSOR 3
/* for sensor control
*/

typedef struct _ctrl_t
{
    sensor_t* sensor[3];
    struct list head;
    pthread_mutex_t lock;
    int list_cnt;
    
    int (*read_data)(ctrl_t* self, data_t* buf); // from ctrler to main
}ctrl_t;

ctrl_t* init_ctrl(sensor_t* sensors[3]);

int read_data(ctrl_t* self, data_t* buf);
void write_data(ctrl_t* self, data_t* buf); // from ctrler to main

void action(ctrl_t* self); // thread function
