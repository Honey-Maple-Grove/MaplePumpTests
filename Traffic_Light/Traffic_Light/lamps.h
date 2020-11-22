#ifndef LAMPS_H_INCLUDED
#define LAMPS_H_INCLUDED

// bits indicating light is on
#define RED_ON 1
#define YELLOW_ON 2
#define GREEN_ON 4

// marker in the lamp state light where traffic lights 2 shall start off
#define START2_HERE 0x80

// The structure containing lamp states
// During operation, the two traffic lights step from one state to the next
struct LampState
{
	int lampSignals;	// defines which lamps are on in this state
	unsigned duration;	// defines the duration of this phase in ms
};


// The list of lamp states
// During operation, the two traffic lights step from one state to the next and return to the top when reaching the end of the list
LampState States[] =
{
	{ RED_ON, 3800 },
	{ RED_ON | START2_HERE, 600 },
#if GERMAN_TYPE
	// only for german traffic lights
	{ RED_ON | YELLOW_ON, 600 },
#endif
	{ GREEN_ON, 1600 },
	{ YELLOW_ON, 600 },
	{ 0, 0 }	// indicates the end of the list
};


LampState* FindStartState2();


#endif


