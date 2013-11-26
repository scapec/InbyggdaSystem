/**
 * \file
 *
 * Blink 01
 * program that blinks an LED connected to pin PB26 of the Arduino DUE board
 * Ulrik Eklund, 2013-10-25
 *
 */

/**
 *
 * \par Content
 *
 * -# Minimal main function that starts with a call to PIOB_init()
 *
 * This program does not rely on the hardware API provided by Atmel, and
 * does not include any functions for drivers imported from
 * Atmel Software Framework (ASF). 
 *
 */

/* cut the declarations from here */
#include "SOS.h"
/* cut the declarations to here */



int main(void)
{
register_ctrl *const p_PIOB_SODR = (register_ctrl *) 0x400E1030U;	/* defines the address for setting the output pins of the B register */
register_ctrl *const p_PIOB_CODR = (register_ctrl *) 0x400E1034U;	/* defines the address for clearing the output pins of the B register  */

int i;				/* loop counter for the delay */	
volatile int j; 	/* Dummy volatile to prevent compiler optimising the variable away */


int delay_length = 400000;	/* variable determining the length of a delay */

PIOB_init(26);		/* initialises the digital B I/O-port */

for (;;)	/* repeat blink in infinity */
{				
	j=0;	/* makes sure j doesn't overflow */
	
	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	

	}
}
	}/* end of main() */




/* cut the function definitions from here */
/* cut the function definitions to here */