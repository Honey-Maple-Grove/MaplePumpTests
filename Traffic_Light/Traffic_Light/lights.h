#ifndef LIGHTS_H_INCLUDED
#define LIGHTS_H_INCLUDED

#include "lamps.h"

// The structure containing light states
// There is one instance of this structure for every individual traffic light (having 3 lamps each)
struct LightState
{
	LampState *lampState;	// the curtrent state this light is in
	int millisLeft;			// the remaining time for the current state in ms
	int lampPins[3];		// the pin numbers assigned to the lamps of this light
};

// Function declarations
void InitLight(int lightIndex, LampState *lamp, int pinRed, int pinYellow, int pinGreen);
void SetNewState(int lightIndex);
void SetLightSignals(int lightIndex);


#endif

