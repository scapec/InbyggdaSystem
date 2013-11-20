//
//  testLCDShield_Runner.c
//  Playing with Unity
//
//  Created by ac7391 on 2013-10-29.
//  Modified by Mathias Beckius & Soded Alatia 2013-11-20
//	Modifications applied to create Unity tests for Lab1b
//

#include <setjmp.h>
#include <stdio.h>
#include <stdio_serial.h>
#include "asf.h"
#include "conf_board.h"
#include "../test/unity.h"
#include "testLCDShield.h"
#include "LCDShield.h"

static void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

static void runTest(UnityTestFunction test)
{
	if (TEST_PROTECT())
	{
		setUp();
		test();
	}
	if (TEST_PROTECT() && !TEST_IS_IGNORED)
	{
		tearDown();
	}
}

void resetTest(void)
{
	tearDown();
	setUp();
}

int main(void)
{
	/* Initialize the Arduino Due system */
	sysclk_init();
	board_init();
	
	/* Initialize the timer used for delays */
	delay_init();
	
	/* initialize the I/O-port used for transmitting data to the LCD-shield */
	ioport_init();

	/* Initialize the console UART used from within Atmel Studio*/
	configure_console();
	
	/* From here on the program uses the Unity testing framework */
	Unity.TestFile = "testLCDShield.c";
	UnityBegin();
	
	/* Run the tests from the test-file */
	RUN_TEST(test_LCDShieldInitialisesProperly, 20);
	RUN_TEST(test_LCDShieldDisplaysASingleByte, 30);
	delay(3000000);
	RUN_TEST(test_ClearLCDDisplay, 40);
	RUN_TEST(test_LCDWritesInteger_4digits, 40);
	delay(3000000);
	RUN_TEST(test_ClearLCDDisplay, 40);
	RUN_TEST(test_LCDWrites_NegativeNumbers, 50);
	delay(3000000);
	RUN_TEST(test_ClearLCDDisplay, 40);
	RUN_TEST(test_LCDWrites_otherThan4Digits, 60);
	
	UnityEnd();
	
	return 0;
}
