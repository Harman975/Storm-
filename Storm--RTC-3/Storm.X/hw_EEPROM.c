/*
 * File:   hw_EEPROM.c
 * Author: harms
 *
 * Created on 26 February 2021, 10:50
 */


#include <xc.h>


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pic18f2520.h"
#define _XTAL_FREQ 8000000
 
unsigned char EERPOM_RD (unsigned char addr)
{
    EEADR = addr;
    EECON1bits.EEPGD = 0; 
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;        
    
    return EEDATA;
    
}

void EEPROM_WR_INIT (unsigned char addr , unsigned char data)
{
    EEADR = addr;        
    EEDATA = data; 
    EECON1bits.EEPGD = 0; 
    EECON1bits.CFGS = 0; 
    EECON1bits.WREN = 1;
    IPEN = 1; 
    INTCONbits.GIEL = 0 ;
    EECON2 = 0x55; 
    EECON1 = 0xAA;
    EECON1bits.WR = 1;
    
    
    while(!PIR2bits.EEIF);	/* Wait for write operation complete */
    PIR2bits.EEIF=0;		/* Reset EEIF for further write operation */ 
}
 

