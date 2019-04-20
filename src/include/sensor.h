#include <stdio.h>
#include <pthread.h>
#include "../lib/list.h"
#include <sys/types.h>


typedef struct _sensor
{
	pthread_mutex_t buf_lock;
	struct list buffer_head;
	struct comm_device* com;
	
	struct list_elem* (*read_buffer)(struct _sensor* self);
	/* 	args: self
		returns: next element's pointer
		doing: read buffer and remove node from list
	*/
	struct list_elem* (*write_buffer)(struct _sensor* self);
	/*
		@self : self..
	*/
	logic* algo;
}sensor; 

typedef struct sensor_logic
{
	
	
}logic;
	
