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
	SSPSTAT = 0;		
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










