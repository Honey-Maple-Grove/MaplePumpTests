/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Daniel Eisterhold
 * Copyright (c) 2020 Abbott Fleur - Upgraded byte -> callback
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

#include "FIFO_CB.h"

FIFO_CB::FIFO_CB() {
  head = 0;
  tail = 0;
  numElements = 0;
}

FIFO_CB::~FIFO_CB() {
}

void FIFO_CB::push(void (*callBack)()) {
  if(numElements == FIFO_CB_SIZE) {
//    Serial.println(F("Buffer full"));
    return;
  }
  else {
    //Increment size
    numElements++;

    //Only move the tail if there is more than one element
    if(numElements > 1) {
      //Increment tail location
      tail++;

      //Make sure tail is within the bounds of the array
      tail %= FIFO_CB_SIZE;
    }
  
    //Store data into array
    buffer[tail] = callBack;
  }
}

function_pointer FIFO_CB::pop() {
  if(numElements == 0) {
//    Serial.println(F("Buffer empty"));
    return 0;
  }
  else {
    //Decrement size
    numElements--;

    function_pointer data = buffer[head];

    if(numElements >= 1) {
      //Move head up one position
      head++;

      //Make sure head is within the bounds of the array
      head %= FIFO_CB_SIZE;
    }

    return data;
  }
}

int FIFO_CB::size() {
  return numElements;
}

