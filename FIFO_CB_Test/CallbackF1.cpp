// 
// 
// 

#include "CallbackF1.h"

void CallbackF1Class::init(long msWait)
{
	_millisWait = msWait;
}


void CallbackF1Class::run(){
	if(CallbackClass::okToRun()){
		CallbackClass::popBuffer();
		CallbackF1Class::actualWork();
	}
}


function_pointer _runPointer = CallbackF1Class::run;
function_pointer CallbackF1Class::runPointer(){	
	// return_type (class_name::*ptr_name) (argument_type) = &class_name::function_name;
	void	(CallbackF1Class::*runPtr)() = &CallbackF1Class::run;
	return (function_pointer)runPtr;
}
void CallbackF1Class::actualWork(){
	Serial.println("F1 Done");
}

CallbackF1Class CallbackF1;

