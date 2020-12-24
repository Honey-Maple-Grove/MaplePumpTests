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
	static const int _bufferSize = 20;
protected:

	typedef void (*fPointer)(InteruptorClass interupt);
private:
	static CircularBuffer<InteruptorClass, _bufferSize> cBuffer;
	static bool push(InteruptorClass interupt);
	static bool priority(InteruptorClass interupt);
	static InteruptorClass peek();
	static InteruptorClass pop();
	static void BuildStaticTest();
	static void RunStaticTest();
	

// Test stuff

	static void TestCall(InteruptorClass interupt) {
		Serial.println("CB1 called");
	}


public:
	static void init ();
	static int interuptCount();
	static bool hasInterupts();
	static InteruptorClass runNextInterupt();
	//static void setupTest();
};

extern InteruptClass Interupt;

#endif

