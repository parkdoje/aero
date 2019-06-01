#include "../include/serial.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

serial_dev_t* uart = NULL;
FILE* result_file = NULL;
static int intflag = 0;
static int flag = 0;


int read_packet(uint8_t buf[static 64])
{
    int length = 0 , received = 0; 

    memset(buf, 0x00, 64);
    while(length < 23 &&((received = uart->super.read_byte(uart)) != 0x0a))
    {
        
        if(received < 0)
        {
            return -1;
        }
        buf[length] = received;
        length += 1;
    }

    buf[length] = 0x00;

    return 0;
}

void parse_packet(uint8_t buf[static 64])
{
    struct timespec ts;
    char* cur = NULL, *saved;
    double a;
    int i = 0;
    /*
    printf("%s\n", buf);
    for(int i = 0; i < 64; i++)
    {
        printf("%x ", buf[i]);
        if(buf[i] == 0x00)
            break;
    }
    */
   if(strlen(buf) == 0)
        return;
    clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("%d %d %s\n",ts.tv_sec, ts.tv_nsec, buf);
	fprintf(result_file, "%d %d %s\n",ts.tv_sec, ts.tv_nsec, buf);
    memset(buf, 0x00, 64);
    /*
    cur = __strtok_r(buf, ",", &saved);
    do
    {
        printf("%s %d \n", cur, strlen(cur));
    }
    while((cur = __strtok_r(NULL, ",", &saved)) != NULL);
    */

}

int shutdown(int sig)
{
    intflag = 1;
}

int main(int argc, char* argv[])
{
    // 1st arg = /dev/something, 2nd arg = baud rate, result_file_name

	if(argc == 1)
	{
		printf("```");
		return 0;
	}
    printf("%s is dev interface , %s is baudrate\n", argv[1], argv[2]);
    uart = init_serial(argv[1], atoi(argv[2]));
    uint8_t buf[64] = {0, };
    
    signal(SIGINT, shutdown);
    result_file = fopen(argv[3], "w+");

    uart->data_flush(uart);//discard prev data
    while(!intflag)
    {
        usleep(100* 1000);
        read_packet(buf);
        parse_packet(buf);
    }

    fclose(result_file);

    return 0;
}
