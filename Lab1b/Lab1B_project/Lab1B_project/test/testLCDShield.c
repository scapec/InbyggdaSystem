//
//  testLCDShield.c
//  tests for controlling and writing to the LCD display
//  Note that it does not test the timer functions
//
//  Created by Ulrik on 2013-11-06.
//
//  Modified by Mathias Beckius & Soded Alatia 2013-11-20
//	Modifications applied to create Unity tests for Lab1b
//

#include "unity.h"

#include "../src/LCDShield.h"
#include "testLCDShield.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LCDShieldInitialisesProperly(void)
{
    TEST_ASSERT_TRUE(LCDInit());
}

void test_LCDShieldDisplaysASingleByte(void)
{
    TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('H')), LCDwrite('H', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('e')), LCDwrite('e', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('l')), LCDwrite('l', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('l')), LCDwrite('l', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('o')), LCDwrite('o', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII(' ')), LCDwrite(' ', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('W')), LCDwrite('W', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('o')), LCDwrite('o', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('r')), LCDwrite('r', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('l')), LCDwrite('l', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('d')), LCDwrite('d', HIGH));
	TEST_ASSERT_EQUAL_UINT8(FLIP_NIBBLES(ASCII('!')), LCDwrite('!', HIGH));
	/*
    TEST_ASSERT_EQUAL_UINT8(0b01100001, LCDwrite(0x68, HIGH));				//0x68 is hex for ASCII symbol 'h'
    TEST_ASSERT_EQUAL_UINT8(0b01101010, LCDwrite((uint8_t) 101, HIGH));		// 101 is decimal and need sto have an explicit cast to a singel byte
    TEST_ASSERT_EQUAL_UINT8(0b01100011, LCDwrite(0x6C, HIGH));
    TEST_ASSERT_EQUAL_UINT8(0b01100011, LCDwrite(0x6C, HIGH));
    TEST_ASSERT_EQUAL_UINT8(0b01101111, LCDwrite(0x6F, HIGH));
    TEST_ASSERT_EQUAL_UINT8(0b01000011, LCDwrite(0x2C, HIGH));
    TEST_ASSERT_EQUAL_UINT8(0b01000000, LCDwrite(0x20, HIGH));	
	TEST_ASSERT_EQUAL_UINT8(0b11101110, LCDwrite('w', HIGH));				//'w' has hex value 0x77
	TEST_ASSERT_EQUAL_UINT8(0b01101111, LCDwrite('o', HIGH));
	TEST_ASSERT_EQUAL_UINT8(0b11100100, LCDwrite('r', HIGH));		
	TEST_ASSERT_EQUAL_UINT8(0b01100011, LCDwrite('l', HIGH));		
	TEST_ASSERT_EQUAL_UINT8(0b01100010, LCDwrite('d', HIGH));				
	*/
}


void test_ClearLCDDisplay(void)
{
	TEST_ASSERT_TRUE(LCDclear());
}

void test_LCDWritesInteger_4digits(void)
{
	char retChrs[20];
	int retStatus;
	
	memset(retChrs, '\0', 20);
	retStatus = LCD_write_integer(1234, retChrs);
	TEST_ASSERT_TRUE(strcmp(retChrs, "1234") == 0);
	TEST_ASSERT_TRUE(retStatus);
}

void test_LCDWrites_NegativeNumbers(void)
{
	char retChrs[20];
	int retStatus;
	
	memset(retChrs, '\0', 20);
	retStatus = LCD_write_integer(-1234, retChrs);
	TEST_ASSERT_TRUE(strcmp(retChrs, "-1234") == 0);
	TEST_ASSERT_TRUE(retStatus);
}

void test_LCDWrites_otherThan4Digits(void)
{
	char retChrs[20];
	int retStatus;
	
	memset(retChrs, '\0', 20);
	retStatus = LCD_write_integer(115200, retChrs);
	TEST_ASSERT_TRUE(strcmp(retChrs, "115200") == 0);
	TEST_ASSERT_TRUE(retStatus);
	
	LCDwrite(' ', HIGH);
	
	memset(retChrs, '\0', 20);
	retStatus = LCD_write_integer(-12, retChrs);
	TEST_ASSERT_TRUE(strcmp(retChrs, "-12") == 0);
	TEST_ASSERT_TRUE(retStatus);
}
/*
void test_ConvertAFourDigitNumberToASCII(void)
{
	
}
*/

/*
void test_LCDShieldDisplaysAFourDigitNumber(void);
{
	
}
*/
