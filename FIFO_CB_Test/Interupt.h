// Interrupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enums.h"
#include <CircularBuffer.h>
#include "Interuptor.h"

class InteruptClass
{
protected:

	typedef void (*fPointer)(InteruptorClass* interupt);
private:
	static bool fifoPush(InteruptorClass* interupt);
	static bool lifoPush(InteruptorClass* interupt);
	static InteruptorClass* peek();
	static InteruptorClass* pop();
public:
	static void init ();
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
	static void BuildStaticTest();
	static void RunStaticTest();
};

extern InteruptClass Interupt;

#endif

