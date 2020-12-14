/*
 * FIFO Buffer Test Program
 * Pushes then pops items onto FIFO buffer.
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Daniel Eisterhold
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Interrupts.h"
#include <stdio.h>
#include "InteruptBuffer.h"
#include "CallbackF1.h"
typedef void (* myFunctionPointer);
char tstMessage[30];
function_pointer fp;
void run(){

}
void AddToFIFO() {

    Serial.println("Pushing F1");
    myFunctionPointer fPointer = run;
    Serial.println(InteruptBufferClass::size());
    InteruptBufferClass::push(fp);
    delay(100);
    Serial.println("Pushing CB_2");
    InteruptBufferClass::push(CB_2);
    delay(100);
    Serial.println(InteruptBufferClass::size());
    Serial.println("Pushing Priority1");
	//Serial.print("Head=");
	//Serial.println(myBuffer.headptr());
	//Serial.print("Tail=");
	//Serial.println(myBuffer.tailptr());
    Serial.println(InteruptBufferClass::size());
    InteruptBufferClass::pushhead(Priority1);
	//Serial.print("Head=");
	//Serial.println(myBuffer.headptr());
	//Serial.print("Tail=");
	//Serial.println(myBuffer.tailptr());
    delay(100);
    Serial.println(InteruptBufferClass::size());
    Serial.println("Pushing Priority2");
    InteruptBufferClass::pushhead(Priority2);
	//Serial.print("Head=");
	//Serial.println(myBuffer.headptr());
	//Serial.print("Tail=");
	//Serial.println(myBuffer.tailptr());
    delay(100);
    Serial.println(InteruptBufferClass::size());
    Serial.println("Pushing CB_6");
    InteruptBufferClass::push(CB_6);
	//Serial.print("Head=");
	//Serial.println(myBuffer.headptr());
	//Serial.print("Tail=");
	//Serial.println(myBuffer.tailptr());
    Serial.println(InteruptBufferClass::size());
    delay(100);
}

void EmptyFIFO() {

    //Pop items off the FIFO buffer until it's empty
    while (InteruptBufferClass::size() > 0) {
        Serial.println(InteruptBufferClass::size());
        InteruptBufferClass::pop()();
        delay(100);
    }

    while (1);
}
void loop() {
 
}

void CB_1() {
    Serial.println("CB1 called");
}

void CB_2() {
    Serial.println("CB2 called");
}

void CB_3() {
    Serial.println("CB3 called");
}
void Priority1() {
    Serial.println("Priority1 called");
}

void Priority2() {
    Serial.println("Priority2 called");
}

void CB_6() {
    Serial.println("CB6 called");
}
void setup() {
  //Open serial port at 115200 baud
  Serial.begin(115200);

  //Wait until the serial port has opened
  while (!Serial) delay(1);
  Serial.println("Test Started");
  //Wait a little bit to make sure we don't get any garbage on the serial monitor
  delay(100);

  AddToFIFO();
  EmptyFIFO();
}
