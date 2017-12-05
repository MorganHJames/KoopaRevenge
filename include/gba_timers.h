//\===========================================================================================
//\ File: gba_timers.h
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: 
//\===========================================================================================

#ifndef _GBA_TIMERS_H_
#define _GBA_TIMERS_H_

#include "gba_types.h"

	//Timer data address pointers.
#define TIMER_0_DATA	*((vu16*)(0x04000100))
#define TIMER_1_DATA	*((vu16*)(0x04000104))
#define TIMER_2_DATA	*((vu16*)(0x04000108))
#define TIMER_3_DATA	*((vu16*)(0x0400010C))

//Timer control address pointers.
#define TIMER_0_CONTROL *((vu16*)(0x04000102))
#define TIMER_1_CONTROL *((vu16*)(0x04000106))
#define TIMER_2_CONTROL *((vu16*)(0x0400010A))
#define TIMER_3_CONTROL *((vu16*)(0x0400010E))

//Defines for timer frequencies.
#define TIMER_FREQUENCY_1	 0x0//1 cycle/tick.
#define TIMER_FREQUENCY_64	 0x0001//64 cycle/tick.
#define TIMER_FREQUENCY_256	 0x0002//256 cycle/tick.
#define TIMER_FREQUENCY_1024 0x0003//1024 cycle/tick.

//Turn on cascading mode = pauses a timer without disabling it as it won't overflow in this mode.
#define TIMER_CASCADE		 0x0004

//Enabling and disabling timers completely.
#define TIMER_ENABLE         0x0080

//Enable timer IRQ.
#define TIMER_IRQ            0x0040

//Timing defines.
#define TIMER_SECONED (u16)-0x2025//About one second.
#define TIMER_MILLISECOND (u16)-0x0008//About one eighth of a millisecond.

//Timer functions.
extern void timerEnable(u16* a_timerControl);
extern void timerDisable(u16* a_timerControl);
extern void timerPause(u16* a_timerControl);
extern void timerUnpause(u16* a_timerControl);
extern void Delay(u16 a_timeScale);
extern void stopDelay();
extern void sleep(u32 a_amount, u16 a_timeScale);

#endif // _GBA_TIMERS_H_