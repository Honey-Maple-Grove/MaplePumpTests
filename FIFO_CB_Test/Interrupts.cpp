// 
// 
// 

#include "Interrupts.h"

void InterruptsClass::init()
{


}


void InterruptsClass::push(EnumsClass::Interrupt interrupt){
	InteruptBufferClass::push(interrupt);
}


void InterruptsClass::priorty(EnumsClass::Interrupt interrupt){
	InteruptBufferClass::pushhead(interrupt);
}


char* InterruptsClass::runFunction(EnumsClass::Interrupt thisInterrupt)
{
	switch (thisInterrupt)	
	{
	case EnumsClass::CheckInTemp:
		return "CheckInTemp";
		break;
	case EnumsClass::CheckMinSensors:
		return "CheckMinSensors"; 
		break;
	case EnumsClass::CheckSapFloat:
		return "CheckSapFloat";
		break;
	case EnumsClass::CheckSapLines:
		return "CheckSapLines";
		break;
	case EnumsClass::Void:
		return "Void";
		break;
	}

}


InterruptsClass Interrupts;

