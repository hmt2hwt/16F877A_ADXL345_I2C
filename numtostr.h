/**************************************************************************
*	Program : numtostr.h												  *
*	Version : 0.510														  *
*	Author	: hmt2hwt						                              *
*	Date	: 18.03.2014												  *
*	Function:                                                             *                                                                        *
***************************************************************************/
#ifndef NUMTOSTR_H
#define NUMTOSTR_H

#include <stdio.h> 
#include <math.h> 
#include <string.h>
#include <stdint.h>

uint8_t mc_strcpy(uint8_t *dest, uint8_t *source);
uint8_t iToStr(int32_t intVal, uint8_t *str, uint8_t digit);
uint8_t fToStr(float fVal, uint8_t *str, uint8_t afterpoint);
#endif

