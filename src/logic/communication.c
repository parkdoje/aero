#include "../include/communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void rcv_msg(rfdev_t* self, mavlink_message_t* dest)//use by main thread
{   
    //critical section start
    pthread_mutex_lock(&self->rcv_lock);
    
    if (self->rcv_count == 0)
    {
        pthread_mutex_unlock(&self->rcv_lock);
        return NULL; // buffer has to be empty
    }

    ASSERT(!list_empty(&self->rcv));
    
    struct list_elem* e = list_pop_front(&self->rcv);
    self->rcv_count -= 1;    

    pthread_mutex_unlock(&self->rcv_lock);
    //critical section end

    packet_t* packet = list_entry(e, packet_t, elem); // packet already pop out from the list.
    memcpy(dest, packet->msg, sizeof(mavlink_message_t));// hence packet access does not effect to other thread

    free(packet->msg);
    free(packet);

    packet = NULL;
    return;
}

int snd_msg(rfdev_t* self, mavlink_message_t* data)// data must not be a heap memory, use by main thread
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

static void read_snd_msg(rfdev_t* self, mavlink_message_t* dest)//from comm thread
{
    packet_t* packet = NULL;
    struct list_elem* e = NULL;

    //critical section start
    pthread_mutex_lock(&self->snd_lock);

    if(self->snd_count == 0)
    {
        pthread_mutex_unlock(&self->snd_lock);
        return;
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
    
    return;
}
static void write_rcv_msg(rfdev_t* self, mavlink_message_t* rcvd)//rcvd must not be a heap mem!
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


