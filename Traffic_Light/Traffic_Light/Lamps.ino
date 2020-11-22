/*
Name:		Lamps.ino
Created:	1/16/2016 8:48:17 AM
Part of Visual Micro's Extended Debugging Tutorial
see http://www.visualmicro.com/page/User-Guide.aspx?doc=gdb-Tutorial-1
Author:	Heinz Kessler, Visual Micro Ltd.
(c) 2016 Visual Micro Ltd., all rights reserved
*/

// This source file contains all functions related to "lamps"

// switch optimization off for this file
#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

#include "lamps.h"

// Find the initial state for light 2
LampState* FindStartState2()
{
	for (LampState* l = States; l->duration > 0; ++l)
	{
		if (l->lampSignals & START2_HERE)
		{
			return l;
		}
	}
}
