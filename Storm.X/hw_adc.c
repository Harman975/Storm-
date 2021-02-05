
#include <stdio.h>
#include <stdbool.h>

#include "pic18f2520.h"

#include "hw_uart.h"
#define _XTAL_FREQ 8000000

float voltage ;
float  value;
float ADC;
float buffer [9];
int i;

void ADC_INT  (void )
{
    //while(!TXIF);  // hold the program till TX buffer is free
   // TXREG = buffer ; // Load the transmitter buffer with the ADC value
}

unsigned int Read_ADC ()
{
    unsigned int _voltage = 0;
   
   // while(PIR1bits.ADIF == 0)
   // {
       
       ADCON0bits.CHS = 0001;
       ADCON0bits.GO = 1;
       while (ADCON0bits.DONE == 1);// wait till GODONE bit is zero
        
        _voltage = (ADRESH << 8) | (ADRESL); //combines two bytes into a long int
        PIR1bits.ADIF = 0;    /*A/D converter interrupt flag bit*/
         //ADCON0bits.DONE = 1;
        
         
           
         //return (Read_ADC);
       //value = (voltage * 5) /  1023;
       //ADC = value;
         
    
   // }
    
    return _voltage;
}

void ADC_intialize(void)
/************************
 * Desc: Init the ADC
 * Inputs: None
 * Return: None
 */
{
   TRISA =  0xff;
   //TRISA1 =  0xff;
   
    // The ADCON1 register, shown in Register 19-2, configures the functions of the port pins. 
    ADCON1bits.PCFG = 0b1101; // VSS,VDD ref. AN0 analog only
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0 ;     
       // The ADCON2 register, shown in Register 19-3, configures the A/D clock source, programmed acquisition time and justification.
   //ADCON2 = 0b00111110;
     ADCON2bits.ADCS = 0b110;
     ADCON2bits.ACQT = 0b111;
     ADCON2bits.ADFM = 0;
     
   
    ADCON0bits.ADON = 1 ; /* A/D module is enabled */
     
#if 0   
    // The ADCON0 register, shown in Register 19-1,controls the operation of the A/D module. 
   ADCON0bits.CHS = 0x00; /* A/D channel AN3 select bits  */
   ADCON0bits.CHS = 0b0100; /* A/D channel AN4 select bits */
   ADCON0bits.ADON = 0 ; /* A/D module is enabled */
   
   
   // Configure A/D interrupt. 
    PIR1bits.ADIF = 0;    /*A/D converter interrupt flag bit*/
    PIE1bits.ADIE = 1 ;
    INTCONbits.GIE = 1;  /*Global Interrupt Enable bit*/
    RCONbits.IPEN = 0;    /*Enables all unmasked interrupts */
#endif    
}

