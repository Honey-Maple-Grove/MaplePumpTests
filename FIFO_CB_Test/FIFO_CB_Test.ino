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
#include "Enms.h"
char tstMessage[30];
void run(){

}
void AddToFIFO() {
    String forPrint;
    Serial.println();
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckInTemp);
    Serial.println(forPrint);
    InterruptsClass::push(EnumsClass::CheckInTemp);
    delay(100);
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckMinSensors);
    Serial.println(forPrint);
    InterruptsClass::push(EnumsClass::CheckMinSensors);
    delay(100);
    Serial.println(InteruptBufferClass::size());
    
    forPrint = "Priority " + EnumsClass::EnumStr(EnumsClass::CheckSapLines);
    Serial.println(forPrint);
    InterruptsClass::priorty(EnumsClass::CheckSapLines);
    Serial.println(InteruptBufferClass::size());
    delay(100);
    forPrint = "Priority " + EnumsClass::EnumStr(EnumsClass::Void);
    Serial.println(forPrint);
    InterruptsClass::priorty(EnumsClass::Void);
    Serial.println(InteruptBufferClass::size());
    delay(100);
    Serial.println(InteruptBufferClass::size());
    forPrint = "Push " + EnumsClass::EnumStr(EnumsClass::CheckSapFloat);
    Serial.println(forPrint);
    InterruptsClass::push(EnumsClass::CheckSapFloat);
    Serial.println(InteruptBufferClass::size());
    delay(100);
}

void EmptyFIFO() {

    //Pop items off the FIFO buffer until it's empty
    while (InteruptBufferClass::size() > 0) {
        Serial.println(InteruptBufferClass::size());
        InterruptsClass::runFunction();
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
