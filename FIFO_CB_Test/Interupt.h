// Interrupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Enms.h"
#include <CircularBuffer.h>

class InteruptClass
{
private:
	static  CircularBuffer<InteruptorClass, BufferSize> cBuffer;
public:
	static void init ();
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
};

extern InteruptClass Interupt;

#endif

