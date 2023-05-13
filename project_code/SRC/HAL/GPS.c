#include "../../HEADERS/MCAL/gpio.h"
#include <stdint.h>
#include "../../HEADERS/HAL/GPS.h"
#include "../../HEADERS/HAL/lcd.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "../../HEADERS/MCAL/UART.h"
#include "stdio.h"
#include "TM4C123.h"
#include "driverlib/fpu.h"  // TO ENABLE floating point in tiva c

// Global variables declaration
volatile double distance = 0.0;
static volatile double points[4];
static volatile int i = 0;
char string[10];


//$GPGGA, 123519, 3003.900, N, 03116.624, E, 1, 08, 0.9, 545.4, M, 46.9, M, , *47      <final point>
void readGPS(void){
   char i=0,c, GPSValues[100], parseValues[12][20], *token;
       do
       {
          while(receive_char() != GPS_LOGNAME[i]);
             i++;

       }while(i!=7);
                                      c= receive_char();
                                     while(c != '*'){
                                        GPSValues[i] = c;
                                        c = receive_char();
                                        i++;
                                    }

                                    i = 0;
                                    token = strtok(GPSValues, ",");
                                    while(token != NULL)
                                    {
                                        strcpy(parseValues[i], token);
                                        token = strtok(NULL, ",");
                                        i++;
                                    }
                                    if(strcmp(parseValues[5], "1") == 0)
                                    {
                                        lcd_cmd(lcd_Clear);
                                        lcd_cmd(lcd_Home);
                                        lcd_str("Lat:");
                                        lcd_cmd(second_row);
                                        lcd_str(parseValues[1]);
                                        delay_ms(500);
                                        lcd_cmd(lcd_Clear);
                                        lcd_cmd(lcd_Home);
                                        lcd_str("Long:");
                                        lcd_cmd(second_row);
                                        lcd_str(parseValues[3]);
                                        delay_ms(500);

                                        if(parseValues[1][0]=='3'&&parseValues[1][1]=='0'&&parseValues[1][2]=='0'&&parseValues[1][3]=='3'&&parseValues[1][5]=='9'&&parseValues[1][6]=='0'&&parseValues[3][6]=='6'&&parseValues[3][7]=='2')//(final point check)
                                        {
                                             lcd_cmd(lcd_Clear);
                                             lcd_cmd(lcd_Home);
                                             GPIO_PORTF_DATA_R=0X08;
                                             lcd_str("Destination");
                                             lcd_cmd(second_row);
                                             lcd_str("Reached !!");
                                             delay_ms(500);
                                         }
                                         else if(parseValues[1][0]=='3'&&parseValues[1][1]=='0'&&parseValues[1][2]=='0'&&parseValues[1][3]=='3'&&parseValues[1][5]=='9'&&parseValues[1][6]=='1'&&parseValues[3][6]=='6'&&parseValues[3][7]=='2')//(5m  point check)
                                         {
                                             GPIO_PORTF_DATA_R=0X0A;
                                             lcd_cmd(lcd_Clear);
                                             lcd_cmd(lcd_Home);
                                             lcd_str("5m Away");
                                             lcd_cmd(second_row);
                                             lcd_str("keep going...");
                                             delay_ms(500);
                                         }
                                         else
                                         {
                                             GPIO_PORTF_DATA_R=0X02 ;
                                             lcd_cmd(lcd_Clear);
                                             lcd_cmd(lcd_Home);
                                             lcd_str("CONTINUE ...");
                                             delay_ms(700);               // bigger delay for lcd screen to display continously without stopping ..
                                         }



                                    }
                                }


/* function that calculate total distance      (((((HARVALSINE LAW FUNCTION ))))                  <<THERE'S PROBLEM ...>>
void calc_distance(void){


       (calculate latitude)


       double latitude = 0.0, longitude = 0.0, min = 0.0, sec = 0.0, result = 0.0;
        int j = 0, deg;
        deg = latitude/100;
        min = latitude - (double)(deg*100);
        sec = min/60.0;
        result = deg + sec;
        if(parseValues[2][0] == 'S') result  *=-1;
        points[j] = result;
           j++;

        (calculate longitude)


        deg = longitude/100;
        min = longitude - (double)(deg*100);
        sec = min/60.0;
        result = deg + sec;
        if(parseValues[4][0] == 'W') result *=-1;

        points[j] = result;
        j++;

        if(j==4)
        {

                double lat_1 = points[0]*PI/180;
                double lat_2 = points[2]*PI/180;
                double d_lat = lat_2 - lat_1;
                double d_lon = (points[3] - points[1])*PI/180;

                //a = sin?(dlatDifference/2) + cos(lat1).cos(lat2).sin?(dlonDifference/2) <<<<< function
                double a = sin(d_lat/2)*sin(d_lat/2) + cos(lat_1)*cos(lat_2)*sin(d_lon)*sin(d_lon);
                //c = 2.atan2(va, v(1-a))
                double c = 2*atan2(sqrt(a), sqrt(1-a));
                //dx = R.c <<<<< dx
                double dx = Earth_Radius*c;

                distance += dx; // <<<<  total dis

                 LCD
                lcd_cmd(lcd_Clear);
                lcd_cmd(lcd_Home);
                lcd_str("Dis:");
                lcd_cmd(second_row);
                LCD_intgerToString((int)distance);

                   j = 2;
                  points[0] = points[2]; //make second point as first point for third point (latitude)
                  points[1] = points[3]; //make second point as first point for third point (longitude)

       }
}
*/
