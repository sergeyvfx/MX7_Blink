/* 
 * File:   newmain.c
 * Author: Cristian Fatu
 * Corrected an old version of Michele Yu
 *
 * Created on March 25, 2015, 10:27 AM
 */
/************************************************************************/
/*  File Description:							*/
/*		This project cycles through LD1 to LD4                  */
/*									*/
/************************************************************************/

#include <plib.h>
/* ------------------------------------------------------------ */
/*				Configuration Bits				                */
/* ------------------------------------------------------------ */

// SYSCLK = 80 MHz (8 MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)

#pragma config FNOSC	 = PRIPLL
#pragma config FPLLMUL 	 = MUL_20
#pragma config FPLLIDIV  = DIV_10

// configure the microcontroller for use with the on-board (MX7) licensed debugger circuit
#pragma config ICESEL = ICS_PGx1

/* ------------------------------------------------------------ */
/*				Forward Declarations							*/
/* ------------------------------------------------------------ */

void DeviceInit();
void DelayInit();
void DelayMs(int cms);


/* ------------------------------------------------------------ */
/*				Definitions										*/
/* ------------------------------------------------------------ */

#define	cntMsDelay	10000			//timer 1 delay for 1ms

/* ------------------------------------------------------------ */
/*				Main											*/
/* ------------------------------------------------------------ */

int main()
{
    //Set LD1 through LD4 as digital output
	DeviceInit();
	//initialize timer for delay
	DelayInit();

	/* Perform the main application loop.
	*/
	while (1)
	{
		//drive LD1 high
		PORTWrite (IOPORT_G, BIT_12);
		DelayMs(1);
		//drive LD2 high
		PORTWrite (IOPORT_G, BIT_13);
		DelayMs(1);
		//drive LD3 high
		PORTWrite (IOPORT_G, BIT_14);
		DelayMs(1);
		//drive LD4 high
		PORTWrite (IOPORT_G, BIT_15);
		DelayMs(1);
	}
}

/* ------------------------------------------------------------ */
/*  DeviceInit()
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Set LD1 through LD4 as digital output
/* ------------------------------------------------------------ */

void DeviceInit()
{
	//On MX4ck LED1 is on RG12
	//		   LED2 is on RG13
	//		   LED3 is on RG14
	//		   LED4 is on RG15
	//Set ports for onboard LEDs to outputs
	PORTSetPinsDigitalOut (IOPORT_G, BIT_12|BIT_13| BIT_14|BIT_15);

}

/* ------------------------------------------------------------ */
/***	DelayInit
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialized the hardware for use by delay functions. This
**		initializes Timer 1 to count at 10Mhz.
/* ------------------------------------------------------------ */

void DelayInit()
{
	unsigned int tcfg;

	/* Configure Timer 1. This sets it up to count a 10Mhz with a period of 0xFFFF
	*/
	tcfg = T1_ON|T1_IDLE_CON|T1_SOURCE_INT|T1_PS_1_8|T1_GATE_OFF|T1_SYNC_EXT_OFF;
	OpenTimer1(tcfg, 0xFFFF);

}

/* ------------------------------------------------------------ */
/***	DelayMs
**
**	Parameters:
**		cms			- number of milliseconds to delay
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Delay the requested number of milliseconds. Uses Timer1.
/* ------------------------------------------------------------ */

void DelayMs(int cms)
{
	int		ims;

	for (ims=0; ims<cms; ims++)
        {
		WriteTimer1(0);
		while (ReadTimer1() < cntMsDelay);
	}
}