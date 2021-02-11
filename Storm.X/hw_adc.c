
#include <stdio.h>
#include <stdbool.h>

#include "pic18f2520.h"

#include "hw_uart.h"
#define _XTAL_FREQ 8000000

float voltage ;
float  value;
float ADC;
int i;


unsigned int Read_ADC (unsigned char channel)
{
    unsigned int result;
    if (channel == 0)
    {
         ADCON0bits.CHS = 0000;
         
         
    }          
    else 
    {
       ADCON0bits.CHS = 0001;
      
    }
       
        //ADCON0bits.CHS = channel; /*optimised*/     
        result = 0; 
       ADCON0bits.GO = 1;
       while (ADCON0bits.DONE == 1);// wait till GODONE bit is zero
       result = (ADRESH << 8) | (ADRESL); //combines two bytes into a long int

        
    return result;
}

void ADC_intialize(void)
/************************
 * Desc: Init the ADC
 * Inputs: None
 * Return: None
 */
{
   TRISA1 = 1 ; 
  
   
    // The ADCON1 register, shown in Register 19-2, configures the functions of the port pins. 
    ADCON1bits.PCFG = 0b1101; // VSS,VDD ref. AN0 and AN1 analog only
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0 ;     
       // The ADCON2 register, shown in Register 19-3, configures the A/D clock source, programmed acquisition time and justification.
   //ADCON2 = 0b00111110;
     ADCON2bits.ADCS = 0b110;
     ADCON2bits.ACQT = 0b111;
     ADCON2bits.ADFM = 1;
   
    ADCON0bits.ADON = 1 ; /* A/D module is enabled */
}
/**************ADC SAMPLE SECOND CHANNEL*************/


