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
	TRISC4 = 1;		// Make SDA and
	TRISC5 = 1;		// SCK pins input

	SSPADD  = 0x09;
	SSPSTAT = 0x80;		// Slew Rate control is disabled
	SSPCON1  = 0x28;		// Select and enable I2C in master mode
}


// Function Purpose: I2C_Start sends start bit sequence
void I2C_start(void)
{
	SSPCON2bits.SEN = 1;			// Send start bit
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


//// Function Purpose: I2C_ReStart sends start bit sequence
void I2C_Restart(void)
{
	SSPCON2bits.RSEN = 1;			// Send Restart bit
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Stop sends stop bit sequence
void I2C_stop()
{
	SSPCON2bits.PEN = 1;			// Send stop bit
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit
}



//Function : I2C_Send_ACK sends ACK bit sequence
void I2C_Send_ACK(void)
{
	SSPCON2bits.ACKDT = 0;			// 0 means ACK
	SSPCON2bits.ACKEN = 1;			// Send ACKDT value
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Send_NACK sends NACK bit sequence
void I2C_Send_NACK(void)
{
	SSPCON2bits.ACKDT = 1;			// 1 means NACK
	SSPCON2bits.ACKEN = 1;			// Send ACKDT value
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


// Function Purpose: I2C_Write_Byte transfers one byte
 int I2C_write(unsigned char Byte)
{
	SSPBUF = Byte;		// Send Byte value
	while(!PIR1bits.SSPIF);		// Wait for it to complete
        PIR1bits.SSPIF = 0;			// Clear the flag bit

	return SSPCON2bits.ACKSTAT;		// Return ACK/NACK from slave
}


// Function Purpose: I2C_Read_Byte reads one byte
unsigned char I2C_read()
{
	SSPCON2bits.RCEN = 1;			// Enable reception of 8 bits
	while(!PIR1bits.SSPIF);		// Wait for it to complete
	PIR1bits.SSPIF = 0;			// Clear the flag bit

    return SSPBUF;		// Return received byte
}