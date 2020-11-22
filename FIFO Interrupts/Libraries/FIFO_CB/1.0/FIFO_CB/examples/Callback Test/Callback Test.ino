/*
 Name:		FIFO_CB.ino
 Created:	3/1/2020 3:44:02 PM
 Author:	Abbott
*/
/*
 * FIFO Callback Buffer Test Program
 * Pushes then pops items onto FIFO buffer.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Abbott Fleur - Modified for Caallbacks
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

FIFO_CB myBuffer;


void setup() {
    //Open serial port at 115200 baud
    Serial.begin(115200);

    //Wait until the serial port has opened
    while (!Serial) delay(1);

    //Wait a little bit to make sure we don't get any garbage on the serial monitor
    delay(100);

    AddToFIFO();
    EmptyFIFO();
}

void AddToFIFO() {
    Serial.println("Pushing CB_1");
    myBuffer.push(CB_1);
    delay(100);
    Serial.println("Pushing CB_2");
    myBuffer.push(CB_2);
    delay(100);
    Serial.println("Pushing CB_3");
    myBuffer.push(CB_3);
    delay(100);
}

void EmptyFIFO() {

    //Pop items off the FIFO buffer until it's empty
    while (myBuffer.size() > 0) {
        myBuffer.pop()();
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