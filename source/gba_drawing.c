//\===========================================================================================
//\ File: gba_drawing.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_drawing.h.
//\===========================================================================================

#include "gba_drawing.h"

//\===========================================================================================
//\ Colors
//\===========================================================================================

COLOR SetColor(u8 a_u8Red, u8 a_u8Green, u8 a_u8Blue)//A function to return a color with RGB inputs.
{
	return (a_u8Red & 0x1F) | (a_u8Green & 0x1F) << 5 | (a_u8Blue & 0x1f) << 10;
}

//\===========================================================================================
//\ Primitive Functions.
//\===========================================================================================

void DrawRectangle(u32 a_u32Left, u32 a_u32Top, u32 a_u32Width, u32 a_u32Height, COLOR a_u16Color)//A function to draw the primitive shape of a rectangle.
{
	for (u32 u32Y = 0; u32Y < a_u32Height; ++u32Y)//For the height rectangle.
	{
		for (u32 u32X = 0; u32X < a_u32Width; ++u32X)//For the width of the rectangle.
		{
			SCREENBUFFER[(a_u32Top + u32Y) * SCREEN_WIDTH + a_u32Left + u32X] = a_u16Color;//Draws to the screen.
		}
	}
}

void DrawLine(s32 a_s32X, s32 a_s32Y, s32 a_s32X2, s32 a_s32Y2, COLOR a_u16Color)//A function to draw the primitive shape of a line.
{
	s32 s32Width = a_s32X2 - a_s32X;//Calculates the width of the line.
	s32 s32Height = a_s32Y2 - a_s32Y;//Calculates the height of the line.
	s32 s32Dx1 = 0, s32Dy1 = 0, s32Dx2 = 0, s32Dy2 = 0;//Initializes the variables to 0.
	if (s32Width<0) s32Dx1 = -1; else if (s32Width>0) s32Dx1 = 1;//If the width is less than 0 set the dx1 to -1 or if width is greater than 0 set it to 1.
	if (s32Height<0) s32Dy1 = -1; else if (s32Height>0) s32Dy1 = 1;//If the height is less than 0 set the dy1 to -1 or if height is greater than 0 set it to 1.
	if (s32Width<0) s32Dx2 = -1; else if (s32Width>0) s32Dx2 = 1;//If the width is less than 0 set the dx2 to -1 or if width is greater than 0 set it to 1.
	s32 s32Longest = Absolute(s32Width);//Sets the longest value to be equal to the absolute value of the width.
	s32 s32Shortest = Absolute(s32Height);//Sets the shortest value to be equal to the absolute value of the height.
	if (!(s32Longest>s32Shortest))//If the longest is not greater than the shortest.
	{
		s32Longest = Absolute(s32Height);//Set the longest variable to the absolute height.
		s32Shortest = Absolute(s32Width);//Set the shortest variable to the absolute width.
		if (s32Height<0) s32Dy2 = -1; else if (s32Height>0) s32Dy2 = 1;//If the height is less than 0 set the dy2 to -1 or if height is greater than 0 set it to 1.
		s32Dx2 = 0;//Set dx2 to 0.
	}
	s32 s32Numerator = s32Longest >> 1;//Set the numerator to be equal to the longest variable bit shifted to the right by 1.
	for (s32 s32I = 0; s32I <= s32Longest; ++s32I)//For as long as i is less than or equal to the longest s32.
	{
		SCREENBUFFER[a_s32Y * SCREEN_WIDTH + a_s32X] = a_u16Color;//Draws to the screen.
		s32Numerator += s32Shortest;//Adds the shortest value to the numerator.
		if (!(s32Numerator<s32Longest))//If the numerator is not smaller than the longest.
		{
			s32Numerator -= s32Longest;//Subtracts the longest value from the numerator.
			a_s32X += s32Dx1;//Add dx1 to the X.
			a_s32Y += s32Dy1;//Add dy1 to the Y.
		}
		else//Otherwise.
		{
			a_s32X += s32Dx2;//Add dx2 to the X.
			a_s32Y += s32Dy2;//Add dy2 to the Y.
		}
	}
}