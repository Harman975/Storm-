/* 
 * File:   hw_uart.h
 * Author: Harman.Singh
 *
 * Created on 04 February 2021, 17:22
 */

#ifndef HW_UART_H
#define	HW_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

    
extern void UART_Init(uint24_t baud_rate);
extern void UART_send_string(char* st_pt);



#ifdef	__cplusplus
}
#endif

#endif	/* HW_UART_H */

