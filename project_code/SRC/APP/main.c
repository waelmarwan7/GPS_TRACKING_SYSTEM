/*
 * TRACKING_SYSTEM_PROJECT
 *
 *  FINISHED on: May 10, 2023
 *      Author: marwan wael mahmoud abbas
 */

#include "../../HEADERS/MCAL/gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "TM4C123.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "../../HEADERS/MCAL/UART.h"
#include "string.h"
#include "stdlib.h"
#include "../../HEADERS/HAL/GPS.h"
#include "../../HEADERS/HAL/lcd.h"

int main(){
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_INT | SYSCTL_MAIN_OSC_DIS); // to convert the frequency of tiva c from 80Mhz to 16Mhz
    PortB_Init();
    PortD_Init();
    PortF_Init();
    SysTick_Init();
    UART5_init();

    lcd_init();
    lcd_cmd(lcd_Clear);
    lcd_cmd(lcd_Home);
    lcd_str("START WALKING ..");
    delay_ms(500);

    GPIO_PORTF_DATA_R = 0x02;

    while(1){
    readGPS();

    }
}

