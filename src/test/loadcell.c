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


int read_packet(uint8_t buf[static 64])
{
    int length = 0 , received = 0; 
    memset(buf, 0x00, 64);
    while(length < 23 && ((received = uart->super.read_byte(uart)) != 0x0a))
    {
        if(received < 0)
        {
           continue;
        }
        buf[length++] = received;
    }

    buf[length] = 0x00;

    return -1;
}

void parse_packet(uint8_t buf[static 64])
{
    struct timespec ts;
    char* cur = NULL, *saved;
    double a;
    int i = 0;
    cur = __strtok_r(buf, ",", &saved);
    do
    {
        if(i == 3)
        {
            a = atof(cur);
            clock_gettime(CLOCK_MONOTONIC, &ts);
            fprintf(result_file, "%d, %d, %f\n", ts.tv_sec, ts.tv_nsec / 1000000, a);// sec, ms, kgf 
            
            break;
        }
        i++;
        printf("Test %s\n",cur);
    }
    while((cur = __strtok_r(NULL, ",", &saved)) != NULL);
    

}

int shutdown(int sig)
{
    intflag = 1;
}

int main(int argc, char* argv[])
{
    // 1st arg = /dev/something, 2nd arg = baud rate, result_file_name

    init_serial(argv[1], atoi(argv[2]));
    printf("%s is dev interface , %s is baudrate\n", argv[1], argv[2]);
    uint8_t buf[64] = {0, };
    
    signal(SIGINT, shutdown);
    result_file = fopen(argv[3], "a+");

    memcpy(buf, argv[4], sizeof(buf));

    uart->data_flush(uart);
    while(!intflag)
    {
        read_packet(buf);
        parse_packet(buf);
        memset(buf, 0x00, sizeof(buf));
    }

    fclose(result_file);

    return 0;
}