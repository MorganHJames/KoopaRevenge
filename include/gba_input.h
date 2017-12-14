//\===========================================================================================
//\ File: gba_input.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Outlines the registers for GBA Key Input and provides functionality for handling key presses.
//\===========================================================================================

#include "gba_registry.h"
#include "gba_types.h"

#ifndef __GBA_INPUT_H__
#define __GBA_INPUT_H__

//\===========================================================================================
//\ Key Registry Defines
//\===========================================================================================

#define REGISTRY_KEY_INPUT	 *(vu16*)(REGISTRY_BASE + 0x130)//Define for Hardware Key Input Register.

#define REGISTRY_KEY_CONTROL *(vu16*)(REGISTRY_BASE + 0x132)//Define for Hardware Key Interrupt Control Register.

//\===========================================================================================
//\ Key Enumerations
//\===========================================================================================

typedef enum KEYS//An enumeration for all GBA keys and inputs.
{
	A = (1 << 0),				 //Button A.
	B = (1 << 1),				 //Button B.
	SELECT = (1 << 2),			 //Select button.
	START = (1 << 3),			 //Start button.
	RIGHT = (1 << 4),			 //Right D-pad.
	LEFT = (1 << 5),			 //Left D-pad.
	UP = (1 << 6),				 //Up D-pad.
	DOWN = (1 << 7),			 //Down D-pad.
	R = (1 << 8),				 //Shoulder R.
	L = (1 << 9),				 //Shoulder L.
	SHOULDER = (1 << 10),		 //L or R.
	ANY = 0x03FF,				 //any key.
	ANYDPAD = 0x00F0,			 //any D-pad.
	ACCEPT = 0x0009,			 //A or start.
	CANCEL = 0x0002,			 //B (well, it usually is).
	RESET = 0x000F,				 //St+Se+A+B.
	KEYIRQ_ENABLE = (1 << 14),	 //Enable keypad interrupt.
	KEYIRQ_OR = (0 << 15),		 //interrupt logical OR mode. 
	KEYIRQ_AND = (1 << 15),		 //interrupt logical AND mode. 
}KEYS;

//\===========================================================================================
//\ Functions For Keys
//\===========================================================================================

#define KEY_MASK 0x03FF//Define for the key mask.

extern u16 u16CurrentKeys, u16PreviousKeys;//Variables to hold the current and previous state of the hardware keys.

extern void PollKeys();//Function to test for Hardware Key Depress.

extern u16	CurrentKeyState();				//Get current key state.
extern u16	PreviousKeyState();				//Get previous key state.
extern u32	KeyDown(u32 a_u32Key);			//Gives the keys of \a key that are currently down. 
extern u32	KeyUp(u32 a_u32Key);			//Gives the keys of \a key that are currently up. 
extern u32	KeyHeld(u32 a_u32Key);			//Gives the keys of \a key that are pressed. 
extern u32	KeyReleased(u32 a_u32Key);		//Gives the keys of \a key that are released.  
extern u32	KeyHit(u32 a_u32Key);			//Gives the keys of \a key that are hit. 
extern u32	KeyStateChange(u32 a_u32Key);	//Gives the keys of \a key that are changed. 

typedef enum AXIS//An enumeration for the axis'.
{
	HORIZONTAL = 0,//The horizontal axis.
	VERTICAL,//The vertical axis.
}AXIS;

extern s32 GetAxis(AXIS a_u32Val);//A function to get the axis.

#endif//__GBA_INPUT_H__