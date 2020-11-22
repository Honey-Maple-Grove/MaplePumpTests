/*
Name:		Traffic_Light.ino
Created:	1/16/2016 8:48:17 AM
Part of Visual Micro's Extended Debugging Tutorial
see http://www.visualmicro.com/page/User-Guide.aspx?doc=gdb-Tutorial-1
Author:	Heinz Kessler, Visual Micro Ltd.
(c) 2016 Visual Micro Ltd., all rights reserved
*/


// switch optimization off for this file
#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

// Pin assignments for traffic light 1
#include <avr8-stub.h>
#include <app_api.h>
#define PIN_RED1 5
#define PIN_YELLOW1 6
#define PIN_GREEN1 7

// Pin assignments for traffic light 2
#define PIN_RED2 8
#define PIN_YELLOW2 9
#define PIN_GREEN2 10

// These constants are only used to make the code more 	self-explanatory
#define LIGHT1 0
#define LIGHT2 1

// traffic ´lights in German style with a red+yellow phase between red and green
#define GERMAN_TYPE 0

// delay after one loop iteration (in ms), can be chosen freely as long as it's not too short
#define LOOP_TIME 200

#include "lights.h"
#include "lamps.h"


// state structures for traffic lights 1 and 2
LightState lights[2];


// the setup function runs once when you press reset or power the board
void setup()
{
	debug_init();
	// digital output pin setup
	pinMode(PIN_RED1, OUTPUT);
	pinMode(PIN_YELLOW1, OUTPUT);
	pinMode(PIN_GREEN1, OUTPUT);

	pinMode(PIN_RED2, OUTPUT);
	pinMode(PIN_YELLOW2, OUTPUT);
	pinMode(PIN_GREEN2, OUTPUT);

	// Initialize lights and set them into the proper state

	// Light 1 starts at the beginning of the list
	InitLight(LIGHT1, States, PIN_RED1, PIN_YELLOW1, PIN_GREEN1);

	// Light 2 starts further down the list (where the START2_HERE marker is)
	InitLight(LIGHT2, FindStartState2(), PIN_RED2, PIN_YELLOW2, PIN_GREEN2);
}



// the loop function runs over and over again until power down or reset
void loop()
{
	// Handle lights
	ProcessLight(LIGHT1);
	ProcessLight(LIGHT2);

	// loop delay
	delay(LOOP_TIME);
}

void ProcessLight(int lightIndex)
{
	LightState *light = &lights[lightIndex];

	light->millisLeft -= LOOP_TIME;

	if (light->millisLeft < 0)
	{
		SetNewState(lightIndex);
	}
}
