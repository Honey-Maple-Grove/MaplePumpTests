// 
// 
// 

#include "Interuptor.h"


InteruptorClass::InteruptorClass(void (*fPointer)(InteruptorClass interupt),
	EnumsClass::Interupt pushPriority,
	EnumsClass::Interupt fName,
	unsigned long period,
	int repeats,
	int repeatCount)
{
	_fPointer = fPointer;
	_pushPriority = pushPriority;
	_fName = fName;
	_period = period;
	_repeats = repeats;
	_repeatCount = repeatCount;
}
void InteruptorClass::init(void (*fPointer)(InteruptorClass interupt),
	EnumsClass::Interupt pushPriority,
	EnumsClass::Interupt fName,
	unsigned long period,
	int repeats,
	int repeatCount)
{
		_fPointer = fPointer;
		_pushPriority = pushPriority;
		_fName = fName;
		_period = period;
		_repeats = repeats;
		_repeatCount = repeatCount;
		_lastMillis = millis();
}
void InteruptorClass::repeatCount(int count) {
	_repeatCount = count;
}
	bool InteruptorClass::canRunFunction() {
		_currentMillis = millis();
		if((_currentMillis - _lastMillis >= _period) &&
			_repeatCount >= _repeats){
			_repeatCount++;
			_lastMillis = millis();
			return true;
		}
		else{
			_repeatCount++;
			return false;
		}
	}

	void InteruptorClass::printlnMe() {
		String aboutMe = 
			EnumsClass::EnumStr(_pushPriority) + "-"
			+ EnumsClass::EnumStr(_fName) + "-"
			+ _period + "/"
			+ _repeats + " /" 
			+ _repeatCount;
		Serial.println(aboutMe);
	}
	
	bool InteruptorClass::canInteruptInfoBeDeleted(){
		return _repeatCount <= _repeats;
	}

	EnumsClass::Interupt InteruptorClass::Interupt(){
		return _fName;
	} 
	void InteruptorClass::runInterupt(){
		_fPointer;
	}

	void InteruptorClass::deleteMe(){
		delete this;
	}
//InteruptorClass Interuptor;

