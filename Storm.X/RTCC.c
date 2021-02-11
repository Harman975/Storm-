/*
 * File:   RTCC.c
 * Author: Harman.Singh
 *
 * Created on 11 February 2021, 10:32
 */


#include <xc.h>
#include "hw_I2C.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pic18f2520.h"
#define _XTAL_FREQ 8000000
#define CMD_READ 0xDF
#define CMD_WRITE 0xDE
#define SEC 0x00 
void BCDtoDecimal (char val);

void RTC_test_write (void)
{
    I2C_start();
    I2C_write(CMD_WRITE); /*control code for write mode */
    I2C_write(SEC); /*written to seconds address */
    I2C_write(0b00100100);  /*value of 24 seconds written to address */
    I2C_stop();  /*i2c stop condition */
}
void RTC_test_read (void)
{
 I2C_start();
 I2C_write(CMD_READ); ; /*control code for read mode */
 unsigned char i2c_val = I2C_read();
 I2C_Send_NACK();       
 I2C_stop();
}
/* Convert BCD to decimal */
/*void BCDtoDecimal (char val)
{
    char decimal;
    decimal = (val & 0x0F) + ((val & 0xF0)>>4)*10;
    return decimal ;
}
*/



 
 
 
    
    
    
    
    
    
    

