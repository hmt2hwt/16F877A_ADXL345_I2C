/************************************************************************
*	Program : i2c.c													    *                                              *
************************************************************************/
#include "i2c.h"

void I2C_init(void)
{
    TRISCbits.TRISC3=1;     //SCK
    TRISCbits.TRISC4=1;     //SDA
    
    SSPSTAT=0x80;       //SMP=1->100khz, 1Mhz, SMP=0->400khz
    SSPCON=0x28;
    SSPCON2=0x00;
    
    SSPADD=49;    //20000Khz/(4*(4+1)) 49->100Khz  4->1Mhz
    
    PIR1bits.SSPIF=0;
}
// SDA and SCK lines are high 
void I2C_wait_idle(void)
{
    while((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}
void I2C_wait(void)
{
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF=0;
}

void I2C_start(void)
{
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
}

void I2C_stop(void)
{
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);
}

void I2C_restart(void)
{
    SSPCON2bits.RSEN=1;
    while(SSPCON2bits.RSEN);
}
//------------------------------------
void I2C_ack(void)
{
    SSPCON2bits.ACKDT=0;
    SSPCON2bits.ACKEN=1;
    
    while(SSPCON2bits.ACKEN);
}

void I2C_nack(void)
{
    SSPCON2bits.ACKDT=1;
    SSPCON2bits.ACKEN=1;
    
    while(SSPCON2bits.ACKEN);   
}

void I2C_write(uint8_t dat)
{
    uint8_t ack=0;
    
	SSPBUF=dat;
    while(SSPSTATbits.BF);        
    I2C_wait_idle();
}

uint8_t I2C_read(void)
{
	uint8_t tmp=0;

	SSPCON2bits.RCEN=1;
	while(!SSPSTATbits.BF);
	tmp=SSPBUF;
    I2C_wait_idle();
    
	return tmp;
}