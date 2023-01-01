/************************************************************************
*	Program : i2c.h													    *
*	Version : 0.510														*
*	Author	: hmt2hwt                                                   *
*	Date	: 10.09.2012                                                *
*   Modified: 21.08.2017                                                *
*	Function:                                                           *
************************************************************************/

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define NACK    0
#define ACK     1

void I2C_init(void);
void I2C_wait(void);
void I2C_wait_idle(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_restart(void);
void I2C_ack(void);
void I2C_nack(void);

void I2C_write(uint8_t dat);
uint8_t I2C_read(void);

#endif	/* I2C_H */

