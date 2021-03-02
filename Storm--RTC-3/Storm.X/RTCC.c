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
#define RTC_REG 0x00 
#define CTRL_REG 0x07

void RTC_write_Init (void)
{
   I2C_Master_Start()           ;   // start I2C communication 
   I2C_Master_Write(CMD_WRITE) ;
   I2C_Master_Write(RTC_REG) ;
   I2C_Master_Write(0x80);
   I2C_Master_Stop(); 
}
//    I2C_start();
//    I2C_write(CMD_WRITE); /*control code for write mode */
//    I2C_write(SEC); /*written to seconds address */
//    I2C_write(0b00100100);  /*value of 24 seconds written to address */
//    I2C_stop();  /*i2c stop condition */
    //  i2c_start();
//i2c_write(0x00);
// I2C_Master_Start();         //Start condition
// I2C_Master_Write(CMD_WRITE);     //7 bit address + Write
//I2C_Master_Write(0x00);    //Write data
//I2C_Master_Stop();          //Stop condition




void RTC_read_init(void)
{
     I2C_Master_Start() ;
     I2C_Master_Write(CMD_WRITE) ;
     I2C_Master_Write(RTC_REG) ;
     I2C_Master_RepeatedStart();
     I2C_Master_Write(CMD_READ) ;
     I2C_Master_Read(0);
     I2C_Master_Stop(); 
      
}

unsigned char rtcc_rd(void )
{
    unsigned char rtcc_buf;
   i2c_start()             ;  // start I2C communication
   i2c_wr(CMD_WRITE) ;  // write DEVICE ADDR for RTCC WRITES
   i2c_wr(RTC_REG)        ;  // write the register ADDRESS 
   i2c_restart()           ;  // RESTART for READS 
   i2c_wr(CMD_READ)  ;  // send the DEVICE ADDRESS for RTCC READS.
   rtcc_buf  = i2c_rd()                ;  // read register (stored in 'rtcc_buf')
   i2c_nack()              ;  // NOACK from MASTER (last read byte)
   i2c_stop()              ;  // stop I2C communication
  
   return rtcc_buf    ;      // store the read byte in 'time_var'
}
// I2C_start();
// I2C_write(CMD_READ);  /*control code for read mode */
// unsigned char i2c_val = I2C_read();
// I2C_Send_NACK();       
// I2C_stop();
//}
/* Convert BCD to decimal */
/*void BCDtoDecimal (char val)
{
    char decimal;
    decimal = (val & 0x0F) + ((val & 0xF0)>>4)*10;
    return decimal ;
}
*/


void rtcc_wr ( void ) 
{
   i2c_start()             ;  // start I2C communication   
   i2c_wr(CMD_WRITE) ;  // write DEVICE ADDR for RTCC WRITE
   i2c_wr(RTC_REG)        ;  // write the register's ADDRES
   i2c_wr(0xFF)        ;  // write byte variable in the register 
   i2c_stop()              ;  // stop I2C communication
   
}
 
 
 
    
    
    
    
    
    
    

