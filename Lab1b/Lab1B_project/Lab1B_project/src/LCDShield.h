/*
 * LCDShield.h
 * Code to be used in Lab 1b
 *
 * Created by Ulrik on 2013-11-06.
 * Based on code from Tommy Andersson.
 *
 * Modified by Mathias Beckius & Soded Alatia 2013-11-20
 * Added features:
 *	- functions required for Lab1b:
 *		- int LCD_write_integer(int32_t, char*)
 *		- int LCDclear(void)
 *	- some nice macros to make life easier
 */

#ifndef LCDShield_h
#define LCDShield_h

#include "asf.h" /* Ugly but necessary */

#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define LCD_mask_D4_D7 0b00000111100000000000000000000000

/* get ASCII value from character */
#define ASCII(chr) ((uint8_t)chr)

/* get character from ASCII value */
#define CHR(ascii) ((char)ascii)

/* get value of bit at position n */
#define BIT(number, n) (((number) >> (n)) & 1)

/* flip 4 bits, ex: 1010 -> 0101 */
#define FLIP_NIBBLE(nibble) ((BIT((nibble),0) << 3) | (BIT((nibble),1) << 2) | \
							 (BIT((nibble),2) << 1) | (BIT((nibble),3) << 0))

/* flip both nibbles, ex: 1010 0001 -> 0101 1000 */
#define FLIP_NIBBLES(byte) ((FLIP_NIBBLE(byte >> 4) << 4) | \
							 FLIP_NIBBLE(byte & 0x0F))

void delay_init(void);
void delay(uint32_t);
int LCDInit(void);
int LCDclear(void);
uint8_t LCDwrite(uint8_t, bool);
int LCD_write_integer(int32_t, char*);
void ADCsetup(void);

#endif