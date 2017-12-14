//\===========================================================================================
//\ File: gba_timers.c
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: Contains the function information for the prototypes contained in gba_timers.h.
//\===========================================================================================

#include "gba_timers.h"

void TimerEnable(u16 a_u16TimerControl)
{
	a_u16TimerControl |= TIMER_ENABLE;
}

void TimerDisable(u16 a_u16TimerControl)
{
	a_u16TimerControl ^= TIMER_ENABLE;
}

void TimerPause(u16 a_u16TimerControl)
{
	a_u16TimerControl |= TIMER_CASCADE;
}

void TimerUnpause(u16 a_u16TimerControl)
{
	a_u16TimerControl ^= TIMER_CASCADE;
}

void Delay(u16 a_u16TimeScale)
{
	TIMER_0_DATA = 0;	TIMER_0_CONTROL = 0;
	TIMER_1_DATA = 0;	TIMER_1_CONTROL = 0;

	TIMER_0_DATA = a_u16TimeScale;
	TIMER_0_CONTROL = TIMER_ENABLE | TIMER_FREQUENCY_1024;

	TIMER_1_CONTROL = TIMER_ENABLE | TIMER_CASCADE;
}

void StopDelay()
{
	TimerDisable(TIMER_0_CONTROL);
	TimerDisable(TIMER_1_CONTROL);
}

void Sleep(u32 a_u32Amount, u16 a_u16TimeScale)
{
	TIMER_2_DATA = 0;	TIMER_2_CONTROL = 0;
	TIMER_3_DATA = 0;	TIMER_3_CONTROL = 0;

	TIMER_2_DATA = a_u16TimeScale;
	TIMER_2_CONTROL = TIMER_ENABLE | TIMER_FREQUENCY_1024;
	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;

	while (1)
	{
		if (TIMER_3_DATA > a_u32Amount)
			return;
	}
}