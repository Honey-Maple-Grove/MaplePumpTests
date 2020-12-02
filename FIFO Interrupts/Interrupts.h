// Interrupts.h

#ifndef _INTERRUPTS_h
#define _INTERRUPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DefinedValues.h"
#include "Enms.h"
#include <FIFO_CB.h>
//#include "Heater.h"
//#include "SapLines.h"
//#include "SapTankPump.h"
//#include "TankFloat.h"
//#include "TempCheck.h"
//#include "Vacuum.h"
//#include "VacuumPump.h"

class InterruptsClass
{

private:
public:
	static void CheckSensors();
	static void Init();
	//static void AttachInterrupt(uint8_t intId, void (*callBack)(), int mode);
	//static void DetachInterrupt(uint8_t intId);
	//static void SetupInterrupts();
	static bool IsInterruptQueued();
	static int QueueSize();
	//static void ManageHeater();
	//static void ManageVacuumPump();
	//static void ManageSapPump();
	static void Restart();
	//static void RunNextInterruptFunction();
	static function_pointer PeekNextInterruptFunction();
	static function_pointer PopNextInterruptFunction();
	//static void StartInterrupts();
	//static void StopInterrupts();
	static void Shutdown();
	//static void TestSapLines();
	static void TimeCheckSensors();
};

extern InterruptsClass Interrupts;

#endif

