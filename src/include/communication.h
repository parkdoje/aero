#include <stdint.h>
#include <pthread.h>

#include "../lib/list.h"
#include "../include/serial.h"
#include "../include/mav/my_link/mavlink.h"


typedef struct packet
{
    struct list_elem elem;
    mavlink_message_t* msg;
}packet_t;

typedef struct rfdev
{
    comm_device_t* comm;
    pthread_mutex_t rcv_lock, snd_lock; // first use mutex
    struct list rcv, snd;// using linked list as a fifo queue
    /*
    To Do: use circular buffer to lower the malloc overhead
    */
    uint16_t rcv_count, snd_count;// scheduling purpose

    //wrapper for comm device
    mavlink_message_t* (*rcv_msg)(struct rfdev* self);
    int (*snd_msg)(struct rfdev* self, mavlink_message_t* data);
}rfdev_t;


//rfdev_t may or may not be a heap memory
//use by main thread, argument pointer need not be a heap memory
void rcv_msg(rfdev_t* self, mavlink_message_t* dest);
int snd_msg(rfdev_t* self, mavlink_message_t* data);


//use by comm thread, argument pointer need not be a heap memory
static void read_snd_msg(rfdev_t* self, mavlink_message_t* dest);
static void write_rcv_msg(rfdev_t* self, mavlink_message_t* rcvd);