#include <stdio.h>
#include <pthread.h>


typedef struct _sensor
{
	pthread_mutex_t lock;
	
	
