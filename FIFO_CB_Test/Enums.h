// Enms.h

#ifndef _ENUMS_h
#define _ENUMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class EnumsClass
{
 public:


	 enum Interupt{
		CheckInTemp,
		CheckMinSensors, // vacuum, outTemp
		CheckSapFloat,
		CheckSapLines,
		Void,
		FifoPush,
		LifoPush,
	 };

	 static String EnumStr(Interupt interrupt);
};

extern EnumsClass Enums;

#endif

