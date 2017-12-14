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

fixed IntegerToFixed(s32 a_s32Value)//Convert and integer to a fixed point representation.
{
	return a_s32Value << FIXED_SHIFT;//Returns a fixed point representation of the integer passed in.
}

fixed FloatToFixed(float a_fValue)//Convert a float to a fixed point representation.	
{
	return (fixed)(a_fValue*FIXED_SCALE_FLOAT);//Returns a fixed point representation of the float passed in.
}

//\===========================================================================================
//\ Functions To Convert From Fixed Point Representation To Non-fixed Point Representation
//\===========================================================================================

u32 FixedToUnsignedInteger(fixed a_fValue)//Convert a fixed point value into a unsigned integer value.
{
	return a_fValue >> FIXED_SHIFT;//Returns a unsigned integer from a fixed point argument.
}

u32 FixedToUnsignedFractionalComponent(fixed a_fValue)//Get only the fractional component of a fixed point value as an integer.
{
	return a_fValue & FIXED_MASK;//Returns the fractional component of the fixed point argument.
}

s32 FixedToInteger(fixed a_fValue)//Convert a fixed point number into a signed integer.
{
	return a_fValue / FIXED_SCALE;//Returns a signed integer from a fixed point argument.
}

float FixedToFloat(fixed a_fValue)//Convert a fixed point number into a float.
{
	return a_fValue / FIXED_SCALE_FLOAT;//Returns a float representation from a fixed point argument.
}

//\===========================================================================================
//\ Functions To Undertake Fixed Point Addition, Subtraction, Multiplication & Division
//\===========================================================================================

fixed FixedAddition(fixed a_fA, fixed a_fB)//Adding two fixed point values together.
{
	return a_fA + a_fB;//Returns the sum of the two arguments passed in.
}

fixed FixedSubtraction(fixed a_fA, fixed a_fB)//Subtract two fixed point values.
{
	return a_fA - a_fB;//Returns the answer of argument one subtracted by argument two.
}

fixed FixedMultiply(fixed a_fA, fixed a_fB)//Multiply two fixed point values together.
{
	return (a_fA * a_fB) >> FIXED_SHIFT;//Returns the multiplication of the two arguments passed in.
}

fixed FixedDivide(fixed a_fA, fixed a_fB)//Divide one fixed point values by another.
{
	return ((a_fA)* FIXED_SCALE) / a_fB;//Returns the division of the first argument by the second.
}

//\===========================================================================================
//\ Look Up Tables
//\===========================================================================================

s32 LookUpSin(u32 a_u32Value)//Sin lookup table.
{
	return sin_lut[(a_u32Value >> 7) & 0x1FF];//Returns the sin of the argument passed in.
}

s32 LookUpCos(u32 a_u32Value)//Cos lookup table.
{
	return sin_lut[((a_u32Value >> 7) + 128) & 0x1FF];//Returns the cos of the argument passed in.
}