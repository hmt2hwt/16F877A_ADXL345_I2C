/************************************************************************
*	Program : numtostr.c											    *                                               *
************************************************************************/
#include "numtostr.h"

uint8_t mc_strcpy(uint8_t *dest, uint8_t *source)
{
	uint8_t count=0;
	
	while(*source != '\0')
	{
		dest[count]=*source++;
		count++;
	}
	return count;	
}

void reverse(uint8_t *str, uint16_t len) 
{ 
	uint16_t i=0, j=len-1, temp=0;
	
	while (i < j) 
	{ 
		temp = str[i]; 
		str[i] = str[j]; 
		str[j] =(uint8_t) temp; 
		i++; 
		j--; 
	} 
} 

uint32_t ipow(uint16_t ibase, uint16_t iexponent)
{
    uint32_t result=1;
    for(;iexponent > 0;iexponent--)
        result *= ibase;
    return result;
}

uint8_t iToStr(int32_t intVal, uint8_t *str, uint8_t digit) 
{ 
	uint8_t i = 0;
	uint8_t sign=0;

	if(intVal < 0)
	{
		intVal*=(-1);
		sign=1;
	}
			
	while (intVal) 
	{ 
		str[i++] =(intVal%10) + '0'; 
		intVal/=10; 
	} 
	
	if(sign==1)
		str[i++]='-';
  
    while ( (i  <  digit)&&(sign==0)) 
        str[i++] = '0'; 
    
	reverse(str, i); 
	str[i] = '\0';

	return i; 
}

uint8_t fToStr(float fVal, uint8_t *str, uint8_t afterpoint) 
{
	uint8_t sign=0, i=0, tmp=0;
	int32_t ipart=0;
	float fpart=0.0;
	
	if(fVal < 0.0f)
	{
		fVal*=(-1.0f);
		sign=1;
	}
	ipart = (int32_t)fVal; 
	fpart = fVal - (float)ipart; 
	if(sign==1)
		ipart*=(-1);
	
	i = iToStr(ipart, str, 1); 

	if (afterpoint != 0) 
	{ 
		str[i] = '.'; 
		
		fpart =fpart * ipow(10, afterpoint);
		
		tmp=i+1;
		tmp+=iToStr((int32_t)fpart, str+i+1, afterpoint); 
	}
	return tmp;
} 