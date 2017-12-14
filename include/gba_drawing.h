//\===========================================================================================
//\ File: gba_drawing.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Functions to draw primitive shapes to the screen.
//\===========================================================================================

#ifndef __GBA_DRAWING_H__
#define __GBA_DRAWING_H__

#include "gba_registry.h"
#include "gba_types.h"
#include "gba_mathUtility.h"

//\===========================================================================================
//\ Defines For Screen Sizes In Different Rendering Modes 
//\===========================================================================================

#define SCREENBUFFER					    ((vu16*)(VIDEO_RANDOM_ACCESS_MEMORY))//Contains a complete frame of data that is displayed to the screen.

#define SCREEN_WIDTH						240//The width of the GBA screen in pixels.
#define SCREEN_HEIGHT						160//The height of the GBA screen in pixels.

#define VIDEO_RENDERING_MODE_3_WIDTH 		SCREEN_WIDTH//The width of video rendering mode 3.
#define VIDEO_RENDERING_MODE_3_HEIGHT		SCREEN_HEIGHT//The height of video rendering mode 3.

#define VIDEO_RENDERING_MODE_4_WIDTH		SCREEN_WIDTH//The width of video rendering mode 4.
#define VIDEO_RENDERING_MODE_4_HEIGHT		SCREEN_HEIGHT//The height of video rendering mode 4.

#define VIDEO_RENDERING_MODE_5_WIDTH	    160//The width of video rendering mode 5 in pixels.
#define VIDEO_RENDERING_MODE_5_HEIGHT		128//The height of video rendering mode 5 in pixels.

#define SCREEN_TOTAL					    38400//The total amount of pixels on the GBA screen in pixels

//\===========================================================================================
//\ Colors
//\===========================================================================================

#define COLOR_BLACK			0x0000//The hexadecimal code for black.
#define COLOR_RED			0x001F//The hexadecimal code for red.
#define COLOR_LIME			0x03E0//The hexadecimal code for lime.
#define COLOR_YELLOW		0x03FF//The hexadecimal code for yellow.
#define COLOR_GREEN			0x07E0//The hexadecimal code for green.
#define COLOR_BLUE			0x7C00//The hexadecimal code for blue.
#define COLOR_MAGENTA		0x7C1F//The hexadecimal code for magenta.
#define COLOR_CYAN			0x7FE0//The hexadecimal code for cyan.
#define COLOR_WHITE			0x7FFF//The hexadecimal code for white.

extern COLOR SetColor(u8 a_u8Red, u8 a_u8Green, u8 a_u8Blue);//A function to return a color with RGB inputs.

//\===========================================================================================
//\ Primitive Functions
//\===========================================================================================

extern void DrawRectangle(u32 a_u32Left, u32 a_u32Top, u32 a_u32Width, u32 a_u32Height, COLOR a_u16Color);//A function to draw the primitive shape of a rectangle.

extern void DrawLine(s32 a_s32X, s32 a_s32Y, s32 a_s32X2, s32 a_s32Y2, COLOR a_u16Color);//A function to draw the primitive shape of a line.

#endif//__GBA_DRAWING_H__
