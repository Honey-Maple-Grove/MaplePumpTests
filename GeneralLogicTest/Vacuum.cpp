// 
// 
// 

#include "Vacuum.h"

#define VACUUM_ANALOG_PIN 3
#define VACUUM_PUMP_DIGI 0  // ????
#define TESTLOOPLIMIT 4
#define LINECOUNT 8

	/* Reads pressure from the given pin.
	* Returns a value in Pascals
	* https://forum.arduino.cc/index.php?topic=401642.0
	*/
	static int _testLoopCount = 0;
	static bool _isTesting = false;
	static int _testLineState[LINECOUNT + 1];
	static int _testLineCount;

	void VacuumClass::Init(bool isTesting = false){
		_isTesting = isTesting;
		_testLineCount = sizeof(_testLineState);
	}

	String VacuumClass::GetVacuumPsiStr() {
		char* s;
		dtostrf(GetVacuumPsi(), 4, 1, s);
		return String(s);
	}

	float VacuumClass::GetVacuumPsi() {
		int vacuum = analogRead(VACUUM_ANALOG_PIN);
		// params from spec sheet
		//int kPaInt = map(vacuum, 41, 986, 0, 256);
		float kPaFloat = ((vacuum / 1024.0) - 0.04) / 0.00369;
		float psiFloat = kPaFloat / 6.89475728;
		return psiFloat;
	}

	// line indicates which line is requesting the vacuum
	// 0 = full line test - default
	// n = line # (used during offline logic testing - else ignored)
	bool VacuumClass::IsVacuumLost(int line = 0) {
		const float _stdVacuumPsi = 5; // vacuum to compare to
		if (_isTesting) {
			return IsTestLostPressure(line);
		}
		else {
			return VacuumClass::GetVacuumPsi() < _stdVacuumPsi;
		}
	}

	String VacuumClass::GetActiveLines() {
		String lineList = {};
		for (int i = 1; i <= LINECOUNT - 1; i++) {
			if (_testLineState[i] ==  1) {
				lineList = lineList + i + ',';
			}
		}	
		return lineList;
	}

	void VacuumClass::SetTestLineStates(){
		srandom(millis());
		for (unsigned int i = 1; i <= sizeof(_testLineState); i++){
			int randInt = rand();
			float randTest = 1 / randInt;
			if (randTest > .5){
				_testLineState[i] = 1;
			} else{
				_testLineState[i] = 0;
			}
		}
		Serial.println(GetActiveLines());
	}
	// creates random list if open lines

	bool VacuumClass::IsTestLostPressure(int line){
		bool returnLost = false;
		if(line == 0){
			if (_testLoopCount++ > TESTLOOPLIMIT){
				_testLoopCount = 0;
				SetTestLineStates();
			}
			returnLost = true;
		}
		else{
			returnLost = _testLineState[line] == 1;
		}
		Serial.println(line + ' - ' + returnLost);
		return returnLost;
	}

VacuumClass Vacuum;

