//\===========================================================================================
//\ File: gba_input.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_input.h.
//\===========================================================================================

#include "gba_input.h"

//\===========================================================================================
//\ Functions For Keys
//\===========================================================================================

u16 u16CurrentKeys = 0, u16PreviousKeys = 0;//Set the extern values for key values.

void PollKeys()//Function to test for Hardware Key Depress.
{
	u16PreviousKeys = u16CurrentKeys;//Makes the previous keys equal to the current keys.
	u16CurrentKeys = ~REGISTRY_KEY_INPUT & KEY_MASK;//Gets the current keys down and sets them to the current keys variable.
}

u16	CurrentKeyState() { return u16CurrentKeys; }											//Get current key state.
u16	PreviousKeyState() { return u16CurrentKeys; }											//Get previous key state.
u32	KeyDown(u32 a_u32Key) { return u16CurrentKeys & a_u32Key; }								//Gives the keys of \a key that are currently down. 
u32	KeyUp(u32 a_u32Key) { return ~u16CurrentKeys & a_u32Key; }								//Gives the keys of \a key that are currently up. 
u32	KeyHeld(u32 a_u32Key) { return (u16CurrentKeys & u16PreviousKeys) & a_u32Key; }			//Gives the keys of \a key that are pressed. 
u32	KeyReleased(u32 a_u32Key) { return (~u16CurrentKeys & u16PreviousKeys) & a_u32Key; }	//Gives the keys of \a key that are released.  
u32	KeyHit(u32 a_u32Key) { return (u16CurrentKeys & ~u16PreviousKeys) & a_u32Key; }			//Gives the keys of \a key that are hit. 
u32	KeyStateChange(u32 a_u32Key) { return (u16CurrentKeys ^ u16PreviousKeys) & a_u32Key; }	//Gives the keys of \a key that are changed. 

s32 GetAxis(AXIS a_u32Val)//A function to get the axis.
{
	switch (a_u32Val)//A switch for the value passed in.
	{
	case HORIZONTAL://If the argument is horizontal.
		return ((u16CurrentKeys >> 4) & 1) - ((u16CurrentKeys >> 5) & 1);//Shift __currentKeys down 4 to move the value for RIGHT to the lowest bit & with 1 do the same for LEFT and subtract if right is pressed the equation becomes 1 - 0 = 1, if Left is pressed then 0 - 1 = -1.
	case VERTICAL://If the argument is vertical.
		return ((u16CurrentKeys >> 6) & 1) - ((u16CurrentKeys >> 7) & 1);//This is the same logic as above however uses UP and DOWN.
	default://If there no matching arguments.
		return 0;//Returns 0 if no case.
	}
}