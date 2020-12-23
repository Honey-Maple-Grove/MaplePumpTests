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
#include <CircularBuffer.h>
#include <stdio.h>
#include "DefinedValues.h"
#include "Enums.h"
#include "InteruptBuffer.h"
#include "Interuptor.h"
#include "Interupt.h"
char tstMessage[30];
void run(){

}
void AddToFIFO() {
    String forPrint;
    Serial.println();
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckInTemp);
    Serial.println(forPrint);
    InteruptorClass I1; I1.init(CB_1, Mills_Sec,0,EnumsClass::CheckInTemp);
    InteruptClass::push(I1);
    delay(100);
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckMinSensors);
    Serial.println(forPrint);
    InteruptorClass I2; I2.init(CB_2, Mills_Sec,0,EnumsClass::CheckMinSensors);
    InteruptClass::push(I2);
    delay(100);
    Serial.println(InteruptClass::interuptCount());
    
    forPrint = "Priority1 " + EnumsClass::EnumStr(EnumsClass::CheckSapLines);
    Serial.println(forPrint);
    InteruptorClass P1; P1.init(Priority1, Mills_Sec,0,EnumsClass::CheckMinSensors);
    InteruptClass::push(P1);
    Serial.println(InteruptClass::interuptCount());
    delay(100);
    forPrint = "Priority2 " + EnumsClass::EnumStr(EnumsClass::Void);
    Serial.println(forPrint);
    InteruptorClass P2; P2.init(Priority2, Mills_Sec,0,EnumsClass::CheckMinSensors);
    InteruptClass::push(P2);
    Serial.println(InteruptClass::interuptCount());
    delay(100);
    Serial.println(InteruptClass::interuptCount());
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckSapFloat);
    Serial.println(forPrint);
    InteruptorClass I3; I3.init(CB_3, Mills_Sec,0,EnumsClass::CheckSapFloat);
    InteruptClass::push(I3);
    Serial.println(InteruptClass::interuptCount());
    delay(100);
}

void EmptyFIFO() {

    //Pop items off the FIFO buffer until it's empty
    while (InteruptClass::hasInterupts()) {
        Serial.println(InteruptBufferClass::size());
        InteruptorClass iC = InteruptBufferClass::pop();
        String msg = EnumsClass::EnumStr(iC.Interupt());
        Serial.println(msg);
        iC.runInterupt();
        delay(100);
    }

    while (1);
}

void ResetFIFO() {
    InteruptBufferClass::init();
}


void loop() {
 
}

char* charString(){
return PROMPT_TEMP;
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
