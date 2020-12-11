// 
// 
// 

#include "CallbackF1.h"

void CallbackF1Class::init(long msWait)
{
	_millisWait = msWait;
}

function_pointer CallbackF1Class::runPointer(){
	_runPointer;
}

void CallbackF1Class::run(){
	if(CallbackClass::okToRun()){
		CallbackClass::popBuffer();
		actualWork();
	}
}
void CallbackF1Class::actualWork(){
	Serial.println("F1 Done");
}

CallbackF1Class CallbackF1;

