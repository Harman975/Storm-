/* 
 * File:   RTCC.h
 * Author: Harman.Singh
 *
 * Created on 11 February 2021, 14:20
 */

#ifndef RTCC_H
#define	RTCC_H

#ifdef	__cplusplus
extern "C" {
#endif
//    extern void RTC_test_write (void);
//    void RTC_test_read (void);
//    void BCDtoDecimal (char val);
//    
    
extern void RTC_write_Init (void) ;
extern void RTC_read_init(void) ;
extern void rtcc_wr ( void ) ;
extern unsigned char rtcc_rd(void ) ;
#ifdef	__cplusplus
}
#endif

#endif	/* RTCC_H */

