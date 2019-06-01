#include "../include/serial.h"
#include "../include/sensor.h"
#include "../include/gpio.h"
#include "../include/mav/my_link/mavlink.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>

serial_dev_t* uart = NULL;
FILE* result_file = NULL;
int flag = 0;

void int_handler(int sig)
{
    static int count = 0;
    if (count == 0)
    {
        mavlink_message_t msg;
        mavlink_msg_command_pack(1, 0, &msg, 1);
        uint8_t buf[MAVLINK_MAX_PACKET_LEN];
        int len = mavlink_msg_to_send_buffer(buf, &msg);
        uart->super.write_nbyte(uart, len, buf);
        count += 1;
    }
    fclose(result_file);
    flag = 1;
}

static int rcv_frm_rf()
{
    mavlink_message_t tmp_msg;
    mavlink_status_t status;
    uint8_t ch;
    uint8_t stat;
    int cnt = -2;

    //TO DO: this method can discard the packet need another method
    while((ch = uart->super.read_byte(uart)) >= 0)
    {
        stat = mavlink_parse_char(0, ch, &tmp_msg, &status);
        if (stat)
        {
            if(stat == MAVLINK_FRAMING_BAD_CRC)
            {
                cnt = -1;
                break;
            }
            return process_packet(&tmp_msg);
        }
    }
    return cnt;
}
int process_packet(mavlink_message_t* msg)
{
    int stat = -1;
    mavlink_accel_t acc; 
    mavlink_gyro_t gyro;
    switch (msg->msgid)
    {
    case ACCEL:
        
        mavlink_msg_accel_decode(msg, &acc);
        printf("accel received! %f %f %f\n", acc.x, acc.y, acc.z);
        goto success;
    case GYRO:
       
        mavlink_msg_gyro_decode(msg, &gyro);
        goto success;
        break;
        //not yet implemented
    case POS:
        break;
    case NAV:
        break;
    case BARO:
        break;
    
    default:
        break;
    }
    return -1;

    success:
        return 0;
}

void init_devices(const char* dev, int baud)
{
    result_file = fopen("received_data", "a+");
    uart = init_serial(dev, baud);
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("usage: gcs /dev/ttyUSBx baudrate");
        return -1;
    }

    init_devices(argv[1], atoi(argv[2]));
    signal(SIGINT, int_handler);

    while(!flag)
    {
        rcv_frm_rf();
    }
}