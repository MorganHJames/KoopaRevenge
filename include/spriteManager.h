//\===========================================================================================
//\ File: spriteManager.h
//\ Author: Morgan James
//\ Date Created: 11/12/2017
//\ Brief: A class containing a variable and function to keep track of how many objects are in the OAM.
//\===========================================================================================

#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "gba_graphics.h"

class SpriteManager//A class that controls the active sprites in OAM.
{
private:
public:
	s32 s32ActivatedSpriteAttributes;//How many active sprites in OAM.

	void SpriteManagerInitialization()//Initializes the active sprites variable.
	{
		s32ActivatedSpriteAttributes = -1;//Sets the active sprites to -1 as when you first call the function it will increase it to 0.
	}

	s32 ObjectAttributeMemoryFree()//Returns the OAM position of the first free address.
	{
		s32ActivatedSpriteAttributes++;//Increases the amount of active sprites.
		return s32ActivatedSpriteAttributes;//Returns the OAM position of the first free address. 
	}
};

#endif//__SPRITE_H__