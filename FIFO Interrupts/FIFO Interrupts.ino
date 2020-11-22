// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       FIFO Interrupts.ino
    Created:	11/17/2020 10:31:11 AM
    Author:     DESKTOP-QQOLG5N\Abbot
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts

#include <FIFO_CB.h>
#include <TimerThree.h>
#include <Interrupts.h>
#include <DefinedValues.h>
const int led = LED_BUILTIN;  // the pin with a LED
	int testCount = 0;
void setup()
{	{
	  pinMode(led, OUTPUT);
	  Timer3.initialize(Timer_1_Sec);
	  Timer3.attachInterrupt(testState); // blinkLED to run every 0.15 seconds

	 Serial.begin(115200);
	 while (!Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
// Do all the initializtion here
	TestSetup();
}

void TestSetup()
{
	
}

// Add the main program code into the continuous loop() function
void loop()
{


}
