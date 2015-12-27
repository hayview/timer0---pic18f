#ifndef __TIMER_0_H
#define __TIMER_0_H

#include <p18cxxx.h>

/* used to hold 16-bit timer value */
union Timers
{
  unsigned int lt;
  char bt[2];
};

void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_Write(unsigned int timer0);

#endif
