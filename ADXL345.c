// ADXL345 read-write with I2C interface
//--------------------------------------------------------
#include "ADXL345.h"

void ADXL345_init(void)
{
	I2C_init();
}

void ADXL345_write(uint8_t adxl345_reg, uint8_t data)
{
	I2C_start();
    I2C_write(ADXL345_I2C_ADR_WR);
    I2C_write(adxl345_reg);
    I2C_write(data);
    I2C_stop();
}

uint8_t ADXL345_read(uint8_t adxl345_reg)
{
    uint8_t tmp=0;
    
    I2C_start();
    I2C_write(ADXL345_I2C_ADR_WR);
    I2C_write(adxl345_reg);
    I2C_restart();
    I2C_write(ADXL345_I2C_ADR_RD);
    tmp=I2C_read();
    I2C_stop();
    
	return tmp;
}
///*****************************************************************************

void ADXL345_read_axis_LSB(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
    uint8_t val[6]={0};
    
    //ADXL345_read_multi(ADXL345_DATAX0,val,6);
    val[0]=ADXL345_read(ADXL345_DATAX0);
    val[1]=ADXL345_read(ADXL345_DATAX1);
    val[2]=ADXL345_read(ADXL345_DATAY0);
    val[3]=ADXL345_read(ADXL345_DATAY1);
    val[4]=ADXL345_read(ADXL345_DATAZ0);
    val[5]=ADXL345_read(ADXL345_DATAZ1);
    
    *x_axis=(val[1] << 8) | val[0];
    *y_axis=(val[3] << 8) | val[2];
    *z_axis=(val[5] << 8) | val[4];
}
