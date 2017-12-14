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
#include "background4.h"
#include "titleSplash.h"
#include "splash.h"

void splash()
{
	//\===========================================================================================
	//\ SPLASH Setup 
	//\===========================================================================================

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_VIDEOMODE_4 | DISPLAYCONTROL_BACKGROUNDMODE_2;

	DirectMemoryAccessWordCopy(VIDEO_RANDOM_ACCESS_MEMORY_PAGE, splashBitmap, splashBitmapLen);
	DirectMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, splashPal, splashPalLen);
	Sleep(3, TIMER_SECONED);
}

void loadGameBackground()
{
	// Load background
	// Load palette
	DirectMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, backgroundSpritesPal, backgroundSpritesPalLen);
	// Load tile memory location
	// & with 0x3 so that we cannot access outside of layers 0-3

	// Copy the background data into our tile memory location
	DirectMemoryAccessWordCopy(TileBlockAddress(0), backgroundSpritesTiles, backgroundSpritesTilesLen);

	// Get the tilemap memory location and copy the map data into it
	// We only want to use tileblock locations 0, 8, 16 and 24
	// so we bitshift a_bgLayer up 3


	//Background 0 - collision and bushes
	u16* tileMapMemoryLocation = TileMapBlockAddress(16);
	u16* mapLocation = (u16*)background1;

	for (int i = 0; i < 128; ++i)
	{
		DirectMemoryAccessWordCopy(tileMapMemoryLocation, mapLocation, 64);
		tileMapMemoryLocation = tileMapMemoryLocation + 32;
		mapLocation += 64;
		if (i == 31)
		{
			mapLocation = (u16*)background1 + 32;
		}
	}

	//Background 1 - hills
	tileMapMemoryLocation = TileMapBlockAddress(18);
	mapLocation = (u16*)background2;
	
	for (int i = 0; i < 128; ++i)
	{
		DirectMemoryAccessWordCopy(tileMapMemoryLocation, mapLocation, 64);
		tileMapMemoryLocation = tileMapMemoryLocation + 32;
		mapLocation += 64;
		if (i == 31)
		{
			mapLocation = (u16*)background2 + 32;
		}	
	}
	
	//Background 2 - clouds and sky
	tileMapMemoryLocation = TileMapBlockAddress(20);
	mapLocation = (u16*)background3;
	
	for (int i = 0; i < 128; ++i)
	{
		DirectMemoryAccessWordCopy(tileMapMemoryLocation, mapLocation, 64);
		tileMapMemoryLocation = tileMapMemoryLocation + 32;
		mapLocation += 64;
		if (i == 31)
		{
			mapLocation = (u16*)background3 + 32;
		}
	}

	DirectMemoryAccessWordCopy(&PALETTE_BACKGROUND_MEMORY[129], titleSplashPal, titleSplashPalLen);
	DirectMemoryAccessWordCopy(TileBlockAddress(129), titleSplashTiles, titleSplashTilesLen);

	//Background 3 - splash title
	tileMapMemoryLocation = TileMapBlockAddress(22);
	mapLocation = (u16*)background4;

	for (int i = 0; i < 128; ++i)
	{
		DirectMemoryAccessWordCopy(tileMapMemoryLocation, mapLocation, 64);
		tileMapMemoryLocation = tileMapMemoryLocation + 32;
		mapLocation += 64;
		if (i == 31)
		{
			mapLocation = (u16*)background4 + 32;
		}
	}

	// Set up the background control register
	SetBackgroundControlRegister(0, 1, 0, 0, 0, 16, 0, BACKGROUND_REGISTRY_SIZE_64x32);
	SetBackgroundControlRegister(1, 2, 0, 0, 0, 18, 0, BACKGROUND_REGISTRY_SIZE_64x32);
	SetBackgroundControlRegister(2, 3, 0, 0, 0, 20, 0, BACKGROUND_REGISTRY_SIZE_64x32);
	SetBackgroundControlRegister(3, 0, 129, 0, 0, 22, 0, BACKGROUND_REGISTRY_SIZE_64x32);

	///Chnages palette of background 3
	for (int i = 0; i < 350; ++i)
	{
		*(u16*)(VIDEO_RANDOM_ACCESS_MEMORY + ((22 * TILE_MAP_BLOCK_SIZE) + (i * 2))) = SetScreenEntry(i , 0, 8);
	}

	//Move the maps the correct starting positions
	REGISTRY_BACKGROUND_OFF_SET[0].s16Y = 80;
	REGISTRY_BACKGROUND_OFF_SET[1].s16Y = 80;
	REGISTRY_BACKGROUND_OFF_SET[2].s16Y = 45;
	REGISTRY_BACKGROUND_OFF_SET[3].s16X = -32;
}

void unloadGameBackground()
{
	u16* tileMapMemoryLocation = TileMapBlockAddress(16);
	DirectMemoryAccessWordCopy(tileMapMemoryLocation, 0, 64);
	tileMapMemoryLocation = TileMapBlockAddress(18);
	DirectMemoryAccessWordCopy(tileMapMemoryLocation, 0, 64);
	tileMapMemoryLocation = TileMapBlockAddress(20);
	DirectMemoryAccessWordCopy(tileMapMemoryLocation, 0, 64);
}

#endif//#define __BACKGROUND_FUNCTIONS_H__
