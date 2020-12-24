// interrupts.cpp
// 
// 
#include "Interupt.h"
/*
Interrupt notes
	There are three interrupts types used in the pump system:
		Timed – Every second. This is used by `the temperature and vacuum calculations
		routines, along with the vacuum test.
		Tank float - Whenever the status of the tank float changes: Full or empty, a change interrupt is raised.
		Flow meter - for each rotation of the flowmeter and interrupt is raised to increment the flow counter.
		
		The timed and senssor test Interrupts set flags that are tested in the sketch loop. The flowmeter interrupt just increments The counter.Flow calculations are performed anytime a log record is created.
		The priority order of handling the interrupts are:Tank float then timed interrupts. 
		The vacuum interrupt is handled in eight slices, one for each line. 
		Each line is tested through One iteration of the loop.
		The first iteration Tests the vacuum and closes all the lines if vacuum is lost.
		Each subsequent iteration tests the next line.

		Once this is operational, integration with the web server time slices will be done.
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

void InteruptClass::init() {
	Serial.print("enter Interrupt");
	InteruptClass::BuildStaticTest();
}

void destroyClass(InteruptorClass interupt){

}
bool InteruptClass::push(InteruptorClass interuptor){
	InteruptClass::cBuffer.push(interuptor);
}

InteruptorClass InteruptClass::peek(){
		return InteruptClass::cBuffer.first();
}

InteruptorClass InteruptClass::pop(){
		return InteruptClass::cBuffer.pop();
}

int InteruptClass::interuptCount(){
		return InteruptClass::cBuffer.size();
}

bool InteruptClass::priority(InteruptorClass interuptor){
	InteruptClass::cBuffer.unshift(interuptor);
}

bool InteruptClass::hasInterupts(){
	return !InteruptClass::cBuffer.isEmpty();
}

// Aside from init, this is the only function called - not invoked by an interupt
// It is called in loop. If the function is deletred, the Interuptor must be destroyed
InteruptorClass InteruptClass::runNextInterupt()
{
	InteruptorClass interuptor  = InteruptClass::peek();
	if(interuptor.canRunFunction()){
		interuptor.runInterupt();
		if(interuptor.canInteruptInfoBeDeleted()){
			InteruptClass::pop();
			interuptor.deleteMe();
		}
	}
	else 
	{
	// do nothimg
	}
}

// Test Stufff{
void InteruptClass::RunStaticTest() {
	Serial.println("Consuming test fifo queue");
	while (InteruptClass::hasInterupts()) {
		InteruptClass::runNextInterupt();
	}
}

void testFunction(InteruptorClass interupt) {
	interupt.printlnMe();
}

void InteruptClass::BuildStaticTest() {
	int order = 0;
	Serial.println("Building test fifo queue");
	InteruptorClass inter; 
	inter.init(testFunction, EnumsClass::Push,EnumsClass::CheckInTemp, ++order,2);
	InteruptClass::push(inter);
	inter.printlnMe();
	inter.init(testFunction, EnumsClass::Push,EnumsClass::CheckMinSensors, ++order,3);
	InteruptClass::push(inter);
	inter.printlnMe();
	inter.init(testFunction, EnumsClass::Push,EnumsClass::CheckSapLines, ++order,4);
	InteruptClass::push(inter);
	inter.printlnMe();
	inter.init(testFunction, EnumsClass::Priority,EnumsClass::CheckSapFloat, ++order,1);
	InteruptClass::push(inter);
	inter.printlnMe();
	inter.init(testFunction, EnumsClass::Push,EnumsClass::Void, ++order,5);
	InteruptClass::push(inter);
	inter.printlnMe();
	Serial.print("Buffer Count - ");
	Serial.println(cBuffer.size()); 
}

InteruptClass Interrupt;

