// Interuptor.h

#ifndef _INTERUPTOR_h
#define _INTERUPTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enums.h"
class InteruptorClass
{
typedef void (*fPointer)();
 protected:

 public:

	 InteruptorClass(void (*fPointer)(InteruptorClass interupt),
		 EnumsClass::Interupt pushPriority,
		 EnumsClass::Interupt fName,
		 unsigned long period);
	 ~InteruptorClass() {};

	bool canRunFunction();
	void incrRepeatCount();
	bool repeatMe();
	void setRepeat(bool repeat);
	int repeatCount();
	EnumsClass::Interupt Interupt();
	void runInterupt();
	void deleteMe();
	void printlnMe();
private:
EnumsClass::Interupt _functionName;
EnumsClass::Interupt _fifoLifoPush;
unsigned long _currentMillis;
unsigned long _lastMillis;
unsigned long _period;
bool _repeatMe;
int _repeatCount = 0; // actual number of function process runs
fPointer _fPointer;
};

extern InteruptorClass Interuptor;

#endif

