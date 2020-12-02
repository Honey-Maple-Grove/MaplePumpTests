// Action.h

#ifndef _ACTION_h
#define _ACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "ActionBase.h"
class ActionClass : protected ActionBaseClass
{
 protected:


 public:
	void init();
};

extern ActionClass Action;

#endif

