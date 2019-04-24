#include <stdio.h>
#include <pthread.h>
#include "../lib/list.h"
#include <sys/types.h>


typedef struct _sensor
{//굳이 쓰레드를 써야할까 ..
	pthread_mutex_t sensor_lock;
	struct list buffer_head;
	int device_addr;
	struct comm_device* com;
	struct list_elem* (*read_buffer)(struct _sensor*);
	/* 	args: self
		returns: next element's pointer
		doing: read buffer and remove node from list
	*/
	struct list_elem* (*write_buffer)(struct _sensor*, struct list_elem*);	
}sensor; 
	
	
