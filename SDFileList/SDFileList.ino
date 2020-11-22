// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       SDFileList.ino
    Created:	6/24/2019 12:36:21 PM
    Author:     ABBOTT-LAP\Abbott
*/
/*  SDlistFiles

 This example shows how print out the files in a directory on a SD card

 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 Adafruit #2971 and Metro/Uno

 created   Nov 2010 by David A. Mellis
 modified 9 Apr 2012 by Tom Igoe
 modified 2 Feb 2014 by Scott Fitzgerald
 modified 12 Apr 2018 by Mike Barela

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File root;
void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	// try to congifure using DHCP address instead of IP:

	Serial.print("Initializing SD card...");
	pinMode(10, OUTPUT); // required for SD lib
	digitalWrite(10, HIGH);
	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");

	root = SD.open("/");
			Serial.print("Dir - ");
			String name = root.name();
			Serial.println(name);

	printDirectory(root, 0);

	Serial.println("done!");


}

void loop() {
	// nothing happens after setup finishes.
}
void printDirectory(File dir, int numTabs) {
	while (true) {
		File entry = dir.openNextFile();
		if (!entry) {
			// no more files
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++) {
		}

		Serial.print(entry.name());
		if (entry.isDirectory()) {
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		}
		else {
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
		}
		entry.close();
	}
}
