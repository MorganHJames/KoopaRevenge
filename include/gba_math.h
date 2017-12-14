//\===========================================================================================
//\ File: gba_math.h
//\ Author: Morgan James
//\ Date Created: 24/11/2017
//\ Brief: Functions to carry out math equations.
//\===========================================================================================

#ifndef __GBA_MATH_H__
#define __GBA_MATH_H__

#include "gba_types.h"

//\======================================================================
// Fixed Point Mathematics
//\======================================================================

#define FIXED_SHIFT			8//This fix shift defines the number of bits reserved for decimal values the GBA uses 8.8 fixed values for it's affine's and transforms in OAM.

#define FIXED_SCALE			( 1 << FIXED_SHIFT	)//1 shifted up by 8 units.
#define FIXED_MASK			( FIXED_SCALE-1		)//Fixed scale with one subtracted from it to set all the lower bits to turn them on or off.
#define FIXED_SCALE_FLOAT	( (float)FIXED_SCALE	)//Fixed scale casted into a float.
#define FIXED_SCALE_INVERSE	( 1.0f/FIXED_SCALE_FLOAT	)//1 divided by the fixed scale float.

#define FIXED_ONE			FIXED_SCALE//1 shifted up by 8 units.

typedef s32 fixed;//Using a signed 32 bit value for fixed point 24.8 fixed. The GBA uses signed 16 bit values as 8.8 fixed. The additional 16 bits on our fixed value will allow for better numerical overflow.

//\===========================================================================================
//\ Functions To Convert From Non-fixed Point Representation To Fixed Point Representation
//\===========================================================================================

extern fixed IntegerToFixed(s32 a_s32Value);//Convert and integer to a fixed point representation.
extern fixed FloatToFixed(float a_fValue);//Convert a float to a fixed point representation.

//\===========================================================================================
//\ Functions To Convert From Fixed Point Representation To Non-fixed Point Representation
//\===========================================================================================

extern u32 FixedToUnsignedInteger(fixed a_fValue);//Convert a fixed point value into an integer value.
extern u32 FixedToUnsignedFractionalComponent(fixed a_fValue);//Get only the fractional component of a fixed point value as an integer.
extern s32 FixedToInteger(fixed a_fValue);//Convert a fixed point number into a signed integer.
extern float FixedToFloat(fixed a_fValue);//Convert a fixed point number into a float.

//\===========================================================================================
//\ Functions To Undertake Fixed Point Addition, Subtraction, Multiplication & Division
//\===========================================================================================

extern fixed FixedAddition(fixed a_fA, fixed a_fB);//Adding two fixed point values together.
extern fixed FixedSubtraction(fixed a_fA, fixed a_fB);//Subtract two fixed point values.
extern fixed FixedMultiply(fixed a_fA, fixed a_fB);//Multiply two fixed point values together.
extern fixed FixedDivide(fixed a_fA, fixed a_fB);//Divide one fixed point values by another.

//\===========================================================================================
//\ Look Up Tables
//\===========================================================================================

extern s32 LookUpSin(u32 a_u32Value);//Sin lookup table.
extern s32 LookUpCos(u32 a_u32Value);//Cos lookup table.

#endif//__GBA_MATH_H__
