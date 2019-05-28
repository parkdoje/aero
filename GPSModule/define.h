#ifndef DEFINES_H_
#define DEFINES_H_

#define GPS_DEBUG

#define ACCESS_PATH

#define GGA         "GGA"
#define GSA         "GSA"
#define GSV         "GSV"
#define RMC         "RMC"
#define VTG         "VTG"

#define MODULE_NAME         "GPS"
#define BUF_SIZE        256
#define TIMEOUT         100
#define MINCHAR         32

void serial_settinf(int gps_sfd);
int gps_open();
void gps_read(int gps_rfd);

#endif
