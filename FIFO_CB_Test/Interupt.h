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
private:
	static CircularBuffer<InteruptorClass, BufferSize> cBuffer;
	static bool push(InteruptorClass interupt);
	static bool priority(InteruptorClass interupt);
	static InteruptorClass peek();
	static InteruptorClass pop();

public:
	static void init ();
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
	//static void setupTest();
};

extern InteruptClass Interupt;

#endif

