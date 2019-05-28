#include "../include/communication.h"
#include "../lib/debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
rfdev_t* init_rf_comm(serial_dev_t* uart, uint8_t com_code)
{

    rfdev_t* rf = malloc(sizeof(rfdev_t));

    rf->comm = (comm_device_t*)uart;
    ASSERT(rf->comm->type == com_code);

    list_init(&rf->rcv);
    list_init(&rf->snd);
    rf->snd_count = rf->rcv_count = 0;

    rf->rcv_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    rf->snd_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    
    rf->snd_msg = snd_msg;
    rf->rcv_msg = rcv_msg;
}

int rcv_msg(rfdev_t* self, mavlink_message_t* dest)//use by main thread
{   
    //critical section start
    pthread_mutex_lock(&self->rcv_lock);
    
    if (self->rcv_count == 0)
    {
        pthread_mutex_unlock(&self->rcv_lock);
        return -1;// no received message
    }

    ASSERT(!list_empty(&self->rcv));// rcv count != 0 => list must filled
    
    struct list_elem* e = list_pop_front(&self->rcv);
    self->rcv_count -= 1;    

    pthread_mutex_unlock(&self->rcv_lock);
    //critical section end

    packet_t* packet = list_entry(e, packet_t, elem); // packet already pop out from the list.
    memcpy(dest, packet->msg, sizeof(mavlink_message_t));// hence packet access does not effect to other thread

    free(packet->msg);
    free(packet);

    packet = NULL;
    return 0;
}

// data must not be a heap memory, use by main thread
void snd_msg(rfdev_t* self, mavlink_message_t* data)
{
    packet_t* packet = malloc(sizeof(packet_t));
    mavlink_message_t* _msg = malloc(sizeof(mavlink_message_t));
    
    memcpy(_msg, data, sizeof(mavlink_message_t));
    packet->msg = _msg;

    //critical section start
    pthread_mutex_lock(&self->snd_lock);

    list_push_back(&self->snd, &packet->elem);
    self->snd_count += 1;

    pthread_mutex_unlock(&self->snd_lock);
    //critical section end

    return 0;
}

static int read_snd_msg(rfdev_t* self, mavlink_message_t* dest)//from comm thread
{
    packet_t* packet = NULL;
    struct list_elem* e = NULL;

    //critical section start
    pthread_mutex_lock(&self->snd_lock);

    if(self->snd_count == 0)
    {
        pthread_mutex_unlock(&self->snd_lock);
        return -1;
    }
    ASSERT(!list_empty(&self->snd));

    e = list_pop_front(&self->snd);
    self->snd_count -= 1;

    pthread_mutex_unlock(&self->snd_lock);
    //critical section end

    packet = list_entry(e, packet_t, elem);
    memcpy(dest, packet->msg, sizeof(mavlink_message_t));

    free(packet->msg);
    free(packet);
    packet = NULL;
    
    return 0;
}
static void write_rcv_msg(rfdev_t* self, mavlink_message_t* rcvd)//rcvd must not be a heap mem, if heap, it will not freed
{
    //use by communication thread
    packet_t* packet = malloc(sizeof(packet_t));
    mavlink_message_t* _msg = malloc(sizeof(mavlink_message_t));

    memcpy(_msg, rcvd, sizeof(mavlink_message_t));
    packet->msg = _msg;

    //critical section start
    pthread_mutex_lock(&self->rcv_lock); // msg received from telemetry;

    list_push_back(&self->rcv, &packet->elem);    
    self->rcv_count += 1;

    pthread_mutex_unlock(&self->rcv_lock);
    //critical section end

    return;
}

static int snd_to_rf(rfdev_t* self)
{
    mavlink_message_t msg;
    serial_dev_t* uart = self->comm;
    
    int stat = read_snd_msg(self, &msg);

    uint8_t msg_arr[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(&msg_arr, &msg);

    if(stat == -1)
    {
        return -1;//no more packet to send;
    }

    uint16_t snd_len = uart->super.write_nbyte((comm_device_t*)self, len, &msg_arr);
    if(len != snd_len)
    {
        // something
    }
    return 0;
}

static int rcv_frm_rf(rfdev_t* self)
{
    mavlink_message_t tmp_msg;
    mavlink_status_t status;
    serial_dev_t* uart = (serial_dev_t*)self->comm;
    uint8_t ch;
    uint8_t stat;

    //TO DO: this method can discard the packet need another method
    while((ch = uart->super.read_byte(uart)) >= 0)
    {
        stat = mavlink_parse_char(0, ch, &tmp_msg, &status);
        if (stat)
        {
            if(stat == MAVLINK_FRAMING_BAD_CRC)
            {
                break;
            }

            write_rcv_msg(self, &tmp_msg);

            return 0;
        }
    }
    
    return -1;
}

static inline bool check(struct timespec cur, struct timespec prev, int sample_rate)
{
    long sec_gap = cur.tv_sec - prev.tv_sec;
    long nsec_gap = cur.tv_nsec - prev.tv_nsec;

    nsec_gap /= 1000000; //in ms

    long ms_gap = sec_gap * 1000 + nsec_gap;
    return ms_gap >= sample_rate ? true : false;
}


void action(rfdev_t* self)
{
    long check_rate[2] = {0,};
    struct timespec prev_check[2] = {0,};
    long cur_time;
    int ret = 0;
    struct timespec cur;

    while(1)
    {
        clock_gettime(CLOCK_MONOTONIC, &cur);
        for(int i = 0; i < 2; i++)
        {
            if(check(cur, prev_check[i], check_rate[i]))
            {
                switch (i)
                {
                    case 0:
                        ret = rcv_frm_rf(self);
                        break;
                    case 1:
                        ret = snd_to_rf(self);
                        break;
                }
                prev_check[i] = cur;

                if(ret == -1 && check_rate[i] <= 100)
                {
                    check_rate[i] += 10;
                }
                else if(ret != -1 && check_rate[i] > 0)
                {
                    check_rate[i] -= 10;   
                }
                else
                {
                    // do nothing 
                }
            }
        }
    }
    
    // todo : implement thread func
}

