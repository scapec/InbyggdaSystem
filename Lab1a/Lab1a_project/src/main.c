/**
 * \file
 *
 * Blink 01
 * program that blinks an LED connected to pin PB26 of the Arduino DUE board
 * Ulrik Eklund, 2013-10-25
 *
 * Modified Matko Scapec & Osama Fayad
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


int delay_length = 100000;	/* variable determining the length of a delay */
int delay_length2 = 300000;
int delay_length3 = 500000;



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
	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */
	for (i=0; i<delay_length2; i++)	/* The delay counter */
	{
		j++;
	}

	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length2; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;
	}
	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length2; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;
	}
	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length2; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */
	for (i=0; i<delay_length2; i++)	/* The delay counter */
	{
		j++;
	}

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
	PIOB_SODR = pin(26);	/* sets a bit of I/O port B to a one */
	for (i=0; i<delay_length; i++)	/* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	PIOB_CODR = pin(26);	/* clears a bit of I/O port B */
	for (i=0; i<delay_length3; i++)	/* The delay counter */
	{
		j++;
	}
}

}	/* end of main() */


