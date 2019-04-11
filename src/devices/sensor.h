#include <stdio.h>
#include <pthread.h>
#include "../lib/list.h"
#include <sys/types.h>


typedef struct _sensor
{
	pthread_mutex_t lock;
	struct list buffer_head;
	struct comm_device* com;
	
	struct list_elem* (*read_buffer)(struct _sensor*);
	/* 	args: self
		returns: next element's pointer
		doing: read buffer and remove node from list
	*/
	struct list_elem* (*write_buffer)(struct _sensor*, struct list_elem*);
	
	size_t (*read)(struct _sensor*, char*);
	void (*write)(struct _sensor*, char*, size_t);
}sensor; 
	
	
