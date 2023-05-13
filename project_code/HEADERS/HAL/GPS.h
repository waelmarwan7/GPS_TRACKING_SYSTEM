#ifndef GPS_H_
#define GPS_H_

#define PI            3.1415926
#define Earth_Radius    6371000
#define GPS_LOGNAME   "$GPGGA,"

void readGPS(void);
void calc_distance(void);

#endif
