#include "../include/communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
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

void snd_msg(rfdev_t* self, mavlink_message_t* data)// data must not be a heap memory, use by main thread
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
    ASSERT(!list_empty(&self->rcv));

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
        return 0;//no more packet to send;
    }

    return uart->super.write_nbyte((comm_device_t*)self, len, &msg_arr);
}

static int rcv_frm_rf(rfdev_t* self)
{
    mavlink_message_t tmp_msg;
    mavlink_status_t status;
    serial_dev_t* uart = (serial_dev_t*)self->comm;
    uint8_t ch;
    uint8_t stat;

    while((ch = uart->super.read_byte(uart)) > 0)
    {
        stat = mavlink_parse_char(0, ch, &tmp_msg, &status);
        if (stat)
        {
            if(stat == MAVLINK_FRAMING_BAD_CRC)
            {
                break;//ERROR!! discard packet 
            }

            write_rcv_msg(self, &tmp_msg);
            break;
        }
    }
    
    return 0;
}

