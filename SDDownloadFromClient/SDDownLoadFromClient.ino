// 
// 
// 

//#include "SDDownLoadFromClient.h"
// Gets a file from the Internet and saves it to the SD card
// Also saves the incoming HTTP header to the file
// This example gets the XML cricket score from synd.cricbuzz.com
//
// References - Arduino Example sketches from IDE by David A. Mellis et al.:
// -- File --> Examples --> Ethernet --> WebClient
// http://www.arduino.cc/en/Tutorial/WebClient
// -- File --> Examples --> SD --> ReadWrite
// http://www.arduino.cc/en/Tutorial/ReadWrite
// 
// Author: W.A. Smith    Date: 10 June 2015
// http://startingelectronics.org/software/arduino/save-web-file-to-SD-card/

#include <avr8-stub.h>
#include <app_api.h>
#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "synd.cricbuzz.com";    // change server to get file from here
IPAddress ip(192, 168, 0, 50);
EthernetClient client;
File theFile;

void setup() {
	// disable Ethernet chip
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	Serial.begin(115200);

	Serial.print(F("Initializing SD card..."));

	if (!SD.begin(4)) {
		Serial.println(F(" initialization failed!"));
		return;
	}
	Serial.println(F(" initialization done."));

	// start the Ethernet connection:
	if (Ethernet.begin(mac) == 0) {
		Serial.println(F("Failed to configure Ethernet using DHCP"));
		// no point in carrying on, so do nothing forevermore:
		// try to congifure using IP address instead of DHCP:
		Ethernet.begin(mac, ip);
	}
	// give the Ethernet shield a second to initialize:
	delay(1000);

	Serial.println("connecting...");

	// if you get a connection, report back via serial:
	if (client.connect(server, 80)) {
		Serial.println("connected");
		// Make a HTTP request:
		client.println("GET /j2me/1.0/livematches.xml HTTP/1.1");  // change resource to get here
		client.println("Host: synd.cricbuzz.com");                 // change resource host here
		client.println("Connection: close");
		client.println();
	}
	else {
		// didn't get a connection to the server:
		Serial.println("connection failed");
	}
	// open the file for writing
	Serial.println("Creating file.");
	theFile = SD.open("results.xml", FILE_WRITE);  // change file name to write to here
	if (!theFile) {
		Serial.println("Could not create file");
		while (1);
	}
}

void loop() {
	// if there are incoming bytes available
	// from the server, read them and print them:
	if (client.available()) {
		char c = client.read();
		theFile.print(c);
	}

	// if the server's disconnected, stop the client:
	if (!client.connected()) {
		Serial.println();
		Serial.println("disconnecting.");
		client.stop();
		theFile.close();
		Serial.println("Finished writing to file");

		// do nothing forevermore:
		while (true);
	}
}


