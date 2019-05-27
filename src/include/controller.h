#include "i2c.h"
#include "serial.h"
#include "sensor.h"

#define NUMBER_OF_SENSOR 3
/* for sensor control
*/

typedef struct _ctrl_t
{
    sensor_t* sensor[NUMBER_OF_SENSOR];// 1: mpu9250, 2 : lps25, 3: gps
    /* To Do : implement edf scheduler for sensor reading, for now we are using round robin*/     
    void (*start_action)(ctrl_t* self);

    
}ctrl_t; 

ctrl_t* init_ctrl(sensor_t* sensors[3]);

void start_action(ctrl_t* self);

void write_to_buffer(ctrl_t* self, data_t* data);