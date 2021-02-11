
// PIC18F2520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO7     // Oscillator Selection bits (Internal oscillator block, CLKO function on RA6, port function on RA7)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pic18f2520.h"
#define _XTAL_FREQ 8000000

#include "hw_uart.h"
#include "hw_adc.h"
//#define vref 4.5

#define TEMPERATURE 0
#define HUMIDITY 1


static void CLK_intialize (void)
{
//    
//    OSCTUNEbits.PLLEN = 1 ; /*Bit 6 - Frequency Multiplier PLL for INTOSC Enable bit */
//    OSCTUNEbits.INTSRC = 0; /*Bit 7 - internal oscillator low frequency select bit */
//    OSCTUNEbits.TUN = 0b00000; /* bit 4-0 - Frequency tuning bit = 4 MHz */
    OSCCONbits.IRCF = 0b111;  /*bit 6-4 - internal frequency bit */
    //OSCCONbits.IOFS = 0b1; /*bit 2 -  INTOSC frequency stable bit */          
    OSCCONbits.IDLEN = 0b0;  /*bit 6-4 - internal frequency bit */
    OSCCONbits.SCS = 0b11 ;/* bit 1 -  system clock select bit - Internal oscillator block*/
}

static void PORT_Initialize(void)
{
   TRISC6 = 1; /* Configure RC6 as TX. */
   TRISC7 = 1; /* configure RC7 as RX */ 
}


static void INTERRUPT_Initialize(void)
{
    INTCONbits.GIE = 1; /* Enable the Global Interrupts */
    INTCONbits.PEIE = 1; /* Enable the Peripheral Interrupts */
}

        /*//////////ADC SET UP *///////////////


void main()
{
    unsigned int temp_adc = 0;
    unsigned int humid_adc = 0;
    
    char _adc_str[20];
    char _adc_buf[20];
    
   CLK_intialize();
   PORT_Initialize();
   UART_Init(9600);
   ADC_intialize();
   
   
    while (1)
    {
           
            UART_send_string("Dave is a legend!\n");
            
            __delay_ms(500); 
            TRISB1 = 0;
           __delay_ms(500);
            TRISB1 = 1;

            
            temp_adc = Read_ADC (TEMPERATURE);
       
            snprintf(_adc_str, 20, "TEMP: %u\n", temp_adc);
            
            
            __delay_ms(500);
           
            
            humid_adc = Read_ADC (HUMIDITY);
            snprintf(_adc_str, 20, "HUMID: %u\n", humid_adc);
             
      
    }
     
}







