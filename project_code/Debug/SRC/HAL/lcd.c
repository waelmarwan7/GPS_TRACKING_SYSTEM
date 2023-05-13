#include "../../HEADERS/MCAL/gpio.h"
#include <stdint.h>
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/fpu.h"
#include "../../HEADERS/HAL/lcd.h"




/*******************************************
 * Function: SysTick timer initialization
 * Parameters : void
 * Return type: void
 *
 ******************************************/
void SysTick_Init(void){
    NVIC_ST_CTRL_R = 0;                 // Disable systick timer
    NVIC_ST_RELOAD_R = 12-1;        // Load 80 counts to reload register for 1 microsecond count
    NVIC_ST_CURRENT_R = 0;          // Clear the counter
    NVIC_ST_CTRL_R = 5;                 // Enable the counter and system CLK
}

/******************************************/
/* Function: Delays n microsecond
 * Parameters : void
 * Return type: void
 */
void delay_us(int count){
    int i;
    for( i = 0; i<count; i++){
        while((NVIC_ST_CTRL_R&0x10000)==0){}        // Loop while count flag is down
    }
}

/******************************************/
/* Function: Delays n millisecond
 * Parameters : void
 * Return type: void
 */

void delay_ms(int count)
{
    int i;
    for( i = 0; i<(count*1000); i++)
    {
        delay_us(1);        // 1 us                             // loop for count milliseconds
    }
}

void lcd_init(void)
{
    lcd_cmd(Set5x7FontSize);
    lcd_cmd(four_bit_mode);
    lcd_cmd(lcd_EntryMode);
    lcd_cmd(lcd_Clear);
    lcd_cmd(lcd_DisplayOn);
}

void lcd_cmd(unsigned char cmd)
{
    lcd_write(cmd & 0xF0, 0);
    lcd_write(cmd<<4, 0);
    if(cmd < 4)
    {
        delay_ms(2);
    }
    else
    {
        delay_us(40);
    }
}

void lcd_write(unsigned char c, unsigned char ctrl)
{
    c &= 0XF0;
    ctrl &= 0x0F;
    GPIO_PORTB_DATA_R = c | ctrl;
    GPIO_PORTB_DATA_R = c | ctrl | EN;
    delay_us(1);
    GPIO_PORTB_DATA_R = c;
    GPIO_PORTB_DATA_R = 0;
}

void lcd_char(unsigned char data, unsigned char ctrl)
{
    lcd_write(data&0xF0, RS);
    lcd_write(data<<4, RS);
    delay_us(40);
}

void lcd_str( char *str){
    int i;
    for( i = 0; *str!=0; i++)
    {
        lcd_char(*(str++),RS);
    }
}






