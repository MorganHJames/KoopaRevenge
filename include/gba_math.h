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

extern fixed	integerToFixed(s32 a_i);//Convert and integer to a fixed point representation.
extern fixed	floatToFixed(float a_f);//Convert a float to a fixed point representation.

//\===========================================================================================
//\ Functions To Convert From Fixed Point Representation To Non-fixed Point Representation
//\===========================================================================================

extern u32		fixedToUnsignedInteger(fixed a_f);//Convert a fixed point value into an integer value.
extern u32		fixedToUnsignedFractionalComponent(fixed a_f);//Get only the fractional component of a fixed point value as an integer.
extern s32		fixedToInteger(fixed a_f);//Convert a fixed point number into a signed integer.
extern float	fixedToFloat(fixed a_f);//Convert a fixed point number into a float.

//\===========================================================================================
//\ Functions To Undertake Fixed Point Addition, Subtraction, Multiplication & Division
//\===========================================================================================

extern fixed	fixedAddition(fixed a_fa, fixed a_fb);//Adding two fixed point values together.
extern fixed	fixedSubtraction(fixed a_fa, fixed a_fb);//Subtract two fixed point values.
extern fixed	fixedMultiply(fixed a_fa, fixed a_fb);//Multiply two fixed point values together.
extern fixed	fixedDivide(fixed a_fa, fixed a_fb);//Divide one fixed point values by another.

//\===========================================================================================
//\ Look Up Tables
//\===========================================================================================

extern s32 lookUpSin(u32 theta);//Sin lookup table.
extern s32 lookUpCos(u32 theta);//Cos lookup table.

#endif //__GBA_MATH_H__
