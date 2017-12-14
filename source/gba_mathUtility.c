//\===========================================================================================
//\ File: gba_mathUtility.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_mathUtility.h.
//\===========================================================================================

#include "gba_mathUtility.h"

//\===========================================================================================
//\ Randomness functions
//\===========================================================================================

s32 s32QuasiRandomSeed = 42;//The seed that the quasi random functions will use. 

s32 SeedQuasiRandom(s32 a_s32Value)//A function to change the seed of the quasi random number generators.
{
	s32 s32Old = s32QuasiRandomSeed;//Creates a variable called old equal to the old seed.
	s32QuasiRandomSeed = a_s32Value;//Sets the seed equal to the value passed in.
	return s32Old;//Returns the old seed.
}

s32 QuasiRandom()//Returns a quasi random s32.
{
	s32QuasiRandomSeed = 1664525 * s32QuasiRandomSeed + 1013904223;//Multiplies the seed by a certain large number and adds another certain large number.
	return (s32QuasiRandomSeed >> 16) & 0x7FFF;//Returns the seed shifted down 16 and &ed with 0x7FFF which should produce a semi random number.
}

int QuasiRandomRange(s32 a_s32Minimum, s32 a_s32Maximum)//Returns a quasi random s32 between the min and max arguments.
{
	return (QuasiRandom()*(a_s32Maximum - a_s32Minimum) >> 15) + a_s32Minimum;//Returns a random value within the max and the min arguments.
}

//\===========================================================================================
//\ Utility
//\===========================================================================================

s32 Sign(s32 a_s32Value)//Returns the sign of a variable.
{
	return (a_s32Value > 0) - (a_s32Value < 0);//Returns 1 if positive and -1 if negative and 0 if neither.
}

s32 Absolute(s32 a_s32Value)//Returns the absolute value of a variable with regards to having no sign (-3 = 3 && 3 = 3).
{
	s32 s32Mask = a_s32Value >> 31;//Sets the mask by shifting down the argument by 31.
	return (a_s32Value ^ s32Mask) - s32Mask;//Returns the number but without the sign ( - or + ).
}

void DelayNoTimer(u32 a_u32Amount)
{
	for (u32 u32I = 0; u32I < a_u32Amount * 10; ++u32I);
}