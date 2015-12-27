#include "timer0.h"

void Timer0_Init(void)
{
	TMR0H = 0;                // Reset Timer0 to 0x0000
	TMR0L = 0;
	INTCONbits.TMR0IF = 0;    // Clear Timer0 overflow flag
	INTCONbits.TMR0IE = 0;
	
/* T0CON values
			bit 7 TMR0ON: Timer0 On/Off Control bit 
			1 = Enables Timer0 
			0 = Stops Timer0
			bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit 
			1 = Timer0 is configured as an 8-bit timer/counter 
			0 = Timer0 is configured as a 16-bit timer/counter 
			bit 5 T0CS: Timer0 Clock Source Select bit 
			1 = Transition on T0CKI pin 
			0 = Internal instruction cycle clock (CLKO) 
			bit 4 T0SE: Timer0 Source Edge Select bit
			1 = Increment on high-to-low transition on T0CKI pin 
			0 = Increment on low-to-high transition on T0CKI pin 
			bit 3 PSA: Timer0 Prescaler Assignment bit 
			1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler. 
			0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
			bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits    
			111 = 1:256 Prescale value
			110 = 1:128 Prescale value
			101 = 1:64   Prescale value
			100 = 1:32   Prescale value
			011 = 1:16   Prescale value
			010 = 1:8     Prescale value
			001 = 1:4     Prescale value
			000 = 1:2     Prescale value
*/

//set up timer0 see abive
	T0CONbits.TMR0ON=0;
	T0CONbits.T08BIT=0;
	T0CONbits.T0CS=0;
	T0CONbits.PSA=0;
	T0CONbits.T0PS=5;
	
	INTCON2bits.TMR0IP=1;
}

void Timer0_Start(void)
{
	T0CONbits.TMR0ON = 1;	// Enable Timer0
	INTCONbits.TMR0IE = 1;  // Enable Timer0 overflow interrupt
}

void Timer0_Stop(void)
{
	T0CONbits.TMR0ON = 0;	// Disable Timer0
	INTCONbits.TMR0IE = 0;  // Disable Timer0 overflow interrupts
}

void Timer0_Write(unsigned int timer0)
{
	union Timers timer;

	timer.lt = timer0;    // Copy timer value into union

	TMR0H = timer.bt[1];  // Write high byte to Timer0
	TMR0L = timer.bt[0];  // Write low byte to Timer0
}
