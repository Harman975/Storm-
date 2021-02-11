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
    extern void I2C_start(void);
    extern void I2C_Restart(void);
    extern void I2C_stop();
    extern void I2C_Send_ACK(void);
    extern void I2C_Send_NACK(void);
    extern int I2C_write(unsigned char Byte);
    extern unsigned char I2C_read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HW_RTC_H */

