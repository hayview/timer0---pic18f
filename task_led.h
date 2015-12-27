#ifndef TASK_LED_H
#define	TASK_LED_H

#include <p18cxxx.h>

#define mInitLED1()		   {TRISBbits.TRISB6=0;}
#define mInitLED2()		   {TRISBbits.TRISB7=0;}
#define mInitLEDAll()	   {mInitLED1(); mInitLED2();}
#define mLED_1              LATBbits.LATB6
#define mLED_2              LATBbits.LATB7

void taskLED1(void);
void taskLED2(void);

#endif	/* TASK_DISPLAY_H */
