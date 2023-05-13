#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "TM4C123.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "../../HEADERS/MCAL/UART.h"
void UART5_init(void){
    SYSCTL_RCGCUART_R |= (1<<5); // Enable UART5 clock
    SYSCTL_RCGCGPIO_R |= (1<<4); // Enable GPIOE clock
    while((SYSCTL_PRGPIO_R & (1<<4)) == 0){}; // Wait for GPIOE clock to be ready

    UART5_CTL_R &= ~(1<<0); // Disable UART5

    // Calculate baud rate divisors for 16 MHz system clock and 9600 baud rate
    // BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
    // UARTSysClk = 16 MHz, ClkDiv = 16, Baud Rate = 9600
    // BRD = 16,000,000 / (16 * 9600) = 104.16667
    // BRDI = integer part of BRD = 104
    // BRDF = fractional part of BRD = 0.16667
    // UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) = 11
    UART5_IBRD_R = 104; // Set integer baud rate divisor
    UART5_FBRD_R = 11; // Set fractional baud rate divisor

    UART5_LCRH_R = 0X0070; // Set line control (8 bits data, 1 stop bit, no parity)
    UART5_CTL_R = 0X0301; // Enable UART5 and its transmitter and receiver
    GPIO_PORTE_AFSEL_R |= (1<<4) | (1<<5); // Enable alternate function for PE4 and PE5
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000; // Configure PE4 and PE5 for UART
    GPIO_PORTE_DEN_R |= 0X30; // Enable digital function for PE4 and PE5
    GPIO_PORTE_AMSEL_R &= ~0X30; // Disable analog function for PE4 and PE5

    GPIO_PORTE_DIR_R |= (1<<5); // Set PE5 as output
    GPIO_PORTE_DIR_R &= ~(1<<4); // Set PE4 as input
}

char receive_char(){
    while((UART5_FR_R&0x10)!=0);
    return (char)(UART5_DR_R&0xFF);
    }

