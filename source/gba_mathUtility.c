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

s32 __quasiRandom_seed = 42;//The seed that the quasi random functions will use. 

s32 seedQuasiRandom(s32 a_s32Value)//A function to change the seed of the quasi random number generators.
{
	s32 old = __quasiRandom_seed;//Creates a variable called old equal to the old seed.
	__quasiRandom_seed = a_s32Value;//Sets the seed equal to the value passed in.
	return old;//Returns the old seed.
}

s32 quasiRandom()//Returns a quasi random s32.
{
	__quasiRandom_seed = 1664525 * __quasiRandom_seed + 1013904223;//Multiplies the seed by a certain large number and adds another certain large number.
	return (__quasiRandom_seed >> 16) & 0x7FFF;//Returns the seed shifted down 16 and &ed with 0x7FFF which should produce a semi random number.
}

int quasiRandomRange(s32 a_s32Min, s32 a_s32Max)//Returns a quasi random s32 between the min and max arguments.
{
	return (quasiRandom()*(a_s32Max - a_s32Min) >> 15) + a_s32Min;//Returns a random value within the max and the min arguments.
}

//\===========================================================================================
//\ Utility
//\===========================================================================================

s32 sign(s32 a_s32Value)//Returns the sign of a variable.
{
	return (a_s32Value > 0) - (a_s32Value < 0);//Returns 1 if positive and -1 if negative and 0 if neither.
}

s32 absolute(s32 a_s32Value)//Returns the absolute value of a variable with regards to having no sign (-3 = 3 && 3 = 3).
{
	s32 mask = a_s32Value >> 31;//Sets the mask by shifting down the argument by 31.
	return (a_s32Value ^ mask) - mask;//Returns the number but without the sign ( - or + ).
}

void delay(unsigned int a_amount)
{
	for (int i = 0; i < a_amount * 10; ++i);
}