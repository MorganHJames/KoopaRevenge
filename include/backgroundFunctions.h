//\===========================================================================================
//\ File: backgroundFunctions.h
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: 
//\===========================================================================================

#ifndef __BACKGROUND_FUNCTIONS_H__
#define __BACKGROUND_FUNCTIONS_H__

#include "gba_directMemoryAccesss.h"
#include "backgroundSprites.h"
#include "gba_graphics.h"
#include "background1.h"
#include "background2.h"
#include "background3.h"

void loadBackground()
{
	// Load background
	// Load palette
	directMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, backgroundSpritesPal, backgroundSpritesPalLen);

	// Load tile memory location
	// & with 0x3 so that we cannot access outside of layers 0-3

	// Copy the background data into our tile memory location
	directMemoryAccessWordCopy(tileBlockAddress(0), backgroundSpritesTiles, backgroundSpritesTilesLen);

	// Get the tilemap memory location and copy the map data into it
	// We only want to use tileblock locations 0, 8, 16 and 24
	// so we bitshift a_bgLayer up 3

	

	//Background 0 - collision and bushes
	u16* tileMapMemoryLocation1 = tileMapBlockAddress(16);
	u16* mapLocation1 = (u16*)background1;

	for (int i = 0; i < 128; ++i)
	{
		directMemoryAccessWordCopy(tileMapMemoryLocation1, mapLocation1, 64);
		tileMapMemoryLocation1 = tileMapMemoryLocation1 + 32;
		mapLocation1 += 64;
		if (i == 31)
		{
			mapLocation1 = (u16*)background1 + 32;
		}
	}

	//Background 1 - hills
	u16* tileMapMemoryLocation2 = tileMapBlockAddress(18);
	u16* mapLocation2 = (u16*)background2;
	
    for (int i = 0; i < 128; ++i)
    {
    	directMemoryAccessWordCopy(tileMapMemoryLocation2, mapLocation2, 64);
    	tileMapMemoryLocation2 = tileMapMemoryLocation2 + 32;
    	mapLocation2 += 64;
    	if (i == 31)
    	{
    		mapLocation2 = (u16*)background2 + 32;
    	}	
    }
	
	//Background 2 - clouds and sky
	u16* tileMapMemoryLocation3 = tileMapBlockAddress(20);
	u16* mapLocation3 = (u16*)background3;
	
	for (int i = 0; i < 128; ++i)
	{
		directMemoryAccessWordCopy(tileMapMemoryLocation3, mapLocation3, 64);
		tileMapMemoryLocation3 = tileMapMemoryLocation3 + 32;
		mapLocation3 += 64;
		if (i == 31)
		{
			mapLocation3 = (u16*)background3 + 32;
		}
	}
	

	// Set up the background control register
	setBackgroundControlRegister(0, 0, 0, 0, 0, 16, 0, BACKGROUND_REGISTRY_SIZE_64x32);
	setBackgroundControlRegister(1, 1, 0, 0, 0, 18, 0, BACKGROUND_REGISTRY_SIZE_64x32);
	setBackgroundControlRegister(2, 2, 0, 0, 0, 20, 0, BACKGROUND_REGISTRY_SIZE_64x32);

	//Move the maps the correct starting positions
	REGISTRY_BACKGROUND_OFF_SET[0].s16Y = 80;
	REGISTRY_BACKGROUND_OFF_SET[1].s16Y = 80;
    REGISTRY_BACKGROUND_OFF_SET[2].s16Y = 80;

}

#endif//#define __BACKGROUND_FUNCTIONS_H__
