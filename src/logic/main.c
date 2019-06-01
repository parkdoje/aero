#include "../include/i2c.h"
#include "../include/mpu9250.h"
#include "../include/serial.h"
#include "../include/lps25.h"
#include "../include/controller.h"
#include "../include/communication.h"
#include "../lib/list.h"
#include "../lib/debug.h"
#include "../include/gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>


mpu9250_t* imu = NULL;
i2c_dev_t* i2c = NULL;
serial_dev_t* uart1 = NULL;//for wireless 
serial_dev_t* uart2 = NULL;//for gps
ctrl_t* controller = NULL;
rfdev_t* rf_dev = NULL;

pthread_t radio, sensor, primary;


int read_sensor_buf(ctrl_t* cnt, data_t* buf)
{
    struct list_elem* e = NULL;

    pthread_mutex_lock(&cnt->lock);

    if(cnt->list_cnt == 0)
    {
        pthread_mutex_unlock(&cnt->lock);
        buf->type = -1;
        return -1;
    }
    ASSERT(!list_empty(&cnt->head));// if this has error list count handle wrong
    
    e = list_pop_front(&cnt->head);
    cnt->list_cnt -= 1;

    pthread_mutex_unlock(&cnt->lock);
    
    data_t* data = list_entry(e, data_t, elem);

    memcpy(buf, data, sizeof(data_t));

    free(data);
    
     return 0;
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
    mavlink_message_t msg = {0, };

    float msg_time = (
        (float)(data->ts.tv_sec) + ((float)(data->ts.tv_nsec) / 1000000)
    );
    switch (data->type)
    {
    case ACCEL:
        mavlink_msg_accel_pack(0, 0, &msg, msg_time, data->val[0], data->val[1], data->val[2]);
        break;
    case GYRO:
        mavlink_msg_gyro_pack(0, 0, &msg, msg_time, data->val[0], data->val[1], data->val[2]);
        break;
    case POS:
        break;
    case NAV:
        break;
    case BARO:
        break;
    default:
        break;
    }
    rf->snd_msg(rf, &msg);
}


void init_devices()
{
    sensor_t* s_list[3] = {imu, NULL, NULL};
    i2c = init_i2c("/dev/somthing");
    uart1 = init_serial("/dev/something", 115200);
    uart2 = init_serial("/dev/s", 115200);
    imu = init_mpu9250(i2c, 1000, 8, 250);
    controller = init_ctrl(s_list);
    rf_dev = init_rf_comm(uart1, uart1->super.type);
    return;    
}

void primary_routine()
{
    data_t s_buf = {0, };
    data_t r_buf = {0, };
    while(1)
    {
        if(read_sensor_buf(controller, &s_buf) == 0)
        {
            pack_n_send(rf_dev, &s_buf);
        }
        read_radio_buf(rf_dev);
    }
}

void start_device()
{
    pthread_create(&radio, NULL, rf_dev->action, rf_dev);
    pthread_create(&sensor, NULL, controller->action, controller);
    pthread_create(&primary, NULL, primary_routine, NULL);
}

int main()
{
    init_devices();
    start_device();
    usleep(1000*1000);
    
    pthread_join(radio, NULL);
    pthread_join(sensor, NULL);
    pthread_join(primary, NULL);
    return 0;

}
    