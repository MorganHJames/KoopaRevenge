//\===========================================================================================
//\ File: sprite.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief:
//\===========================================================================================

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "gba_graphics.h"
#include "gba_vector2.h"

typedef struct Sprite//A structure for a sprite. 
{
	union
	{
		ObjectAttribute* Attribute;
		ObjectAffine* Affine;
	};
	Vector2 position;

}__attribute__((packed, aligned(4))) Sprite;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.


#endif//__SPRITE_H__