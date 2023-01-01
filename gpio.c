/************************************************************************
*	Program : gpio.c													*                                               *
************************************************************************/
#include "gpio.h"

void GPIO_init(void)
{
    //TEST_LED_TRIS=0;
    //TEST_LED=0;
    
    PORTA=0x00;
    TRISA=0x00;
    
    PORTB=0x00;
    TRISB=0x00;
    
    PORTC=0x00;
    TRISC=0x00;
    
    PORTD=0x00;
    TRISD=0x00;
    
    PORTE=0x00;
    TRISE=0x00;
}
