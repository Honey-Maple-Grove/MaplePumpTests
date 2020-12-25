// 
// 
// 

#include "Interuptor.h"


void InteruptorClass::init(void (*fPointer)(InteruptorClass interupt),
	EnumsClass::Interupt pushPriority,
	EnumsClass::Interupt fName,
	long cycle,
	int repeats,
	int interuptCount)
{
		_fPointer = fPointer;
		_pushPriority = pushPriority;
		_fName = fName;
		_cycle = cycle;
		_repeats = repeats;
		_interuptCount = interuptCount;
}
void InteruptorClass::InteruptCount(int count) {
	_interuptCount = count;
}
	bool InteruptorClass::canRunFunction() {
		if((millis() >= _lastMillis + _cycle) && 
			_repeatCount <= _repeats){
			_repeatCount++;
			_lastMillis = millis();
			return true;
		}
		else{
			return false;
		}
	}

	void InteruptorClass::printlnMe() {
		String aboutMe = _interuptCount + " " +
			EnumsClass::EnumStr(_pushPriority) + "-"
			+ EnumsClass::EnumStr(_fName) + "-"
			+ _cycle + "/"
			+ _repeats;
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
InteruptorClass Interuptor;

