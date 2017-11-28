//\===========================================================================================
//\ File: gba_math.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_math.h.
//\===========================================================================================

#include "gba_math.h"
#include "sinlut.h"

//\===========================================================================================
//\ Functions To Convert From Non-fixed Point Representation To Fixed Point
//\===========================================================================================

fixed	integerToFixed(s32 a_i)//Convert and integer to a fixed point representation.
{
	return a_i << FIXED_SHIFT;//Returns a fixed point representation of the integer passed in.
}

fixed	floatToFixed(float a_f)//Convert a float to a fixed point representation.	
{
	return (fixed)(a_f*FIXED_SCALE_FLOAT);//Returns a fixed point representation of the float passed in.
}

//\===========================================================================================
//\ Functions To Convert From Fixed Point Representation To Non-fixed Point Representation
//\===========================================================================================

u32		fixedToUnsignedInteger(fixed a_f)//Convert a fixed point value into a unsigned integer value.
{
	return a_f >> FIXED_SHIFT;//Returns a unsigned integer from a fixed point argument.
}

u32		fixedToUnsignedFractionalComponent(fixed a_f)//Get only the fractional component of a fixed point value as an integer.
{
	return a_f & FIXED_MASK;//Returns the fractional component of the fixed point argument.
}

s32		fixedToInteger(fixed a_f)//Convert a fixed point number into a signed integer.
{
	return a_f / FIXED_SCALE;//Returns a signed integer from a fixed point argument.
}

float	fixedToFloat(fixed a_f)//Convert a fixed point number into a float.
{
	return a_f / FIXED_SCALE_FLOAT;//Returns a float representation from a fixed point argument.
}

//\===========================================================================================
//\ Functions To Undertake Fixed Point Addition, Subtraction, Multiplication & Division
//\===========================================================================================

fixed	fixedAddition(fixed a_fa, fixed a_fb)//Adding two fixed point values together.
{
	return a_fa + a_fb;//Returns the sum of the two arguments passed in.
}

fixed	fixedSubtraction(fixed a_fa, fixed a_fb)//Subtract two fixed point values.
{
	return a_fa - a_fb;//Returns the answer of argument one subtracted by argument two.
}

fixed	fixedMultiply(fixed a_fa, fixed a_fb)//Multiply two fixed point values together.
{
	return (a_fa * a_fb) >> FIXED_SHIFT;//Returns the multiplication of the two arguments passed in.
}

fixed	fixedDivide(fixed a_fa, fixed a_fb)//Divide one fixed point values by another.
{
	return ((a_fa)* FIXED_SCALE) / a_fb;//Returns the division of the first argument by the second.
}

//\===========================================================================================
//\ Look Up Tables
//\===========================================================================================

s32 lookUpSin(u32 theta)//Sin lookup table.
{
	return sin_lut[(theta >> 7) & 0x1FF];//Returns the sin of the argument passed in.
}

s32 lookUpCos(u32 theta)//Cos lookup table.
{
	return sin_lut[((theta >> 7) + 128) & 0x1FF];//Returns the cos of the argument passed in.
}