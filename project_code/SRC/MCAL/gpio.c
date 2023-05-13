#include "../../HEADERS/MCAL/gpio.h"
#include <stdint.h>
#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/fpu.h"
// Port F init (LED)
void PortF_Init(void){
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // Enable port F clock
  delay = SYSCTL_RCGC2_R;           // Reading register adds a delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Unlock PortF PF0
  GPIO_PORTF_CR_R = 0x1F;           // Allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;          // PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTF_PUR_R = 0x11;          // Enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;          // Enable digital pins PF4-PF0
}

/******************************************/

// Port B init (LCD)
void PortB_Init(void){
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // Enable port B clock
  delay = SYSCTL_RCGC2_R;           // Reading register adds a delay
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // Unlock PortB
  GPIO_PORTB_CR_R = 0xFF;           // Allow changes to PB7-0
  GPIO_PORTB_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // GPIO clear bit PCTL
  GPIO_PORTB_DIR_R = 0xFF;          // PORT B OUTPUT
  GPIO_PORTB_AFSEL_R = 0x00;        // No alternate function
  //GPIO_PORTB_PUR_R = 0x00;        // Enable pullup resistors on PF4,PF0               MITAKE ??
  GPIO_PORTB_DEN_R = 0xFF;          // Enable digital pins PB7-PB0
}

// Port D init
void PortD_Init(void){
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;     // Enable port D clock
  delay = SYSCTL_RCGC2_R;           // Reading register adds a delay
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   // Unlock PortD
  GPIO_PORTD_CR_R = 0xFF;           // Allow changes to PD7-0
  GPIO_PORTD_AMSEL_R = 0x00;        // Disable analog function
  GPIO_PORTD_PCTL_R = 0x00000000;   // GPIO clear bit PCTL
  GPIO_PORTD_DIR_R = 0xFF;          // PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTD_AFSEL_R = 0x00;        // No alternate function
  GPIO_PORTD_PUR_R = 0x00;          // Enable pullup resistors on PF4,PF0
  GPIO_PORTD_DEN_R = 0xFF;          // Enable digital pins PF4-PF0
}




