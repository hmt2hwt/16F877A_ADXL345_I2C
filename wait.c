/************************************************************************
*	Program : wait.c													*								*
************************************************************************/
#include "wait.h"

void delay_ms(uint8_t cnt)
{
	uint8_t i;
	do
	{
		i=4;
		do
		{
			delay_us(249);
			CLRWDT();
		}
		while(--i);
	}
	while(--cnt);
}
//----------------------------------------------
void delay_big_ms(uint16_t cnt)
{
	uint8_t i;
	do
	{
		i=4;
		do
		{
			delay_us(249);
			CLRWDT();
		}
		while(--i);
	}
	while(--cnt);
}
//---------------------------------------------
void delay_sec(uint8_t cnt)
{
	uint8_t i;
	do
	{
		i=4;
		do
		{
			delay_ms(250);
			CLRWDT();
		}
		while(--i);
	}
	while(--cnt);
}
//-------------------------------------------
