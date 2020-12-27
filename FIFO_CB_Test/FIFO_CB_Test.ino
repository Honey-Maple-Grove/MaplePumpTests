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
#include <stdio.h>
#include "Interupt.h"

void loop() {
    // keeps trying
    if (InteruptClass::hasInterupts) {
        Serial.print("Consume Buffer Count - ");
        Serial.println(InteruptClass::interuptCount());
        InteruptClass::runNextInterupt();
    }
}

void setup() {
  //Open serial port at 115200 baud
  Serial.begin(115200);

  //Wait until the serial port has opened
  while (!Serial) delay(1);
  Serial.println("Test Started");
  //Wait a little bit to make sure we don't get any garbage on the serial monitor
  delay(100);
  InteruptClass::init(); // does nothing until timers are implemented
  InteruptClass::BuildStaticTest();
  InteruptClass::RunStaticTest();
}
