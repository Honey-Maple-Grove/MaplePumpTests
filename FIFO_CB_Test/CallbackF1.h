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
	virtual void actualWork(); 
 public:
	void init(long msWait);
	function_pointer runPointer();
	void run();
};

extern CallbackF1Class CallbackF1;

#endif

