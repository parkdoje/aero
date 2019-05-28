#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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
    self->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    self->list_cnt = 0;
    list_init(&self->head);

    self->read_data = read_data;

    return self;
}

int read_data(ctrl_t* self, data_t* buf)
{
    struct list_elem* e = NULL;
    struct list* head = &self->head;
    pthread_mutex_lock(&self->lock);

    if(list_empty(head))
    {
        return -1;
    }
    e = list_pop_front(&self->head);
    self->list_cnt -= 1;

    pthread_mutex_unlock(&self->lock);

    data_t* dat = list_entry(e, data_t, elem);

    memcpy(buf, dat, sizeof(data_t));
    free(dat);
    return 0;
}

void write_data(ctrl_t* self, data_t* data)
{
    data_t* buf = malloc(sizeof(data_t));
    memcpy(buf, data, sizeof(data_t));

    pthread_mutex_lock(&self->lock);

    list_push_back(&self->head, &buf->elem);
    self->list_cnt += 1;

    pthread_mutex_unlock(&self->lock);
    return;
}
void read_raw_data(sensor_t* s, data_t* buf, int type)
{
    switch (type)
    {
    case ACCEL:
        /* code */
        ((mpu9250_t*)s)->read_accel_data(s, buf);
        break;
    case GYRO:
        ((mpu9250_t*)s)->read_gyro_data(s, buf);
        break;
    
    default:
        break;
    }

}

static inline bool check(struct timespec cur, struct timespec prev, int sample_rate)
{
    long sec_gap = cur.tv_sec - prev.tv_sec;
    long nsec_gap = cur.tv_nsec - prev.tv_nsec;

    nsec_gap /= 1000000; //in ms

    long ms_gap = sec_gap * 1000 + nsec_gap;
    return ms_gap >= sample_rate ? true : false;
}
void action(ctrl_t* self)// thread_fucntion
{
    //getting sensor objects
    struct timespec cur;

    struct timespec prev_sample[3] = {0,};    
    int sample_rate[3] = {
        self->sensor[0]->rate,
        self->sensor[1]->rate, self->sensor[2]->rate
    };   

    for(int i = 0; i < 3; i++)
    {
        //ms resolution
        sample_rate[i] = (unsigned int)((1.0 / sample_rate[i]) * 1000000.0);//sample rate less than 1kHz
    }
    
    // periodically do the read write job
    data_t buf;

    while(1)
    {
        clock_gettime(CLOCK_MONOTONIC, &cur);
        
        for(int i = 0; i < 3; i++)
        {
            if(check(cur, prev_sample[i], sample_rate[i]))
            {
                switch (i)
                {
                case 0://for imu
                    read_raw_data(self->sensor[i], &buf, ACCEL);
                    write_data(self, &buf);

                    memset(&buf, 0x00, sizeof(data_t));

                    read_raw_data(self->sensor[i], &buf, GYRO);
                    write_data(self, &buf);
                    
                    break;
                case 1://for gps
                    break;
                case 2: // for barometer
                    break;
                default:
                    break;
                }
                prev_sample[i] = cur;
            }
        }
    }

}
