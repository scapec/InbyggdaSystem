/*
 * TestDegreeFunctions.h
 *
 * Created: 2013-10-30 15:10:43
 * Author: staff
 *
 * Modified by Mathias Beckius & Soded Alatia 2013-11-20
 * Modifications applied to create Unity tests for Lab1b
 */ 


#ifndef TESTLCDSHIELD_H_
#define TESTLCDSHIELD_H_

#include <string.h>

void setUp(void);
void tearDown(void);
void test_LCDShieldInitialisesProperly(void);
void test_LCDShieldDisplaysASingleByte(void);
void test_ClearLCDDisplay(void);
void test_LCDWritesInteger_4digits(void);
void test_LCDWrites_NegativeNumbers(void);
void test_LCDWrites_otherThan4Digits(void);

/*
void test_ConvertAFourDigitNumberToASCII(void);
void test_LCDShieldDisplaysAFourDigitNumber(void);
*/

#endif /* TESTLCDSHIELD_H_ */