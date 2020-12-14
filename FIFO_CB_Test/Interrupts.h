// Interrupts.h

#ifndef _INTERRUPTS_h
#define _INTERRUPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "CallbackF1.h"
class InterruptsClass
{
 protected:


 public:
	void init();
};

extern InterruptsClass Interrupts;

#endif

