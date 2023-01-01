/************************************************************************
*	Program : wait.h													*
*	Version : 0.512														*
*	Author	: Shane Tolmie 					    						*
*   Modified: hmt2hwt												*
*	Date	: 10.09.2012												*
*	Function: delay_us(x) (for 4MHZ x>=4, for 8MHZ x>=2) 1<=x<=255	    *
*			  delay_ms(x)		1<=x<=255								*
*			  delay_big_ms(x)	1<=x<=65535					            *
*			  delay_sec(x)		1<=x<=255								*
************************************************************************/
//for 20MHZ
//cnt*(1ms+0.8uS)+1.4uS
//1ms  ->  1*(1+0.8)+1.4=1mS+2.2uS    =  1002.2uS
//2ms  ->  2*(1+0.8)+1.4=2mS+3uS      =  2003.0uS
//250ms->250*(1+0.8)+1.4=250mS+201.4uS=250201.4uS
//255ms->255*(1+0.8)+1.4=255ms+205.4uS=255205.4uS
//------------------------------------------------
//delay_us(1)=1.6uS
//delay_us(x+1)uS = x>=2
//x=1 (8  clock) -> 1.6uS
//x=2 (15 clock) -> 3us
//x=3 (20 clock) -> 4uS
//x=4 (25 clock) -> 5uS
//x=5 (30 clock) -> 6uS
//------------------------------------------------
#ifndef WAIT_H
#define WAIT_H

//#define PIC16 0x01
//#define PIC18 0x02
//----------------------------------------
#define PIC_CLK 20000000
//----------------------------------------
//#define PIC_TYPE PIC16
//----------------------------------------

#include <xc.h>
#include <stdint.h>

uint8_t delayus_variable;
//------------------16F series Begin------------------------------------------------------------
#if	defined(__PICC__)			//#if (PIC_TYPE==PIC16)
//--------------------------------------------------------------------------------
	#if PIC_CLK==4000000
		#define DelayDivisor 4
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 2")
//		#warning --delay_us(x), be careful,(must be x>=4)
	#elif PIC_CLK==8000000
		#define DelayDivisor 2
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 2")
//		#warning --delay_us(x), be careful,(must be x>=2)
	#elif ((PIC_CLK==16000000)||(PIC_CLK==16257000))
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 2")
	#elif PIC_CLK==20000000
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop"); asm("nop")
		#define Jumpback asm("goto $ - 3")
	#elif PIC_CLK==32000000
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop")
		#define Jumpback asm("goto $ - 6")
	#else
		#error delay.h - please define pic_clk correctly
	#endif

	// ---- (5xdelayus_variable+1)*cpu_clock(uS) -- 20mhz x=1 -> 6*0,2=1.2uS
	#define delay_us(x) { \
				delayus_variable=(uint8_t)(x/DelayDivisor); \
				WaitFor1Us; } \
				asm("decfsz _delayus_variable,f"); \
				Jumpback;
#endif
//-------------------16F series end---------------------------------------------------------
//-------------------18F series begin-------------------------------------------------------
#if	defined(__PICC18__)				//#if (PIC_TYPE==PIC18)
	#if PIC_CLK==4000000
		#define DelayDivisor 4
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 4") //on PIC18F, it is asm("goto $ - 4") and on PIC16F core it is asm("goto $ - 2")
//		#warning --delay_us(x), be careful,(must be x>=4)
	#elif PIC_CLK==8000000
		#define DelayDivisor 2
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 4")
//		#warning --delay_us(x), be careful,(must be x>=2)
	#elif PIC_CLK==16000000
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop")
		#define Jumpback asm("goto $ - 4")
	#elif PIC_CLK==20000000
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop"); asm("nop")
		#define Jumpback asm("goto $ - 6")
	#elif PIC_CLK==32000000
		#define DelayDivisor 1
		#define WaitFor1Us asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop")
		#define Jumpback asm("goto $ - 12")
	#else
		#error delay.h - please define PIC_CLK correctly
	#endif

	#define delay_us(x) { \
				delayus_variable=(uint8_t)(x/DelayDivisor); \
				asm("movlb (_delayus_variable) >> 8"); \
				WaitFor1Us; } \
				asm("decfsz (_delayus_variable)&0ffh,f"); \
				Jumpback;

#endif
//-------------------18F series end---------------------------------------------------------
//-------------------functions----------------------------------------
void delay_ms(uint8_t);
void delay_big_ms(uint16_t);
void delay_sec(uint8_t);

#endif