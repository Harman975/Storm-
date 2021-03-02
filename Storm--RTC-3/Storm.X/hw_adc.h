/* 
 * File:   hw_adc.h
 * Author: Harman.Singh
 *
 * Created on 04 February 2021, 17:40
 */

#ifndef HW_ADC_H
#define	HW_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void ADC_intialize(void);
extern unsigned int Read_ADC (unsigned char channel);
extern void ADC_INT  (void );



#ifdef	__cplusplus
}
#endif

#endif	/* HW_ADC_H */

