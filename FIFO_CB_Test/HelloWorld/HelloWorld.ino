
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include "arduino.h"


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	Serial.begin(115200);
	while (!Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
	Serial.print(F("Startup Free RAM: ")); Serial.println(FreeRam());  
	//HMGHelloWorld::Init();
	//// initialize the LCD
	lcd.begin(16,0);
	lcd.noBacklight();
	delay(2000);

	//// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop()
{
	// Do nothing here...
}
