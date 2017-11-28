//\===========================================================================================
//\ File: gba_input.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the class contained in gba_input.h.
//\===========================================================================================

#include "gba_input.h"

//\===========================================================================================
//\ Functions For Keys
//\===========================================================================================

u16 __currentKeys = 0, __previousKeys = 0;//Set the extern values for key values.

void pollKeys()//Function to test for Hardware Key Depress.
{
	__previousKeys = __currentKeys;//Makes the previous keys equal to the current keys.
	__currentKeys = ~REGISTRY_KEY_INPUT & KEY_MASK;//Gets the current keys down and sets them to the current keys variable.
}

u16	currentKeyState() { return __currentKeys; }												//Get current key state.
u16	prevKeyState() { return __currentKeys; }												//Get previous key state.
u32	keyDown(u32 a_u32Key) { return __currentKeys & a_u32Key; }								//Gives the keys of \a key that are currently down. 
u32	keyUp(u32 a_u32Key) { return ~__currentKeys & a_u32Key; }								//Gives the keys of \a key that are currently up. 
u32	keyHeld(u32 a_u32Key) { return (__currentKeys & __previousKeys) & a_u32Key; }			//Gives the keys of \a key that are pressed. 
u32	keyReleased(u32 a_u32Key) { return (~__currentKeys & __previousKeys) & a_u32Key; }		//Gives the keys of \a key that are released.  
u32	keyHit(u32 a_u32Key) { return (__currentKeys & ~__previousKeys) & a_u32Key; }			//Gives the keys of \a key that are hit. 
u32	keyStateChange(u32 a_u32Key) { return (__currentKeys ^ __previousKeys) & a_u32Key; }	//Gives the keys of \a key that are changed. 

s32 getAxis(AXIS a_AVal)//A function to get the axis.
{
	switch (a_AVal)//A switch for the value passed in.
	{
	case HORIZONTAL://If the argument is horizontal.
		return ((__currentKeys >> 4) & 1) - ((__currentKeys >> 5) & 1);//Shift __currentKeys down 4 to move the value for RIGHT to the lowest bit & with 1 do the same for LEFT and subtract if right is pressed the equation becomes 1 - 0 = 1, if Left is pressed then 0 - 1 = -1.
	case VERTICAL://If the argument is vertical.
		return ((__currentKeys >> 6) & 1) - ((__currentKeys >> 7) & 1);//This is the same logic as above however uses UP and DOWN.
	default://If there no matching arguments.
		return 0;//Returns 0 if no case.
	}
}