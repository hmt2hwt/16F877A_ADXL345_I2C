/************************************************************************
*	Program : gpio.h													                            *
*	Version : 0.500														                            *
*	Author	: hmt2hwt						                                          *
*	Date	: 10.09.2012												                            *
*	Function: GPIO_init()                                                 *
************************************************************************/

#ifndef GPIO_H
#define	GPIO_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define TEST_LED        PORTDbits.RD2
#define TEST_LED_TRIS   TRISDbits.TRISD2

void GPIO_init(void);

#endif	/* GPIO_H */

