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
};

extern InteruptorClass Interuptor;

#endif

