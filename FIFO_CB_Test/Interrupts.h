// Interrupts.h

#ifndef _INTERRUPTS_h
#define _INTERRUPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "CallbackF1.h"
#include "InteruptBuffer.h"
class InterruptsClass
{
 protected:
	CallbackF1Class f1;
	CallbackF1Class f2;
	CallbackF1Class f3;
	CallbackF1Class f4;
	CallbackF1Class f5;

 public:
	static void init();
	static char* runFunction(EnumsClass::Interrupt);
	static void push(EnumsClass::Interrupt);
	static void priorty(EnumsClass::Interrupt);

};

extern InterruptsClass Interrupts;

#endif

