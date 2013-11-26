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
#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */

typedef uint32_t register_ctrl;	/* ARM Cortex-M3 is a 32 bit processor, typedef based on C99 standard */
typedef uint32_t register_data;

/*
* The following #defines allows for nicer programming of the PIOB I/O-port
* not requiring explicit pointers in main() or any other functions
*
* Note that most of these I/O controls will not be needed in Laboration 1a!
*/

#define PIOB_PER (*p_PIOB_PER)
#define PIOB_PSR (*p_PIOB_PSR)
#define PIOB_OER (*p_PIOB_OER)
#define PIOB_ODR (*p_PIOB_ODR)
#define PIOB_SODR (*p_PIOB_SODR)
#define PIOB_CODR (*p_PIOB_CODR)
#define PIOB_MDER (*p_PIOB_MDER)
#define PIOB_MDDR (*p_PIOB_MDDR)
#define PIOB_OWER (*p_PIOB_OWER)
#define PIOB_OWDR (*p_PIOB_OWDR)
#define PIOB_ODSR (*p_PIOB_ODSR)
#define PIOB_ABSR (*p_PIOB_ABSR)

void PIOB_init(int);	/* declaration of function that initiates the B I/O-port */

register_data pin(int); /* declaration of a support function that sets a specific bit, e.g. pin, to 1 */
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
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */ 
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;
	}
}

}	/* end of main() */




/* cut the function definitions from here */

void PIOB_init(int PinNumber) /**< Configures the PB port on the Due board */
{
/*
 * Nothing in this function needs to be changed in lab 1a 
 *
 * Note that all these register controls will not be needed in Laboration 1a
 * but are included for future use
 */

/* 
 * setting up the memory addresses of the digital I/O B-port 
 * which does not depend if the B-port is used as an input or output
 * Most of these variables will not be used
 */
register_ctrl *const p_PIOB_BASE = (register_ctrl *) 0x400E1000U;	/*base address for PIO registers */
register_ctrl *const p_PIOB_ABSR = (register_ctrl *) (0x400E1070U);
register_ctrl *const p_PIOB_PER = (register_ctrl *) (0x400E1000U);	/* defines the address for enabling the parallel Input/output B register */
register_ctrl *const p_PIOB_PSR = (register_ctrl *) (0x400E1008U);	/* defines the address for status of the parallel Input/output B register */
register_ctrl *const p_PIOB_OER = (register_ctrl *) 0x400E1010U;	/* defines the address for enabling the parallel output B register */
register_ctrl *const p_PIOB_OSR = (register_ctrl *) 0x400E1018U;	/* defines the address for status of the parallel output B register */
register_ctrl *const p_PIOB_ODR = (register_ctrl *) 0x400E1014U;	/* defines the address for output disable of the parallel output B register */
register_ctrl *const p_PIOB_MDER = (register_ctrl *) 0x400E1050U;	/*   */
register_ctrl *const p_PIOB_MDDR = (register_ctrl *) 0x400E1054U;	/*   */
register_ctrl *const p_PIOB_OWER = (register_ctrl *) 0x400E10A0U;	/*   */
register_ctrl *const p_PIOB_OWDR = (register_ctrl *) 0x400E10A4U;	/*   */

/* 
 * configuring the relevant pin on the B-port as outputs, 
 * e.g. pin 27 which is the built-in LED on an Arduino Due board
 * for other pins see http://arduino.cc/en/Hacking/PinMappingSAM3X 
 */
 
PIOB_PER = pin(PinNumber);		/* Enables pin on PIOB */
PIOB_OER = pin(PinNumber);		/* Enables pins for output */
PIOB_OWER = pin(PinNumber);	/* Enables pins for output */

/*	
PIOB_ABSR =	0xFFFFFFFFU;
PIOB_ODR = 0xF0FFFFFFU;
PIOB_SODR = 0x00000000U;
PIOB_CODR = 0xFFFFFFFFU;
PIOB_MDER = 0x0F000000U;
PIOB_MDDR = 0xF0FFFFFFU;
PIOB_OWDR = 0x00FFFFFFU;
*/

}	/* end of PIO_init() */


//#include "PortB.h"

register_data pin(int n) /**< Sets bit n to 1 */
/*
 * A simple, but maybe not so efficient, way to create a single 1 at a
 * particular place in a long word
 *
 * Note that the first bit in an I/O port is bit 0, not bit 1
 */
{
return (1 << (n));	
}	/* end of pin() */

/* cut the function definitions to here */