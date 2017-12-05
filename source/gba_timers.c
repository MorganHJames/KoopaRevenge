//\===========================================================================================
//\ File: gba_timers.c
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: Contains the function information for the prototypes contained in gba_timers.h.
//\===========================================================================================

#include "gba_timers.h"

void timerEnable(u16* a_timerControl)
{
	*a_timerControl |= TIMER_ENABLE;
}

void timerDisable(u16* a_timerControl)
{
	*a_timerControl ^= TIMER_ENABLE;
}

void timerPause(u16* a_timerControl)
{
	*a_timerControl |= TIMER_CASCADE;
}

void timerUnpause(u16* a_timerControl)
{
	*a_timerControl ^= TIMER_CASCADE;
}

void Delay(u16 a_timeScale)
{
	TIMER_0_DATA = 0;	TIMER_0_CONTROL = 0;
	TIMER_1_DATA = 0;	TIMER_1_CONTROL = 0;

	TIMER_0_DATA = a_timeScale;
	TIMER_0_CONTROL = TIMER_ENABLE | TIMER_FREQUENCY_1024;

	TIMER_1_CONTROL = TIMER_ENABLE | TIMER_CASCADE;
}

void stopDelay()
{
	timerDisable(TIMER_0_CONTROL);
	timerDisable(TIMER_1_CONTROL);
}

void sleep(u32 a_amount, u16 a_timeScale)
{
	TIMER_2_DATA = 0;	TIMER_2_CONTROL = 0;
	TIMER_3_DATA = 0;	TIMER_3_CONTROL = 0;

	TIMER_2_DATA = a_timeScale;
	TIMER_2_CONTROL = TIMER_ENABLE | TIMER_FREQUENCY_1024;
	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;

	while (1)
	{
		if (TIMER_3_DATA > a_amount)
			return;
	}
}