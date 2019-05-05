#include "../include/i2c.h"
#include "../include/serial.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	i2c_dev_t* i2c = init_i2c("/dev/i2c-1");


	
	return 0;
}

