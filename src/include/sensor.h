
#include <pthread.h>
#include "../lib/list.h"
#include "comm_device.h"
#include <sys/types.h>


typedef struct _sensor
{
	pthread_mutex_t sensor_lock; // handle by controller, not by the sensor self.
	comm_device_t* comm;
	struct list buffer_head;
	unsigned int buf_cnt;
	int device_addr;
	unsigned int rate;

	struct list_elem* (*read_buffer)(struct _sensor*);
	struct list_elem* (*wrivte_buffer)(struct _sensor*, struct list_elem*);
}sensor_t; 
	
	
