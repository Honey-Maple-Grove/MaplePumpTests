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
		The lifoPush order of handling the interrupts are:Tank float then timed interrupts. 
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

static const int _bufferSize = 20;
static CircularBuffer<InteruptorClass*, _bufferSize> cBuffer;
void InteruptClass::init() {
}

bool InteruptClass::fifoPush(InteruptorClass* interuptor){
	cBuffer.push(interuptor);
}

InteruptorClass* InteruptClass::peek(){
		return cBuffer.first();
}

InteruptorClass* InteruptClass::pop(){
		return cBuffer.pop();
}

int InteruptClass::interuptCount(){
		return cBuffer.size();
}

bool InteruptClass::lifoPush(InteruptorClass* interuptor){
	cBuffer.unshift(interuptor);
}

bool InteruptClass::hasInterupts(){
	return !cBuffer.isEmpty();
}

// Aside from init, this is the only function called - not invoked by an interupt
// It is called in loop. If the function is deletred, the Interuptor must be destroyed
InteruptorClass InteruptClass::runNextInterupt()
{
	InteruptorClass* interuptor  = InteruptClass::peek();
	if(interuptor->canRunFunction()){
		interuptor->runInterupt();
		//interuptor->repeatCount(cBuffer.size()); // ????
		if(interuptor->canInteruptInfoBeDeleted()){
			InteruptClass::pop();
			interuptor->deleteMe();
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
	InteruptorClass* inter1 = new InteruptorClass 
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckInTemp, ++order,2, cBuffer.size());
	InteruptClass::fifoPush(inter1);
	inter1->printlnMe();

	InteruptorClass* inter2 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckMinSensors, ++order,3, cBuffer.size());
	InteruptClass::fifoPush(inter2);
	inter2->printlnMe();

	InteruptorClass* inter3 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckSapLines, ++order,4, cBuffer.size());
	InteruptClass::fifoPush(inter3);
	inter3->printlnMe();

	InteruptorClass* inter4 = new InteruptorClass
	(testFunction, EnumsClass::LifoPush,EnumsClass::CheckSapFloat, ++order,1, cBuffer.size());
	InteruptClass::lifoPush(inter4);
	inter4->printlnMe();

	InteruptorClass* inter5 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::Void, ++order,5, cBuffer.size());
	InteruptClass::fifoPush(inter5);
	inter5->printlnMe();
	Serial.print("Buffer Count - ");
	Serial.println(cBuffer.size()); 
}

InteruptClass Interrupt;

