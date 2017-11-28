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

COLOR setColor(u8 a_u8Red, u8 a_u8Green, u8 a_u8Blue)//A function to return a color with RGB inputs.
{
	return (a_u8Red & 0x1F) | (a_u8Green & 0x1F) << 5 | (a_u8Blue & 0x1f) << 10;
}

//\===========================================================================================
//\ Primitive Functions.
//\===========================================================================================

void drawRectangle(u32 a_u32Left, u32 a_u32Top, u32 a_u32Width, u32 a_u32Height, COLOR a_cColor)//A function to draw the primitive shape of a rectangle.
{
	for (u32 y = 0; y < a_u32Height; ++y)//For the height rectangle.
	{
		for (u32 x = 0; x < a_u32Width; ++x)//For the width of the rectangle.
		{
			SCREENBUFFER[(a_u32Top + y) * SCREEN_WIDTH + a_u32Left + x] = a_cColor;//Draws to the screen.
		}
	}
}

void drawLine(s32 a_s32X, s32 a_s32Y, s32 a_s32X2, s32 a_s32Y2, COLOR a_cColor)//A function to draw the primitive shape of a line.
{
	s32 width = a_s32X2 - a_s32X;//Calculates the width of the line.
	s32 height = a_s32Y2 - a_s32Y;//Calculates the height of the line.
	s32 dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;//Initializes the variables to 0.
	if (width<0) dx1 = -1; else if (width>0) dx1 = 1;//If the width is less than 0 set the dx1 to -1 or if width is greater than 0 set it to 1.
	if (height<0) dy1 = -1; else if (height>0) dy1 = 1;//If the height is less than 0 set the dy1 to -1 or if height is greater than 0 set it to 1.
	if (width<0) dx2 = -1; else if (width>0) dx2 = 1;//If the width is less than 0 set the dx2 to -1 or if width is greater than 0 set it to 1.
	s32 longest = absolute(width);//Sets the longest value to be equal to the absolute value of the width.
	s32 shortest = absolute(height);//Sets the shortest value to be equal to the absolute value of the height.
	if (!(longest>shortest))//If the longest is not greater than the shortest.
	{
		longest = absolute(height);//Set the longest variable to the absolute height.
		shortest = absolute(width);//Set the shortest variable to the absolute width.
		if (height<0) dy2 = -1; else if (height>0) dy2 = 1;//If the height is less than 0 set the dy2 to -1 or if height is greater than 0 set it to 1.
		dx2 = 0;//Set dx2 to 0.
	}
	s32 numerator = longest >> 1;//Set the numerator to be equal to the longest variable bit shifted to the right by 1.
	for (s32 i = 0; i <= longest; ++i)//For as long as i is less than or equal to the longest s32.
	{
		SCREENBUFFER[a_s32Y * SCREEN_WIDTH + a_s32X] = a_cColor;//Draws to the screen.
		numerator += shortest;//Adds the shortest value to the numerator.
		if (!(numerator<longest))//If the numerator is not smaller than the longest.
		{
			numerator -= longest;//Subtracts the longest value from the numerator.
			a_s32X += dx1;//Add dx1 to the X.
			a_s32Y += dy1;//Add dy1 to the Y.
		}
		else//Otherwise.
		{
			a_s32X += dx2;//Add dx2 to the X.
			a_s32Y += dy2;//Add dy2 to the Y.
		}
	}
}