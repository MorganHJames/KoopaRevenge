//\===========================================================================================
//\ File: gba_timers.h
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: Defines and functions for tracking time passage and stalling the game.
//\===========================================================================================

#ifndef _GBA_TIMERS_H_
#define _GBA_TIMERS_H_

#include "gba_types.h"

// --- Timer data address pointers ---
#define TIMER_0_DATA	*((vu16*)(0x04000100))
#define TIMER_1_DATA	*((vu16*)(0x04000104))
#define TIMER_2_DATA	*((vu16*)(0x04000108))
#define TIMER_3_DATA	*((vu16*)(0x0400010C))

//Timer control address pointers.
#define TIMER_0_CONTROL *((vu16*)(0x04000102))
#define TIMER_1_CONTROL *((vu16*)(0x04000106))
#define TIMER_2_CONTROL *((vu16*)(0x0400010A))
#define TIMER_3_CONTROL *((vu16*)(0x0400010E))

// --- Defines for timer frequencies ---
#define TIMER_FREQUENCY_1	 0x0//1 cycle/tick.
#define TIMER_FREQUENCY_64	 0x0001//64 cycle/tick.
#define TIMER_FREQUENCY_256	 0x0002//256 cycle/tick.
#define TIMER_FREQUENCY_1024 0x0003//1024 cycle/tick.

#define TIMER_CASCADE		 0x0004//Turn on cascading mode = pauses a timer without disabling it as it won't overflow in this mode.

#define TIMER_ENABLE         0x0080//Enabling and disabling timers completely.

#define TIMER_IRQ            0x0040//Enable timer IRQ.

// --- Timing defines ---
#define TIMER_SECONED		(u16)-0x2025//About one second.
#define TIMER_MILLISECOND	(u16)-0x0008//About one eighth of a millisecond.

// --- Timer functions ---
extern void TimerEnable(u16 a_u16TimerControl);
extern void TimerDisable(u16 a_u16TimerControl);
extern void TimerPause(u16 a_u16TimerControl);
extern void TimerUnpause(u16 a_u16TimerControl);
extern void Delay(u16 a_u16TimeScale);
extern void StopDelay();
extern void Sleep(u32 a_u32Amount, u16 a_u16TimeScale);

#endif//_GBA_TIMERS_H_