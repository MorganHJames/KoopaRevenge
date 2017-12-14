//\===========================================================================================
//\ File: gba_vector2.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief: A header to define a structure to hold the positional data of the sprites.
//\===========================================================================================

#ifndef __GBA_VECTOR2_H__
#define __GBA_VECTOR2_H__

#include "gba_math.h"

typedef struct Vector2//A structure to hold two variables. 
{
	fixed fX, fY;//A variable for x and y.
}__attribute__((packed, aligned(4)))Vector2;

#endif//__GBA_VECTOR2_H__