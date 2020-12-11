// CallbackF1.h

#ifndef _CALLBACKF1_h
#define _CALLBACKF1_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Callback.h"
class CallbackF1Class : public CallbackClass
{
 protected:
	function_pointer _runPointer = run;
	 static void actualWork(); 
 public:
	void init(long msWait);
	static void run();
	function_pointer runPointer();
};

extern CallbackF1Class CallbackF1;

#endif

