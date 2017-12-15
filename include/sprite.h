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

/* there are 128 sprites on the GBA */
#define NUM_SPRITES 128

/* setup all sprites */
void SetupSprites()
{
	ObjectAttributeMemoryInitialize(MEMORY_OBJECT_ATTRIBUTE_MEMORY, NUMBER_SPRITES);
}

//* a sprite is a moveable image on the screen */
class Sprite 
{
private:
public:
	union
	{
		ObjectAttribute* poAttribute;
		ObjectAffine* poAffine;
	};

	/* set a sprite postion */
	void SpriteSetPosition(s32 a_s32X, s32 a_s32Y)
	{
		SetObjectPosition(poAttribute, a_s32X, a_s32Y);
	}

	/* move a sprite in a direction */
	void SpriteMove(s32 a_s32DirectionX, s32 a_s32DirectionY)
	{
		/* get the current y coordinate */
		s32 s32Y = poAttribute->u16Attribute0 & 0xff;

		/* get the current x coordinate */
		s32 s32X = poAttribute->u16Attribute1 & 0x1ff;

		/* move to the new location */
		SpriteSetPosition(s32X + a_s32DirectionX, s32Y + a_s32DirectionY);
	}

	/* change the vertical flip flag */
	void SpriteSetVerticalFlip(u8 a_u8VerticalFlip)
	{
		if (a_u8VerticalFlip)
		{
			/* set the bit */
			poAttribute->u16Attribute1 |= 0x2000;
		}
		else
		{
			/* clear the bit */
			poAttribute->u16Attribute1 &= 0xdfff;
		}
	}

	/* change the vertical flip flag */
	void SpriteSetHorizontalFlip(u8 a_u8HorizontalFlip)
	{
		if (a_u8HorizontalFlip)
		{
			/* set the bit */
			poAttribute->u16Attribute1 |= 0x1000;
		}
		else
		{
			/* clear the bit */
			poAttribute->u16Attribute1 &= 0xefff;
		}
	}

	/* change the tile offset of a sprite */
	void SpriteSetOffset(s32 a_s32Offset)
	{
		/* clear the old offset */
		poAttribute->u16Attribute2 &= 0xfc00;

		/* apply the new one */
		poAttribute->u16Attribute2 |= (a_s32Offset & 0x03ff);
	}

	void HideSprite()
	{
		ObjectHide(poAttribute);
	}

	void UnHideSprite(u8 a_u8Mode)
	{
		ObjectUnhide(poAttribute, a_u8Mode);
	}
};

#endif//__SPRITE_H__