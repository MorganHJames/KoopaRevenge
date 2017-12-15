//\===========================================================================================
//\ File: gba_vector4.h
//\ Author: Morgan James
//\ Date Created: 09/12/2017
//\ Brief: A header to define a structure to hold the positional data of the sprites bounding boxes for collisions.
//\===========================================================================================

#ifndef __GBA_VECTOR4_H__
#define __GBA_VECTOR4_H__

#include "gba_math.h"

typedef struct Vector4//A structure to hold four variables. 
{
	fixed fX, fY , fW, fH;//A variable for x, y , w and  h.
}Vector4;

#endif//__GBA_VECTOR4_H__