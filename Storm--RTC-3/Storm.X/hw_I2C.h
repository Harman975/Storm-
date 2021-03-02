/* 
 * File:   hw_RTC.h
 * Author: Harman.Singh
 *
 * Created on 10 February 2021, 11:37
 */

#ifndef HW_I2C_H
#define	HW_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    extern void InitI2C();
//     extern void I2C_start(void);
//     extern void I2C_Restart(void);
//    extern void I2C_stop();
//    extern void I2C_Send_ACK(void);
//    extern void I2C_Send_NACK(void);
//    extern int I2C_write(unsigned char Byte);
//    extern unsigned char I2C_read(void);
    extern void I2C_Master_Start();
    extern void I2C_Master_Write(unsigned d);
    extern void I2C_Master_Stop();
    extern unsigned short I2C_Master_Read(unsigned short a);
    extern void I2C_Master_RepeatedStart();
    extern void i2c_start(void);
    
    
   /////////
    
   extern  void i2c_start(void);
    extern void i2c_restart(void) ;
   extern void i2c_stop(void) ;
   extern void i2c_wr(unsigned char i2c_data) ;
   extern unsigned char i2c_rd(void) ; 
   extern void i2c_ack(void)  ;   
   extern void i2c_nack(void); 
#ifdef	__cplusplus
}
#endif

#endif	/* HW_RTC_H */



