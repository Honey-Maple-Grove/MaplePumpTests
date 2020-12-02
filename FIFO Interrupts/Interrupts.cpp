// interrupts.cpp
// 
// 
#include "Interrupts.h"
#include <FIFO_CB.h>
#include <TimerThree.h>

/*
Interrupt notes
	There are three interrupts types used in the pump system:
		Timed – Every x second **. This is used by `the temperatures (in and out) and vacuum test and updating the flow meter count. It pushes a test values FIFO entry onto the queue. 
		Tank float - Whenever the status of the tank float changes: Full or empty, a pin change interrupt is raised.
		Flow meter - for each rotation of the flow meter, a pin interrupt is raised to increment the flow counter.
		
		The timed and float Interrupts set flags that are tested in the sketch loop. The flowmeter interrupt just increments its+ counter.Flow calculations are performed anytime a log record is created.
		The priority order of handling the interrupts are:Tank float then timed interrupts. 
		The vacuum interrupt is handled in eight slices, one for each line. The FIFO Vacuum entry has a counter which is updated and pushed back to the list.
		Each line is tested through One iteration of the loop.
		The first iteration double tests (verifies) the vacuum and closes all the lines if vacuum is lost.
		Each subsequent iteration tests the associated (count) line by opening it. If the vacuum is ok, the line is left open.

		** The timed interval will be determined by	the required line valve delay.
		
		Every interrupt action test pushes an entry onto the FIFO stack.

		Each interrupt function ill have it's own delay count which is increments until the appropriate delay is reached. While counting up the fifo interrupt remains on the queue, when it is completed, the interrupt is popped.

		Once the interrupt processing is operational, integration with the web server time slices will be done.
*/
/*
Timed Line interrupt approach:
When the loop occurs, we check to see which, if any, interrupt is to be flagged to be run in this iteration.
There are 2 options:
 !: Run a specific timed interrupt;
	a: Check Sensors (seys appropriate flags)
	b: Manage Heater
	c: Manage SapPump
	d: Manage vacuum pump
 2: Run a single “line” of the line check
	For the first rep (counter preset to 0), close the all the lines, set rep counter to 1, set timer to 2 seconds
	Calls close lines (2-8)s – using Statics::Delay (2) for 2 seconds,
	line1 force open
	return
Each rep:
		Open line – Delay(2)
		Check Vacuum – if ok, leave open, else  close, set line state
		Counter++
		return
*/
static const bool isTest = true;
static FIFO_CB fifoQueue;


void InterruptsClass::Init() {
	Serial.print("enter Interrupt");
	
	  Timer3.initialize(Timer_1_Sec);
	  Timer3.attachInterrupt(TimeCheckSensors); // blinkLED to run every 0.15 seconds
}


int InterruptsClass::QueueSize() {
	return fifoQueue.size();
}

void InterruptsClass::TimeCheckSensors() {
	fifoQueue.push(InterruptsClass::CheckSensors);
}

bool InterruptsClass::IsInterruptQueued() {
	return fifoQueue.size() > 0;
}          

int QueueSize() {
	return fifoQueue.size();
}

function_pointer InterruptsClass::PeekNextInterruptFunction() {
	
		return fifoQueue.peek();
	
}
function_pointer InterruptsClass::PopNextInterruptFunction() {
	
		return fifoQueue.pop();
}
void InterruptsClass::PutActionTestsOnQueue() {
	
		fifoQueue.push(InterruptsClass::CheckSensors);
}
void InterruptsClass::CheckSensors() {
}
//void InterruptsClass::CheckSensors() { 
//	TempCheckClass::SetTempStates(TEST_TEMP);
//
//	if (TempCheckClass::GetOutState() == EnumsClass::Temperature::OutInRange &&
//		VacuumPumpClass::IsOff()) {
//		fifoQueue.push(InterruptsClass::ManageVacuumPump);
//	}
//	if (TempCheckClass::GetOutState() == EnumsClass::Temperature::OutCold &&
//		VacuumPumpClass::IsOn()) {
//		fifoQueue.push(InterruptsClass::ManageVacuumPump);
//	}
//	if (TempCheckClass::GetOutState() == EnumsClass::Temperature::OutInRange && 
//		VacuumClass::IsVacuumLost()) {
//		fifoQueue.push(InterruptsClass::TestSapLines);
//	}
//	if (TempCheckClass::GetInState() == EnumsClass::Temperature::OutInRange &&
//		VacuumPumpClass::IsOff()){
//		VacuumPumpClass::TurnOn;
//		if (VacuumClass::IsVacuumLost()) {
//			fifoQueue.push(InterruptsClass::TestSapLines);
//		}
//	}		
//}
//void InterruptsClass::ManageSapPump() {
//	if (SapTankPumpClass::IsTankPumpOff() &&
//		TankFloatClass::IsFloatHigh()) {
//		SapTankPumpClass::TurnTankPumpOn;
//	}
//	else {
//		SapTankPumpClass::TurnTankPumpOff;
//	}
//}
//void InterruptsClass::TestSapLines() {
//	bool IsTestLoopComplete = SapLinesClass::CheckAllLines();
//	// If tests not complete ... call again to process next line
//	if (!IsTestLoopComplete) {
//		fifoQueue.push(InterruptsClass::TestSapLines);
//	}
//}
//
//void InterruptsClass::ManageHeater() {
//	if (HeaterClass::IsHeaterOff()  &&
//		TempCheckClass::GetInState() == EnumsClass::Temperature::InCold) {
//		HeaterClass::SetHeater(SET_HEATER_ON);
//	}
//	else {
//		HeaterClass::SetHeater(SET_HEATER_OFF);
//	}
//} 
//
///// Only calld when change of state
//void InterruptsClass::ManageVacuumPump() {
//	if (VacuumPumpClass::IsOff() &&
//		TankFloatClass::IsFloatHigh()) {
//		VacuumPumpClass::TurnOn;
//	}
//	else{
//		VacuumPumpClass::TurnOff;
//	}
//}
void InterruptsClass::Restart() {
	
}
void InterruptsClass::Shutdown() {
	
}
//
//void InterruptsClass::StartInterrupts() {
//	sei();//allow interrupts
//}
//void InterruptsClass::StopInterrupts() {
//	cli();//stop interrupts 
//}

InterruptsClass Interrupts;

