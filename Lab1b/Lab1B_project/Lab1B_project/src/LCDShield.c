/*
 * LCDShield.c
 * Code to be used in Lab 1b
 *
 * Created by Ulrik on 2013-11-06.
 * Based on code from Tommy Andersson.
 *
 * Modified LCDWrite() to make use of some new macros.
 * See 'LCDShield.h' for more description of added features.
 */

#include <stdio.h>
#include "asf.h"
#include "LCDShield.h"

void delay_init(void)		/* Initializes the timer used for delays */
{
	pmc_enable_periph_clk(ID_TC0);
	tc_init(TC0,0,0);		 /* TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC0,0);
	tc_stop(TC0,0);			/* making sure the timer does not run  */
}


void delay(uint32_t us)		/* A simple implementation for a delay in us (not calibrated) */
{
	tc_start(TC0,0);
	while (tc_read_cv(TC0,0) < us*42);
	tc_stop(TC0,0);
}

/*
 * Initializes the display on the LCD shield, returns 1 if everything is OK.
 */
int LCDInit(void)
{
	int all_ok=0;		/* at the beginning assume nothing works */
	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(4100);	/* wait for more than 4,1 ms */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);

	delay(100);	/* wait 100 us */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);		
	
	delay(100);	/* wait 100 us */
		
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);

	LCDwrite(0b00101000, LOW);		/* Two rows, small font */
	LCDwrite(0b00001000, LOW);		/* Display off */
	LCDwrite(0b00000001, LOW);		/* Display clear */
	
	delay(3000);
	
	LCDwrite(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	LCDwrite(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */

	all_ok = 1;					/* simple return statement showing that the initialization of the LCD has completed */
	return all_ok;
}

/*
 * Clearing the display.
 * Returning 1 if no errors occurred, otherwise 0.
 */
int LCDclear(void)
{
	return (LCDwrite(0x01, LOW) == FLIP_NIBBLES(0x01));
}

/*
 * Writes a byte to the LCD display
 * writes the byte (8 bits) to the LCD display as two consecutive 4 bits 
 * type = 0 controls the display
 * type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
 *
 * LCDwrite returns the actual pinout value on PIOC 26-23, which is the reverse order compared to the Due pin order of D4-D7
 */
uint8_t LCDwrite(uint8_t byte, bool type)
{
	uint32_t byte32;
	uint8_t byte_orig;
	uint8_t mirrored_output = 0;

	byte_orig = byte;

	/* write the first 4 bits to the shield. */
	byte = byte>>4;
	byte = FLIP_NIBBLE(byte);
	byte32 = (uint32_t)byte<<23;
	mirrored_output = byte<<4;
	
	ioport_set_pin_level(LCD_RS, type); 
	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);
	
	/* write the second 4 bits to the shield. */
	byte = byte_orig;
	byte = byte & 0x0f;
	byte = FLIP_NIBBLE(byte);
	byte32 = (uint32_t)byte<<23;
	mirrored_output = mirrored_output + byte;

	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delay(100);
	
	return mirrored_output;
}

/*
 * Writes an integer number (positive/negative) to the LCD.
 * Returning 1 if no errors occurred when sending characters to LCD,
 * otherwise 0.
 *
 * ARGUMENTS:
 * 'number'	- number to write to LCD
 * 'ret_chrs' - will contain corresponding character that were sent to LCD.
 */
int LCD_write_integer(int32_t number, char *ret_chrs)
{
	/* calculate absolute value of 'number' */
	int32_t abs_nr = (number < 0 ? -number : number);
	/* size of number (power of tens), min 1 */
	int32_t nr_size = 1;
	/* character index for 'ret_chrs' */
	uint8_t chr_i = 0;
	/* the rest of 'abs_nr' after division - for printing digits */
	int32_t rest_of_nr;
	/* LCDWrite return value */
	int lcdStatus;
	/* return status value - assume everything's OK! */
	int retStatus = 1;
	
	/* negative number? */
	if (number < 0) {
		/* write to LCD and store return value */
		lcdStatus = LCDwrite('-', HIGH);
		/* check return value - possible error? */
		if (lcdStatus != FLIP_NIBBLES(ASCII('-'))) {
			retStatus = 0;
		}
		/* append character */
		ret_chrs[chr_i++] = '-';
	}
	/* determine size of number */
	while ((nr_size * 10) < abs_nr) {
		nr_size = nr_size * 10;
	}
	/* print digits */
	rest_of_nr = abs_nr;
	while (nr_size >= 1) {
		/* write to LCD and store return value */
		lcdStatus = LCDwrite((0x30 + (rest_of_nr / nr_size)), HIGH);
		/* check return value - possible error? */
		if (lcdStatus != FLIP_NIBBLES((0x30 + (rest_of_nr / nr_size)))) {
			retStatus = 0;
		}
		/* append character */
		ret_chrs[chr_i++] = 0x30 + (rest_of_nr / nr_size);
		
		rest_of_nr = rest_of_nr % nr_size;
		nr_size = nr_size / 10;
	}
	
	return retStatus;
}