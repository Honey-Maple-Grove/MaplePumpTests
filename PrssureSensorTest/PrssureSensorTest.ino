// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       PrssureSensorTest.ino
    Created:	6/17/2019 4:11:48 PM
    Author:     ABBOTT-LAP\Abbott
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#define VACUUM_SENSOR_PIN 3
float sensorValue = 0;
float highestValue = 0;
float lowestValue = 0;
float lastValue = 0;
void setup()
{

	// start serial port
	Serial.begin(9600);
	Serial.println("mpx4250D Vacuum Demo");
	sensorValue = analogRead(VACUUM_SENSOR_PIN);
	lowestValue = highestValue = sensorValue;

}

// Add the main program code into the continuous loop() function
void loop()
{
	sensorValue = analogRead(VACUUM_SENSOR_PIN);
	if (sensorValue > highestValue) highestValue = sensorValue;
	if (sensorValue < lowestValue) lowestValue = sensorValue;
	char charBuffer[15];
	dtostrf(lowestValue, 5, 2, charBuffer);
	String lowestVal = String(charBuffer);
	dtostrf(sensorValue, 5, 2, charBuffer);
	String sensorVal = String(charBuffer);
	dtostrf(highestValue, 5, 2, charBuffer);
	String highestVal = String(charBuffer);
	if (lastValue != sensorValue) {
		lastValue = sensorValue;
		Serial.println("Vacuum is " + lowestVal + "---" + sensorVal + "---" + highestVal);
	}
	delay(1000);

}
