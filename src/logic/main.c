#include "../include/i2c.h"
#include "../include/mpu9250.h"
#include "../include/serial.h"
#include "../include/lps25.h"
#include "../include/controller.h"
#include "../include/communication.h"
#include "../lib/list.h"
#include "../lib/debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NDEBUG 1

mpu9250_t* imu = NULL;
i2c_dev_t* i2c = NULL;
serial_dev_t* uart1 = NULL;//for wireless 
serial_dev_t* uart2 = NULL;//for gps
ctrl_t* controller = NULL;
rfdev_t* rf_dev = NULL;

pthread_t radio, sensor, primary;


void read_sensor_buf(ctrl_t* cnt, data_t* buf)
{
    struct list_elem* e = NULL;

    pthread_mutex_lock(&cnt->lock);

    if(cnt->list_cnt == 0)
    {
        pthread_mutex_unlock(&cnt->lock);
        return;
    }
    ASSERT(!list_empty(&cnt->head));// if this has error list count handle wrong
    
    e = list_pop_front(&cnt->head);
    cnt->list_cnt -= 1;

    pthread_mutex_unlock(&cnt->lock);
    
    data_t* data = list_entry(e, data_t, elem);

    memcpy(buf, data, sizeof(data_t));

    free(data);
}

void read_radio_buf(rfdev_t* rf)
{
    mavlink_message_t msg;
    rf->rcv_msg(rf, &msg);
    switch (msg.msgid)
    {
        case 1:
            //command
            break;
        case 2:
            //update status
            break;
        default:
            break;
    }
}

void pack_n_send(rfdev_t* rf, data_t* data)
{
    mavlink_message_t msg;
    mavlink_msg_baro_pack();
}


void init_devices()
{
    i2c = init_i2c("/dev/somthing");
    uart1 = init_serial("/dev/something", 115200);
    uart2 = init_serial("/dev/s", 115200);
    imu = init_mpu9250(i2c, 1000, 8, 250);
    controller = init_ctrl(
            (sensor_t**){imu, NULL, NULL}
            );
    rf_dev = init_rf_comm(uart1, uart1->super.type);
    return;    
}

void start_device()
{
    pthread_create(&radio, NULL, rf_dev->action, rf_dev);
    pthread_create(&sensor, NULL, controller->action, controller);
}

int main()
{
    init_devices();
    start_device();

    pthread_join(radio, NULL);
    pthread_join(sensor, NULL);
    return 0;

}
    