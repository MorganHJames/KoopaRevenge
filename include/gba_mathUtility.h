//\===========================================================================================
//\ File: gba_mathUtility.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains common math functions for producing quasi random numbers.
//\===========================================================================================

#ifndef __GBA_MATHUTILITY_H__
#define __GBA_MATHUTILITY_H__

#include "gba_types.h"

//\===========================================================================================
//\ Randomness functions
//\===========================================================================================

extern s32 __quasiRandom_seed;//The seed that the quasi random functions will use. 
extern s32 seedQuasiRandom(s32 a_s32Value);//A function to change the seed of the quasi random number generators.
extern s32 quasiRandom();//Returns a quasi random s32.
extern int quasiRandomRange(s32 a_s32Min, s32 a_s32Max);//Returns a quasi random s32 between the min and max arguments.

//\===========================================================================================
//\ Utility
//\===========================================================================================

extern s32 sign(s32 a_s32Value);//Returns the sign of a variable.
extern s32 absolute(s32 a_s32Value);//Returns the absolute value of a variable with regards to having no sign (-3 = 3 && 3 = 3).

#endif//__GBA_MATHUTILITY_H__
