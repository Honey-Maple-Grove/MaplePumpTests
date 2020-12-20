// Interrupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enms.h"
#include "InteruptBuffer.h"

class InteruptClass
{
private:
public:
	static void init ();
	static bool push(InteruptorClass interuptor);
	static bool priority(InteruptorClass interuptor);
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
};

extern InteruptClass Interupt;

#endif

