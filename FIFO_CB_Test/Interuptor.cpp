// 
// 
// 

#include "Interuptor.h"

void InteruptorClass::init(void (*fPointer)(InteruptorClass interupt),
	EnumsClass::Interupt pushPriority,
	EnumsClass::Interupt fName,
	long cycle,
	int repeats)
{
		_fPointer = fPointer;
		_pushPriority = pushPriority;
		_fName = fName;
		_cycle = cycle;
		_repeats = repeats;
}

	bool InteruptorClass::canRunFunction() {
		if((millis() >= _lastMillis + _cycle) && 
			_repeatCount <= _repeats){
			_repeatCount++;
			_lastMillis = millis();
			return true;
		}
		else{
		return false;}
	}

	void InteruptorClass::printlnMe() {
		String aboutMe = EnumsClass::EnumStr(_pushPriority) + "-"
			+ EnumsClass::EnumStr(_fName) + "-"
			+ _cycle + "/"
			+ _repeats;
		Serial.println(aboutMe);
	}
	
	bool InteruptorClass::canInteruptInfoBeDeleted(){
		return _repeatCount <= _repeats;
	}

	EnumsClass::Interupt InteruptorClass::Interupt(){
		return _interupt;
	} 
	void InteruptorClass::runInterupt(){
		_fPointer;
	}

	void InteruptorClass::deleteMe(){
		delete this;
	}
InteruptorClass Interuptor;

