// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       GeneralLogicTest.ino
    Created:	10/9/2019 1:46:21 PM
    Author:     ABBOTT-LAP\Abbott
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
#include "Pins.h"
#include "Vacuum.h"
#include<Arduino.h>

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	while (!Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
	Serial.print(F("Startup: 0")); Serial.println();

	VacuumClass::Init(true);
}

// Add the main program code into the continuous loop() function
void loop()
{
	VacuumClass::IsVacuumLost(0);
	for(int i = 1; i <= LINECOUNT; i++ ){
		bool vacLost = VacuumClass::IsVacuumLost(i);
		Serial.print("Line: " + i );
		Serial.println(" - " + vacLost);
	}

	delay(5000);
}
