/*
Name:		Lights.ino
Created:	1/16/2016 8:48:17 AM
Part of Visual Micro's Extended Debugging Tutorial
see http://www.visualmicro.com/page/User-Guide.aspx?doc=gdb-Tutorial-1
Author:	Heinz Kessler, Visual Micro Ltd.
(c) 2016 Visual Micro Ltd., all rights reserved
*/

// This source file contains all functions related to "lights"

// switch optimization off for this file
#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

#include "lights.h"

// Initialize light
void InitLight(int lightIndex, LampState *lamp, int pinRed, int pinYellow, int pinGreen)
{
	LightState *light = &lights[lightIndex];

	// set initial lamp state
	light->lampState = lamp;

	// assign pins
	light->lampPins[0] = pinRed;
	light->lampPins[1] = pinYellow;
	light->lampPins[2] = pinGreen;

	light->millisLeft = light->lampState->duration;

	SetLightSignals(lightIndex);
};


// If the duration of one state is reached, step to the next state in the list
void SetNewState(int lightIndex)
{
	int delayTime = 100;
	char *activeLamp = "yellow";

	LightState *light = &lights[lightIndex];

	light->lampState++;

	// end of list reached?
	if (light->lampState->duration == 0)	// indicates end of list, restart from beginning
	{
		// go back to top
		light->lampState = States;
	}

	// set remaining time to full duration
	light->millisLeft = light->lampState->duration;

	// set outputs
	SetLightSignals(lightIndex);
}


// Sets the digital output pins according to the light pattern in a given state
void SetLightSignals(int lightIndex)
{
	LightState *light = &lights[lightIndex];

	digitalWrite(light->lampPins[0], (light->lampState->lampSignals & RED_ON) ? HIGH : LOW);
	digitalWrite(light->lampPins[1], (light->lampState->lampSignals & YELLOW_ON) ? HIGH : LOW);
	digitalWrite(light->lampPins[2], (light->lampState->lampSignals & GREEN_ON) ? HIGH : LOW);
}
