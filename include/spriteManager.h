//\===========================================================================================
//\ File: spriteManager.h
//\ Author: Morgan James
//\ Date Created: 11/12/2017
//\ Brief: A class containing a variable and function to keep track of how many objects are in the OAM.
//\===========================================================================================

#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "gba_graphics.h"

class SpriteManager
{
private:
public:
	s32 s32ActivatedSpriteAttributes;

	void SpriteManagerInitialization()
	{
		s32ActivatedSpriteAttributes = -1;
	}

	//Check oam pos for usage
	s32 ObjectAttributeMemoryFree()
	{
		s32ActivatedSpriteAttributes = s32ActivatedSpriteAttributes + 1;
		return s32ActivatedSpriteAttributes;
	}
};

#endif//__SPRITE_H__