/************************************************************************
*	Program : ADXL345.h                                                   *
*	Version : 0.510                                                       *
*	Author	: hmt2hwt                                                      *
*	Date	: 10.09.2017                                                     *
* Modified: 21.08.2019                                                  *
*	Function:                                                             *
*   CKP=1  CKE=0   for SPI                                              *
************************************************************************/
#ifndef ADXL345_H
#define	ADXL345_H

#include <xc.h>
#include "i2c.h"
 
//I2C ADDRESS                           //0x1D   3A write 3B read  (SDA=ADDR 1)
#define ADXL345_I2C_ADR         0x53    //0x53   A6 write A7 read  (SDA=ADDR 0)
#define ADXL345_I2C_ADR_WR      0xA6
#define ADXL345_I2C_ADR_RD      0xA7

// ADXL345 ID
#define ADXL345_ID              0xE5

//for SPI
#define ADXL345_WRITE_SINGLE    0x00
#define ADXL345_WRITE_MULTIPLE  0x40
#define ADXL345_READ_SINGLE     0x80
#define ADXL345_READ_MULTIPLE   0xC0

// ADXL345 Registers
#define	ADXL345_DEVID			        0x00    // R   Device ID. - 0xE5 (229)
#define ADXL345_THRESH_TAP		    0x1D    // R/W Tap threshold.
#define ADXL345_OFSX			         0x1E    // R/W X-axis offset.
#define ADXL345_OFSY			         0x1F    // R/W Y-axis offset.
#define ADXL345_OFSZ			         0x20    // R/W Z-axis offset.
#define ADXL345_DUR			          0x21    // R/W Tap duration.
#define ADXL345_LATENT			       0x22    // R/W Tap latency.
#define ADXL345_WINDOW			       0x23    // R/W Tap window.
#define ADXL345_THRESH_ACT		    0x24    // R/W Activity threshold.
#define ADXL345_THRESH_INACT	   0x25    // R/W Inactivity threshold.
#define ADXL345_TIME_INACT		    0x26    // R/W Inactivity time.
#define ADXL345_ACT_INACT_CTL	  0x27    // R/W Axis enable control for activity and inactivity detection.
#define ADXL345_THRESH_FF		     0x28    // R/W Free-fall threshold.
#define ADXL345_TIME_FF			      0x29    // R/W Free-fall time.
#define ADXL345_TAP_AXES		      0x2A    // R/W Axis control for tap/double tap.
#define ADXL345_ACT_TAP_STATUS	 0x2B    // R   Source of tap/double tap.
#define ADXL345_BW_RATE			      0x2C    // R/W Data rate and power mode control.
#define ADXL345_POWER_CTL		     0x2D    // R/W Power saving features control.
#define ADXL345_INT_ENABLE		    0x2E    // R/W Interrupt enable control.
#define ADXL345_INT_MAP			      0x2F    // R/W Interrupt mapping control.
#define ADXL345_INT_SOURCE		    0x30    // R   Source of interrupts.
#define ADXL345_DATA_FORMAT		   0x31    // R/W Data format control.
#define ADXL345_DATAX0			       0x32    // R   X-Axis Data 0.
#define ADXL345_DATAX1			       0x33    // R   X-Axis Data 1.
#define ADXL345_DATAY0			       0x34    // R   Y-Axis Data 0.
#define ADXL345_DATAY1			       0x35    // R   Y-Axis Data 1.
#define ADXL345_DATAZ0			       0x36    // R   Z-Axis Data 0.
#define ADXL345_DATAZ1			       0x37    // R   Z-Axis Data 1.
#define ADXL345_FIFO_CTL		      0x38    // R/W FIFO control.
#define ADXL345_FIFO_STATUS		   0x39    // R   FIFO status.

//Functions prototips
void ADXL345_init(void);
void ADXL345_write(uint8_t adxl345_reg, uint8_t data);
uint8_t ADXL345_read(uint8_t adxl345_reg);
void ADXL345_read_axis_LSB(int16_t *x_asis, int16_t *y_axis, int16_t *z_axis);

#endif	/* ADXL345_H */

