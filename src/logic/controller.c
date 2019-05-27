#include <stdlib.h>
#include <string.h>

#include "../lib/list.h"
#include "../include/communication.h"
#include "../include/controller.h"
#include "../include/mpu9250.h"
#include "../include/lps25.h"


ctrl_t* init_ctrl(sensor_t* sensors[3])
{
    ctrl_t* self = malloc(sizeof(ctrl_t));
    for(int i = 0; i < 3; i++)
    {
        self->sensor[i] = sensors[i];
    }
    return self;
}

void start_action(ctrl_t* self)
{
    data_t buffer;
    mpu9250_t* imu = self->sensor[0];
    //for now we only have imu implementation
    while(1)
    {
        
    }
}

void write_to_buffer(ctrl_t* self, data_t* data)
{
    int type = data->type;
    data_t* data_to_send = malloc(sizeof(data_t));
    memcpy(data_to_send, data, sizeof(data_t));

    switch (type)
    {
        case ACCEL:
        case GYRO:
            list_push_back(&self->sensor[0]->buffer_head, &data_to_send->elem);
            break;
        case GPS:
            list_push_back(&self->sensor[0]->buffer_head, &data_to_send->elem);
            break;
        case BARO:
            list_push_back(&self->sensor[0]->buffer_head, &data_to_send->elem);
            break;
    }
}

