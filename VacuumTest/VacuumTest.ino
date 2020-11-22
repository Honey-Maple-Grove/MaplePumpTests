/*
    Name:       VacuumTest.ino
    Created:	1/24/2020 8:04:00 AM
    Author:     ABBOTT-LAP\Abbott
*/
int sensor1 = 0; // select the input pin for sensor 1

int sensorValue1 = 512; // variable to store the value coming from sensor 1

void setup()
{

    Serial.begin(115200); // initialize serial communications
    while (!Serial);      // 
    Serial.print("Vacuum Sensor Test ");
    Serial.println();
    delay(3000);

}

void loop()
{

    sensorValue1 = analogRead(sensor1); // read the value from sensor1:
    delay(1000); // pause for 1 second
    Serial.print("sensor 1 = "); // print to screen
    Serial.println();
    Serial.println(sensorValue1); // print sensor value to screen
    Serial.println();

}
