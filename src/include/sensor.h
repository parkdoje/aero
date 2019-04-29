
#include <pthread.h>
#include "../lib/list.h"
#include "comm_device.h"
#include <sys/types.h>


typedef struct _sensor
{//굳이 쓰레드를 써야할까 ..
	/* need more var?*/
	pthread_mutex_t sensor_lock;
	comm_device_t* comm;
	struct list buffer_head;
	int device_addr;
	unsigned int rate;

	struct list_elem* (*read_buffer)(struct _sensor*);
	struct list_elem* (*write_buffer)(struct _sensor*, struct list_elem*);
}sensor_t; 
	
	
