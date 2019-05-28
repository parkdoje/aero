
#include <pthread.h>
#include "../lib/list.h"
#include "comm_device.h"
#include <sys/types.h>

enum data_type 
{
	ACCEL,
	GYRO,
	BARO,
	GPS
}data_type;


typedef struct _data_t
{
	uint8_t type;
	struct timespec ts; 
	float val[3];
	struct list_elem elem;	
}data_t;


typedef struct _sensor
{
	comm_device_t* comm;
	int device_addr;
	unsigned int rate;
}sensor_t; 
	
	
