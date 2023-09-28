/************************************************************************
*	Program : 16F877A + I2C + ADXL345									*
*	Version : 0.500														*
*	Author	: hmt2hwt                                                   *                                                        *
*   20Mhz                                                               *
************************************************************************/
#pragma warning push
#pragma warning disable 520     //function xxx is never called
#pragma warning disable 1498    //pointer (xxx@yyy) in expression may have no targets
                                
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "gpio.h"
#include "wait.h"
#include "usart.h"
#include "numtostr.h"
#include "ADXL345.h"

#pragma warning pop

uint8_t send_flag;

void USART_decode_code(void);

void main(void)
{
    uint8_t uptr[16]={0}, uptr_cnt=0, dt=0, eol=13, spc=32;
    uint16_t led_counter=0;
    int16_t accX=0, accY=0, accZ=0;
    
    GPIO_init();
    USART_init();
    ADXL345_init();
    PORTCbits.RC2=1;
   
    uptr_cnt=mc_strcpy(uptr,(uint8_t *)"I2C ADXL345=");
    USART_write(uptr,uptr_cnt);
    
    dt=ADXL345_read(ADXL345_DEVID);
    uptr_cnt=iToStr(dt,uptr,3);
    USART_write(uptr,uptr_cnt);
    USART_write(&eol,1);
    
    ADXL345_write(ADXL345_BW_RATE,0x0A);        //ODR->100
    delay_ms(5);
    ADXL345_write(ADXL345_DATA_FORMAT,0x0B);    //+-16g 13bit
    delay_ms(5);
    ADXL345_write(ADXL345_POWER_CTL,0x08);
    delay_ms(5);
    
    while(true)
    {   
        //USART_decode_code();
        
        ADXL345_read_axis_LSB(&accX, &accY, &accZ);
            
        uptr_cnt=iToStr(accX,uptr,5);
        USART_write(uptr,uptr_cnt);
        USART_write(&spc,1);
        
        uptr_cnt=iToStr(accY,uptr,5);
        USART_write(uptr,uptr_cnt);
        USART_write(&spc,1);
        
        uptr_cnt=iToStr(accZ,uptr,5);
        USART_write(uptr,uptr_cnt);        
        
        USART_write(&eol,1);
    //--------------------------------------
        if(led_counter >= 50)
        {
            TEST_LED = (~TEST_LED);
            led_counter=0;
        }
        delay_us(249);
        delay_us(249);
        led_counter++;
    //---------------------------------------
    }
}
// [W wrReg wrDat] - [R wrReg wrDat] 
//[R 000 000] read DEV_ID  [R 050 000] Read Reg 50
//[W 030 255] OffsetX=255
void USART_decode_code(void)
{
    uint8_t rec[16]={0}, str[16]={0}, uptr_cnt=0, eol=13, spc=32;
    uint8_t wrReg, wrDat;
    uint8_t a=0,b=0,c=0;
            
    uptr_cnt=USART_read(rec);
    
    if(uptr_cnt > 0)
    {
        if(rec[0] == '[' && rec[10] == ']')
        {
            if(rec[1] == 'W')
            {
                a=(rec[3]-48)*100;
                b=(rec[4]-48)*10;
                c=(rec[5]-48)*1;
                wrReg=a+b+c;
                
                a=(rec[7]-48)*100;
                b=(rec[8]-48)*10;
                c=(rec[9]-48)*1;
                wrDat=a+b+c;
                
                ADXL345_write(wrReg, wrDat);
                uptr_cnt=mc_strcpy(str, (uint8_t *)"WriteOK");
                USART_write(str, uptr_cnt);
                USART_write(&eol,1);
            }
            if(rec[1] == 'R')
            {
                a=(rec[3]-48)*100;
                b=(rec[4]-48)*10;
                c=(rec[5]-48)*1;
                wrReg=a+b+c;
                                
                wrDat=ADXL345_read(wrReg);
                uptr_cnt=iToStr(wrReg,str,3);
                USART_write(str, uptr_cnt);
                USART_write(&spc,1);
                uptr_cnt=iToStr(wrDat,str,3);
                USART_write(str, uptr_cnt);
                USART_write(&eol,1);
            }
            if(rec[1] == 'A')
            {
                if(rec[3] == '1')
                    send_flag=1;
                if(rec[3] == '0')
                    send_flag=0;
                else
                {
                    uptr_cnt=mc_strcpy(rec, (uint8_t *)"Command Error");
                    USART_write(rec, uptr_cnt);
                    USART_write(&eol,1);    
                }
            }
        }
        else
        {
            uptr_cnt=mc_strcpy(rec, (uint8_t *)"Command Error");
            USART_write(rec, uptr_cnt);
            USART_write(&eol,1);
        }
    }    
}
