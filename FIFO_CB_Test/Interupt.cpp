// interupt.cpp
/* 
	Encapsulatres all interupt handling for a timed interupt/ pin interupt system
	It conatrins all the interupt functions that are pointed to;
	It cantains logic for static testing
	It manages the TimerOne & TimerThree interpts (thanks - 
@PaulStoffregen)(FUTURE)
	If manages the Circular Buffer (thanks - Roberto Lo Giacco)
*/ 
#include "Interupt.h"
/*
Interrupt notes
	1. Initial implementation is without timed interupts (the final objective - use TimerOne/TimeThree) - see ReadMe
	2. The interupt function calls are all done in the IteruptClass - There is no dynammic discovery
	3. Creating an interupt creates and adds an Interuptor to the circular lifo/fifo queue - see Interuptor.h
	4. Since this is designed for timed/pin interupts - there is no loop logic
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
			InteruptClass::pop();
			interuptor->deleteMe();
	}
	else 
	{
	// do nothimg - where waiting for period to elapse 
	}
}

// Test Stufff{
void InteruptClass::RunStaticTest() {
	Serial.println("Consuming test fifo queue");
	Serial.println("");
	// loop will consume the interupts
}
void InteruptClass::PrintBuffer() {
	InteruptorClass* interuptor;
	if (cBuffer.isEmpty()) {
		Serial.println("empty");
	}
	else {
		Serial.print("[");
		for (decltype(cBuffer)::index_t i = 0; i <= cBuffer.size() - 1; i++) {
			interuptor = cBuffer[i];
			interuptor->printlnMe();
			//Serial.print(cBuffer[i]);
			//Serial.print(",");
		}
		

		Serial.print(cBuffer.size());
		Serial.print("/");
		Serial.print(cBuffer.size() + cBuffer.available());
		if (cBuffer.isFull()) {
			Serial.print(" full");
		}

		Serial.println(")");
	}

}
void testFunction(InteruptorClass interupt) {
	long randNumber = random(2);
	//interupt.setRepeat(randNumber = 0);
	interupt.printlnMe();
}

// Note - I'm using period to indicate expected order of popping

void InteruptClass::BuildStaticTest() {
	int order = 0;
	Serial.println("Building test fifo queue");
	Serial.println("");
	InteruptorClass* inter1 = new InteruptorClass 
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckInTemp, 2);
	InteruptClass::fifoPush(inter1);
	InteruptClass::PrintBuffer(); // inter1->printlnMe();

	InteruptorClass* inter2 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckMinSensors, 3);
	InteruptClass::fifoPush(inter2);
	InteruptClass::PrintBuffer(); // inter2->printlnMe();

	InteruptorClass* inter3 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::CheckSapLines, 4);
	InteruptClass::fifoPush(inter3);
	InteruptClass::PrintBuffer(); // inter3->printlnMe();

	InteruptorClass* inter4 = new InteruptorClass
	(testFunction, EnumsClass::LifoPush,EnumsClass::CheckSapFloat, 1);
	InteruptClass::lifoPush(inter4);
	InteruptClass::PrintBuffer(); // inter4->printlnMe();

	InteruptorClass* inter5 = new InteruptorClass
	(testFunction, EnumsClass::FifoPush,EnumsClass::Void, 5);
	InteruptClass::fifoPush(inter5);
	InteruptClass::PrintBuffer(); // inter5->printlnMe();
	Serial.print("Buffer Count - ");
	Serial.println(cBuffer.size()); 
}

InteruptClass Interrupt;

