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
typedef void (*fPointer)(InteruptorClass interupt);
 protected:

 public:

	 InteruptorClass(void (*fPointer)(InteruptorClass interupt),
		 EnumsClass::Interupt pushPriority,
		 EnumsClass::Interupt fName,
		 unsigned long period,
		 int repeats,
		 int repeatCount);
	 ~InteruptorClass() {};

	 void init(void (*fPointer)(InteruptorClass interupt),
		 EnumsClass::Interupt pushPriority,
		 EnumsClass::Interupt fName,
		 unsigned long period,
		 int repeats,
		 int repeatCount);
	bool canRunFunction();
	bool canInteruptInfoBeDeleted();
	EnumsClass::Interupt Interupt();
	void runInterupt();
	void deleteMe();
	void printlnMe();
	void repeatCount(int count);
private:
EnumsClass::Interupt _fName;
EnumsClass::Interupt _pushPriority;
unsigned long _currentMillis;
unsigned long _lastMillis;
unsigned long _period;
int _repeats;
int _repeatCount = 0; // actual number of function process runs
fPointer _fPointer;
};

extern InteruptorClass Interuptor;

#endif

