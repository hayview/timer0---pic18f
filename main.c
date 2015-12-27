#include <p18f4553.h>
#include "task_led.h"
#include "timer0.h"

//******************************************************************************
//  CONFIG
//******************************************************************************
        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2  
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF

#define GIEL()		INTCONbits.GIEL=1;

unsigned int counter=0;
unsigned char flag_1sec=0;
unsigned char flag_2sec=0;
unsigned char flag_3sec=0;
unsigned char flag_led1=0;
unsigned char flag_led2=0;

void main()
{
    //------------------------------------------------------------------------------
    //  Init PIC periphery
    //------------------------------------------------------------------------------
	RCONbits.IPEN=1;
	mInitLEDAll();
	Timer0_Init();
	Timer0_Write(63661);
	Timer0_Start();
	INTCONbits.GIEH=1;

	while(1)
	{
		if(flag_led1==1)
		{
			flag_led1=0;
			taskLED1();
			
		}

		if(flag_led2==1)
		{
			flag_led2=0;
			taskLED2();
		}
	}

}

//----------------------------------------------------------------------------
// High priority interrupt vector
void InterruptHandlerHigh() ;
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void) {
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}

//----------------------------------------------------------------------------
// Low priority interrupt routine
#pragma code
#pragma interrupt InterruptHandlerHigh
//
// Timer0 overflow
void InterruptHandlerHigh() 
{
    if (INTCONbits.TMR0IF) {
		INTCONbits.TMR0IF = 0;

		//set timer int on overflow
   		Timer0_Write(63661);

		counter++;
		if(counter>=100) 
		{
			counter=0;
			flag_1sec=1;
		
		}
		
		if(flag_1sec==1)
		{
			flag_1sec=0;
			flag_2sec++;
			flag_led1=1;
		}

		if(flag_2sec==2)
		{
			flag_2sec=0;
			flag_led2=1;
		}
	}
}
