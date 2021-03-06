// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Blinker.ino
    Created:	5/15/2019 7:34:30 PM
    Author:     ABBOTT-LAP\Abbott
*/

#define PIN_LED1 6
#define PIN_LED2 7
#define PIN_LED3 5
#define PIN_LED4 6

/*
 * BLINKER CLASS DEFINITION
 */
	class Blinker {
	private:
		byte pinLED;

		boolean ledState = LOW;

		unsigned long timeLedOn;
		unsigned long timeLedOff;

		unsigned long nextChangeTime = 0;

	public:
		Blinker(byte pinLED, unsigned long timeLedOn, unsigned long timeLedOff) {
			this->pinLED = pinLED;
			this->timeLedOn = timeLedOn;
			this->timeLedOff = timeLedOff;

			pinMode(pinLED, OUTPUT);
		}

		// Checks whether it is time to turn on or off the LED.
		void check() {
			unsigned long currentTime = millis();

			if (currentTime >= nextChangeTime) {

				if (ledState) {
					// LED is currently turned On. Turn Off LED.
					ledState = LOW;
					nextChangeTime = currentTime + timeLedOff;
				}
				else {
					// LED is currently turned Off. Turn On LED.
					ledState = HIGH;
					nextChangeTime = currentTime + timeLedOn;
				}

				digitalWrite(pinLED, ledState);
			}
		}
};

/*
 *  BLINKER CLASS VARIABLES DECLARATION
 */
Blinker blink1 = Blinker(PIN_LED1, 500, 500);
Blinker blink2 = Blinker(PIN_LED2, 2000, 2000);
Blinker blink3 = Blinker(PIN_LED3, 2000, 2000);
Blinker blink4 = Blinker(PIN_LED4, 1000, 2000);

void setup() {

}

void loop() {
	blink1.check();
	blink2.check();
	//blink3.check();
	//blink4.check();
}