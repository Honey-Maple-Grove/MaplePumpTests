/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
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
 
#ifndef __FIFO_CB__
#define __FIFO_CB__

#include "Arduino.h"

#define FIFO_CB_SIZE 10
typedef void (*function_pointer)();

static FIFO_CB fifoQueue;

class FIFO_CB {
  private:
    int head;
    int tail;
    int numElements;
    function_pointer buffer[FIFO_CB_SIZE];
  public:
    FIFO_CB();
    ~FIFO_CB();
    void push(void (*callBack)());
    function_pointer pop();
    int size();
};

#endif
