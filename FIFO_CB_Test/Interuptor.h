// Interuptor.h

#ifndef _INTERUPTOR_h
#define _INTERUPTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enums.h"
#include "Interuptor.h"
class InteruptorClass
{
typedef void (*fPointer)(InteruptorClass interupt);
 protected:

 public:
	 void init(void (*fPointer)(InteruptorClass interupt),
		 EnumsClass::Interupt pushPriority,
		 EnumsClass::Interupt fName,
		 long cycle,
		 int repeats);
	bool canRunFunction();
	bool canInteruptInfoBeDeleted();
	EnumsClass::Interupt Interupt();
	void runInterupt();
	void deleteMe();
	void printlnMe();
private:
	EnumsClass::Interupt _fName;
	EnumsClass::Interupt _pushPriority;
	long _lastMillis;
	long _cycle;
	int _repeats ;
	int _repeatCount = 0;
	fPointer _fPointer;
};

extern InteruptorClass Interuptor;

#endif

