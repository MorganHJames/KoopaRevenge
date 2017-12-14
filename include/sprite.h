//\===========================================================================================
//\ File: sprite.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief:
//\===========================================================================================

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "gba_graphics.h"
#include "gba_directMemoryAccesss.h"

/* there are 128 sprites on the GBA */
#define NUM_SPRITES 128

/* setup all sprites */
void setupSprites()
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
		ObjectAttribute* Attribute;
		ObjectAffine* Affine;
	};

	/* set a sprite postion */
	void spriteSetPosition(int x, int y)
	{
		SetObjectPosition(Attribute, x, y);
	}

	/* move a sprite in a direction */
	void spriteMove(int dx, int dy)
	{
		/* get the current y coordinate */
		int y = Attribute->u16Attribute0 & 0xff;

		/* get the current x coordinate */
		int x = Attribute->u16Attribute1 & 0x1ff;

		/* move to the new location */
		spriteSetPosition(x + dx, y + dy);
	}

	/* change the vertical flip flag */
	void spriteSetVerticalFlip(int vertical_flip)
	{
		if (vertical_flip)
		{
			/* set the bit */
			Attribute->u16Attribute1 |= 0x2000;
		}
		else
		{
			/* clear the bit */
			Attribute->u16Attribute1 &= 0xdfff;
		}
	}

	/* change the vertical flip flag */
	void spriteSetHorizontalFlip(int horizontal_flip)
	{
		if (horizontal_flip)
		{
			/* set the bit */
			Attribute->u16Attribute1 |= 0x1000;
		}
		else
		{
			/* clear the bit */
			Attribute->u16Attribute1 &= 0xefff;
		}
	}

	/* change the tile offset of a sprite */
	void spriteSetOffset(int offset)
	{
		/* clear the old offset */
		Attribute->u16Attribute2 &= 0xfc00;

		/* apply the new one */
		Attribute->u16Attribute2 |= (offset & 0x03ff);
	}

	void hideSprite()
	{
		ObjectHide(Attribute);
	}

	void unHideSprite(int a_mode)
	{
		ObjectUnhide(Attribute, a_mode);
	}
};

#endif//__SPRITE_H__