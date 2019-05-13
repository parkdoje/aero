#include "../include/serial.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

serial_dev_t* uart = NULL;
FILE* result_file = NULL;


int read_packet(uint8_t buf[static 64])
{
    int length = 0 , received = 0; 
    memset(buf, 0x00, 64);
    while(length < 22)
    {
        received = uart->super.read_byte(uart);
        if(received < 0)
            continue;
        buf[length] = received;
        length +=1;
    }
    buf[length + 1] = 0x00;

    if(buf[length] == 0x0A)
        return 0;
    
    return -1;
}

void parse_packet(uint8_t buf[static 64])
{
    char* cur = NULL, *saved;
    double a;
    int i = 0;
    cur = __strtok_r(buf, ",", &saved);
    do
    {
        a = atof(cur);
        if (a == 0) 
        {
            continue;
        }
        printf("%f\n", a);

    }
    while((cur = __strtok_r(NULL, ",", &saved)) != NULL);
}

int main(int argc, char* argv[])
{
    // 1st arg = /dev/something, 2nd arg = baud rate

    struct timespec ts;
    uint8_t buf[64];
    memcpy(buf, argv[3], 16);
    //printf("%s\n", argv[3]);
    parse_packet(buf);

    int len = 0;


    clock_gettime(CLOCK_REALTIME_COARSE, &ts);
    int start = ts.tv_sec;   
    int cur = 0;
    memset(buf, 0x00, 64);
    //uart->data_flush(uart);
    uint8_t data = 0;
    
    return 0;
}