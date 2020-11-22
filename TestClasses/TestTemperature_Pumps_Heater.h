// TestTemperature_Pumps_Heater.h

#ifndef _TESTTEMPERATURE_PUMPS_HEATER_h
#define _TESTTEMPERATURE_PUMPS_HEATER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TestTemperature_Pumps_HeaterClass
{
 protected:


 public:
	void init();
};

extern TestTemperature_Pumps_HeaterClass TestTemperature_Pumps_Heater;

#endif

