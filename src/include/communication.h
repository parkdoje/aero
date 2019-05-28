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
    // rcv : receive from ground, snd : sent from main

    /*
    To Do: use circular buffer to lower the malloc overhead
    */
    uint16_t rcv_count, snd_count;// scheduling purpose

    //wrapper for comm device
    int (*rcv_msg)(struct rfdev* self);
    void (*snd_msg)(struct rfdev* self, mavlink_message_t* msg);
    void (*action)(struct rfdev* self);
}rfdev_t;


rfdev_t* init_rf_comm(serial_dev_t* uart, uint8_t com_code);

//rfdev_t may or may not be a heap memory
//use by main thread, argument pointer need not be a heap memory
int rcv_msg(rfdev_t* self, mavlink_message_t* dest);// receive from ground
void snd_msg(rfdev_t* self, mavlink_message_t* data);// send to ground 

//internal usage
static int read_snd_msg(rfdev_t* self, mavlink_message_t* dest);
static void write_rcv_msg(rfdev_t* self, mavlink_message_t* data);

//comm thread
static int snd_to_rf(rfdev_t* self);
static int rcv_frm_rf(rfdev_t* self);
