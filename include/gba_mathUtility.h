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

extern s32 s32QuasiRandomSeed;//The seed that the quasi random functions will use. 
extern s32 SeedQuasiRandom(s32 a_s32Value);//A function to change the seed of the quasi random number generators.
extern s32 QuasiRandom();//Returns a quasi random s32.
extern s32 QuasiRandomRange(s32 a_s32Minimum, s32 a_s32Maximum);//Returns a quasi random s32 between the min and max arguments.

//\===========================================================================================
//\ Utility
//\===========================================================================================

extern s32 Sign(s32 a_s32Value);//Returns the sign of a variable.
extern s32 Absolute(s32 a_s32Value);//Returns the absolute value of a variable with regards to having no sign (-3 = 3 && 3 = 3).
extern void DelayNoTimer(u32 a_u32Amount);//A delay for scrolling.

#endif//__GBA_MATHUTILITY_H__
