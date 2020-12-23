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
typedef void (*fPointer)(InteruptorClass interupt);
class InteruptorClass
{
 protected:


 public:
	void init(void (*fPointer)(InteruptorClass interupt),
		long cycle,
		int repeats,
		EnumsClass::Interupt interupt);
	bool canRunFunction();
	bool canInteruptInfoBeDeleted();
	EnumsClass::Interupt Interupt();
	void runInterupt();
	void deleteMe();
private:
	
	EnumsClass::Interupt _interupt;
	long _lastMillis;
	long _cycle;
	int _repeats ;
	int _repeatCount = 0;
	fPointer _fPointer;
};

extern InteruptorClass Interuptor;

#endif

