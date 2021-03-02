
#include <stdio.h>
#include <stdbool.h>

#include "pic18f2520.h"

#include "hw_uart.h"


void UART_Init(unsigned int baud_rate)
{
    /* Transmit Enable */
   TXSTAbits.TXEN = 1;
   /* EUSART mode select */
   TXSTAbits.SYNC = 0;
   /* High Baud Rate Select */
   TXSTAbits.BRGH = 0;
   /* 16-bit Baud Rate Generator is used */
   BAUDCONbits.BRG16 = 0;
   /* Serial Port Enable */
   RCSTAbits.SPEN = 1;
    /* Baud rate configuration at 9600*/
   SPBRGH = 0x00;
   SPBRG = 0x0C;
}

void UART_send_char(char bt) // sends one byte to UART  
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = bt; //Load the transmitter buffer with the received value
}

//**Function to get one byte of date from UART**//
char UART_get_char()  
{
   
    if (RCSTAbits.OERR == 1) // check for Error
    {
        LATA4 = 0;
        LATA5 = 0;
        LATA6 = 0;

      RCSTAbits.SPEN = 1; //If error -> Reset
      RCSTAbits.SPEN = 1; //If error -> Reset
         
    }
   
   
    while(!RCIF);  // hold the program till RX buffer is free
   
    return RCREG; //receive the value and send it to main function
}

void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
