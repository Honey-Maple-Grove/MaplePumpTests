// TestLogging.h

#ifndef _TESTLOGGING_h
#define _TESTLOGGING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TestLoggingClass
{
 protected:


 public:
	void init();
};

extern TestLoggingClass TestLogging;

#endif

