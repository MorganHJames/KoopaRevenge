//\===========================================================================================
//\ File: sprite.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief:
//\===========================================================================================

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "gba_graphics.h"
#include "gba_dma.h"

//* a sprite is a moveable image on the screen */
struct Sprite 
{
	union
	{
		ObjectAttribute* Attribute;
		ObjectAffine* Affine;
	};
};

/* there are 128 sprites on the GBA */
#define NUM_SPRITES 128
/* array of all the sprites available on the GBA */
struct Sprite sprites[NUM_SPRITES];
int next_sprite_index = 0;


/* setup all sprites */
void setupSprites()
{
	objectAttributeMemoryInitialize(MEMORY_OBJECT_ATTRIBUTE_MEMORY,NUMBER_SPRITES);
}

/* set a sprite postion */
void spriteSetPosition(struct Sprite* sprite, int x, int y)
{
	setObjectPosition(sprite->Attribute, x, y);
}

/* move a sprite in a direction */
void spriteMove(struct Sprite* sprite, int dx, int dy)
{
	/* get the current y coordinate */
	int y = sprite->Attribute->attribute0 & 0xff;

	/* get the current x coordinate */
	int x = sprite->Attribute->attribute1 & 0x1ff;

	/* move to the new location */
	spriteSetPosition(sprite, x + dx, y + dy);
}

/* change the vertical flip flag */
void spriteSetVerticalFlip(struct Sprite* sprite, int vertical_flip)
{
	if (vertical_flip)
	{
		/* set the bit */
		sprite->Attribute->attribute1 |= 0x2000;
	}
	else
	{
		/* clear the bit */
		sprite->Attribute->attribute1 &= 0xdfff;
	}
}

/* change the vertical flip flag */
void spriteSetHorizontalFlip(struct Sprite* sprite, int horizontal_flip)
{
	if (horizontal_flip)
	{
		/* set the bit */
		sprite->Attribute->attribute1 |= 0x1000;
	}
	else
	{
		/* clear the bit */
		sprite->Attribute->attribute1 &= 0xefff;
	}
}

/* change the tile offset of a sprite */
void spriteSetOffset(struct Sprite* sprite, int offset)
{
	/* clear the old offset */
	sprite->Attribute->attribute2 &= 0xfc00;

	/* apply the new one */
	sprite->Attribute->attribute2 |= (offset & 0x03ff);
}

#endif//__SPRITE_H__