/************************************************************************
*	Program : usart.h													*
*	Version : 0.520														*
*	Author	: hmt2hwt						                            *
*	Date	: 19.10.2012												*
*	Function:USART_init()                                               *
*            USART_write(uint8_t *, uint8_t);                           *
*            uint8_t USART_read(uint8_t *);                             *
************************************************************************/
#ifndef USART_H
#define	USART_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define USART_TX_PIN        PORTCbits.RC6
#define USART_TX_PIN_TRIS   TRISCbits.TRISC6
#define USART_RX_PIN        PORTCbits.RC7
#define USART_RX_PIN_TRIS   TRISCbits.TRISC7

#define USART_BUFFER        32			//bytes
#define BRGH_SET            1			//baud speed
#define BAUD_VAL            32			//38400 20Mhz
#define TIME_OUT            100       	//timeout 100ms (3,6uS step for 20Mhz)

void USART_init(void);
void USART_write(uint8_t *, uint8_t);
uint8_t USART_read(uint8_t *);

#endif	/* USART_H */

