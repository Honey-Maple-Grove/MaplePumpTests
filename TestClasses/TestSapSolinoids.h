// TestSapSolinoids.h

#ifndef _TESTSAPSOLINOIDS_h
#define _TESTSAPSOLINOIDS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TestSapSolinoidsClass
{
 protected:


 public:
	void Init();
};

extern TestSapSolinoidsClass TestSapSolinoids;

#endif

