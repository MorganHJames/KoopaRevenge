//\===========================================================================================
//\ File: sprite.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief: A header that contains the class declaration and prototypes for the sprite.
//\===========================================================================================

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "gba_graphics.h"
#include "gba_directMemoryAccesss.h"

#define NUM_SPRITES 128//A define for the amount of sprites that there can be.

void SetupSprites()//Sets up all sprites.
{
	ObjectAttributeMemoryInitialize(MEMORY_OBJECT_ATTRIBUTE_MEMORY, NUMBER_SPRITES);//Initializes OAM.
}

class Sprite//A class for sprites which is a moveable image on the screen.
{
private:
public:
	
	ObjectAttribute* poAttribute;//A pointer to the Object attribute.
	
	void SpriteSetPosition(s32 a_s32X, s32 a_s32Y)//Sets a sprites position
	{
		SetObjectPosition(poAttribute, a_s32X, a_s32Y);//Moves an object.
	}

	void SpriteMove(s32 a_s32DirectionX, s32 a_s32DirectionY)//Moves a sprite in a direction.
	{
		s32 s32Y = poAttribute->u16Attribute0 & 0xff;//Gets the current y coordinate.

		s32 s32X = poAttribute->u16Attribute1 & 0x1ff;//Gets the current x coordinate.

		SpriteSetPosition(s32X + a_s32DirectionX, s32Y + a_s32DirectionY);//Moves the sprite to the new location.
	}

	void SpriteSetVerticalFlip(u8 a_u8VerticalFlip)//Changes the vertical flip flag.
	{
		if (a_u8VerticalFlip)//If 1.
		{
			poAttribute->u16Attribute1 |= 0x2000;//See the bit.
		}
		else
		{
			poAttribute->u16Attribute1 &= 0xdfff;//Clear the bit.
		}
	}

	void SpriteSetHorizontalFlip(u8 a_u8HorizontalFlip)//Changes the horizontal flip flag.
	{
		if (a_u8HorizontalFlip)
		{
			poAttribute->u16Attribute1 |= 0x1000;//See the bit.
		}
		else
		{
			poAttribute->u16Attribute1 &= 0xefff;//clear the bit.
		}
	}

	void SpriteSetOffset(s32 a_s32Offset)//Change the tile offset of the sprite.
	{
		poAttribute->u16Attribute2 &= 0xfc00;//Clear the old offset.

		poAttribute->u16Attribute2 |= (a_s32Offset & 0x03ff);//Apply the new offset.
	}

	void HideSprite()//Hides a sprite in OAM.
	{
		ObjectHide(poAttribute);//Hides an object.
	}

	void UnHideSprite(u8 a_u8Mode)//Reveals a sprite in OAM.
	{
		ObjectUnhide(poAttribute, a_u8Mode);//Reveals an object.
	}
};

#endif//__SPRITE_H__