//\===========================================================================================
//\ File: spriteManager.h
//\ Author: Morgan James
//\ Date Created: 11/12/2017
//\ Brief:
//\===========================================================================================

#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "gba_graphics.h"

class SpriteManager
{
private:
public:
	int activatedSpriteAttributes = -1;

	//Check oam pos for usage
	int objectAttributeMemoryFree()
	{
		activatedSpriteAttributes = activatedSpriteAttributes + 1;
		return activatedSpriteAttributes;
	}

};

#endif//__SPRITE_H__