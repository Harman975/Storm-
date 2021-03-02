/*
 * File:   hw_RTC.c
 * Author: Harman.Singh
 *
 * Created on 10 February 2021, 11:36
 */


#include <xc.h>


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pic18f2520.h"
#define _XTAL_FREQ 8000000
 

void InitI2C()
{
	TRISC3 = 1;		// Make SDA and
	TRISC4 = 1;		// SCL pins input
 
	SSPADD  = 0x13;
	SSPCON1bits.SSPEN  = 1;     // Master Synchronous Serial Port Enable bit
    SSPCON1bits.SSPM = 0b1000;  // Select and enable I2C in master mode
    SSPIF = 0;
}   

void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}
void I2C_Master_Start()
{
  I2C_Master_Wait();    
  SEN = 1;             //Initiate start condition
}

void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;           //Initiate repeated start condition
}

void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;           //Initiate stop condition
}

void I2C_Master_Write(unsigned d)
{
  I2C_Master_Wait();
  SSPBUF = d;         //Write data to SSPBUF
  I2C_Master_Wait();
}

unsigned short I2C_Master_Read(unsigned short a)
{
  unsigned short data;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  data = SSPBUF;      //Read data from SSPBUF
  I2C_Master_Wait();
  ACKDT = (a)?0:1;    //Acknowledge bit
  ACKEN = 1;          //Acknowledge sequence
  return data;
}

//void I2C_READ_NEW ()
//{
//    unsigned int data ; 
//     I2C_Master_Wait();
//     RCEN = 1 ;
//     I2C_Master_Wait();
//     data = SSPBUF;
//}
//    
//void I2C_ACK (void)
//{
//    
//}

  void poll_if_tim1(void) {            // poll 2 flags: MSSP1IF & T1
  unsigned char err_flg = 0x00 ; 
  TMR1H = ~(10000/256)&0xff ; 
  TMR1L = ~(10000%256)&0xff ;          //  1msec delay m
  T1CONbits.TMR1ON  = 1 ;                          //  start timer1
  while(!(PIR1bits.SSPIF| PIR1bits.TMR1IF)) ;  // wait at least on flag to rise
  if (PIR1bits.TMR1IF) { err_flg = 0x01 ; }    // if timeout, set error flag 
  PIR1bits.SSPIF = 0  ;               // in any case, clear all   
  PIR1bits.TMR1IF =0 ;  // overflow of TMR1  
  T1CONbits.TMR1ON ;    // start/stop T1 bit
  
  }  


  
    void i2c_start(void)             // START I2C communication 
    {
    SEN = 1    ;      // START bit (cleared by hw in the end) 
    poll_if_tim1()    ;           // poll MSSP1IF with 1msec timeout
    }

     void i2c_restart(void)           // RESTART I2C communication (change to 'reads') 
  { RSEN = 1   ;      // REPEATED START bit (cleared by hw in the end) 
    poll_if_tim1()    ;          // poll MSSP1IF with 1msec timeout 
     }
     
      void i2c_stop(void)              // STOP I2C communication 
  { PEN = 1    ;      // STOP bit (cleared by hw in the end) 
    poll_if_tim1()    ;     }      // poll MSSP1IF with 1msec timeout 
     
void i2c_wr(unsigned char i2c_data) // writes a byte in the I2C SLAVE 
  { SSPBUF = i2c_data      ;      // load char in data buffer ; start streaming
    
    poll_if_tim1()    ;            // poll MSSP1IF with 1msec timeout  
}  
unsigned char i2c_rd(void)
 { 
    unsigned char rtcc_buf ;
    RCEN = 1   ;      // enable I2C receive mode(RCEN=0 after 8cks by hw)
    poll_if_tim1()    ;            // poll MSSP1IF with 1msec timeout 
    rtcc_buf = SSPBUF      ;     // store read result in the related buffer
    return rtcc_buf;
}

 void i2c_ack(void)               // ACK=0 from MASTER 
  { SSPCON2bits.ACKDT = 0  ;      // set the MASTER ACK bit 
    SSPCON2bits.ACKEN = 1  ;      // enable MASTER ACK sequence  
    poll_if_tim1()    ;           // poll MSSP1IF with 1msec timeout
 }
   void i2c_nack(void)              // NACK=1 from MASTER 
  { SSPCON2bits.ACKDT = 1  ;      // set the MASTER NOACK bit  
    SSPCON2bits.ACKEN = 1  ;      // enable MASTER ACK sequence 
    poll_if_tim1()     ;    }      // poll MSSP1IF with 1msec timeout
 
  