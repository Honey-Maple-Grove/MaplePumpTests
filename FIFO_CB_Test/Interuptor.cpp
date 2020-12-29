// 
// InteruptorClass
//
// == function pointer -  function to run when Iteruptor wait period has elapsed
// == period - period to wait (in millis) for function to run
// == repeat indicator - after function runs, it sets this true if it has to be run again
//  I use this in my maple sap vacuum to test multiple valves (maple lines) for pressure leakage
// 

#include "Interuptor.h"

typedef void (*fPointer)();
EnumsClass::Interupt _functionName;
EnumsClass::Interupt _fifoLifoPush;
unsigned long _currentMillis;
unsigned long _lastMillis;
unsigned long _period;
bool _repeatMe;
int _repeatCount = 0; // actual number of function process runs
fPointer _fPointer;
// The enums are used for testing display - not requied for implementation
InteruptorClass::InteruptorClass(void (*fPointer)(InteruptorClass interupt),
	EnumsClass::Interupt fifoLifoPush,
	EnumsClass::Interupt functionName,
	unsigned long period)
{
	_fPointer = fPointer;
	_fifoLifoPush = fifoLifoPush;
	_functionName = functionName;
	_period = period;
	_repeatMe = false;
	_lastMillis = millis(); // used for millis() period test
}

// number of timed the iterupt function has run
void InteruptorClass::incrRepeatCount() {
	_repeatCount++;
}

void InteruptorClass::setRepeat(bool repeat) {
	_repeatMe = repeat;
}

int InteruptorClass::repeatCount() {
	return _repeatCount;
}

bool InteruptorClass::repeatMe() {
	return _repeatMe;
}

bool InteruptorClass::canRunFunction() {
	_currentMillis = millis();
	if(_currentMillis - _lastMillis >= _period){
		_lastMillis = millis();
		return true;
	}
	else{
		return false;
	}
}

void InteruptorClass::printlnMe() {
	String aboutMe = 
		EnumsClass::EnumStr(_fifoLifoPush) + "-"
		+ EnumsClass::EnumStr(_functionName) + "-"
		+ _period + "/"
		+ _repeatMe ;
	Serial.println(aboutMe);
}
	
EnumsClass::Interupt InteruptorClass::Interupt(){
	return _functionName;
} 

void InteruptorClass::runInterupt(){
	_fPointer();
}

void InteruptorClass::deleteMe(){
	delete this;
}
//InteruptorClass Interuptor;

