// 
// 
// 

#include "CallbackF1.h"

void CallbackF1Class::init(long msWait, EnumsClass::Interrupt thisInterrupt)
{
	_millisWait = msWait;
	_thisInterrupt = thisInterrupt;
}


void CallbackF1Class::run(){
	if(CallbackClass::okToRun()){
		CallbackClass::popBuffer();
		CallbackF1Class::actualWork();
	}
}



void CallbackF1Class::actualWork(){
	Serial.println(EnumsClass::EnumStr(_thisInterrupt));
}

CallbackF1Class CallbackF1;

