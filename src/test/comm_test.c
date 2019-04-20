#include "../include/serial.h"
#include <stdio.h>
#include <stdlib.h>



int main()
{
	int fd = serial_open("/dev/ttyUSB0", 57600);
	const char* h = "hello world!";
	uint8_t* buff = malloc(sizeof(uint8_t)* 32);
	int buf;
	printf("%d\n", fd);
	while(1)
	{
		buf = serial_nread(fd, 0, 32, buff);
		printf("%d,", buf);
		printf("%s\n", (char*)buff);
		sleep(1);
	}
}


