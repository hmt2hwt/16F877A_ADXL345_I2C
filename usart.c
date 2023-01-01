/************************************************************************
*	Program : usart.c													    *                                              *
************************************************************************/
#include "usart.h"

void USART_init(void)
{
    USART_TX_PIN=0;
    USART_RX_PIN=0;
    USART_TX_PIN_TRIS=0;
    USART_RX_PIN_TRIS=1;
    
    SPBRG=BAUD_VAL;    //BRGH=1,38400
    TXSTA=0x20;
    TXSTAbits.BRGH=BRGH_SET;
    RCSTA=0x90;
}

void USART_write(uint8_t *data, uint8_t count)
{
    for(uint8_t i=0;i<count;i++)
    {
        while(!TXSTAbits.TRMT)  //PIR1bits.TXIF
        {
            //write timeout
        }
            TXREG=data[i];
    }
}

uint8_t USART_read(uint8_t *data)
{
    uint8_t i=0;
    uint16_t timeout=0;   

    while(true)
    {
        if(RCSTAbits.OERR)              // OERR only readable
        {               				// overrun error
            RCSTAbits.CREN=0;     		// Restart USART
            RCSTAbits.CREN=1;
        }
        if(RCSTAbits.FERR)
        {
            RCREG=RCREG;	 			// if error Flush buffer
            RCREG=RCREG;
            RCREG=RCREG;
        }
        while(!PIR1bits.RCIF)           //only readble
        {
            ++timeout;
            if(timeout >= TIME_OUT)
                return i;			//i=0 no data (timeout), i > 0 read data byte            
        }
        timeout=0;
        data[i]=RCREG;
        i++;
        if(i > USART_BUFFER)		//buffer overflow
        	i=0;                    //reset data buffer no data
    }
    return 0;						// no data
}

