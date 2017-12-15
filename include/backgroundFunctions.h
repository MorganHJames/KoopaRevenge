//\===========================================================================================
//\ File: backgroundFunctions.h
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: A header that contains functions to set up the backgrounds.
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

void SplashScreenLoad()//A functions to display a splash screen for a certain amount of time.
{
	//\===========================================================================================
	//\ SPLASH Setup 
	//\===========================================================================================

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_VIDEOMODE_4 | DISPLAYCONTROL_BACKGROUNDMODE_2;//Sets the registry up for bitmap rendering.

	DirectMemoryAccessWordCopy(VIDEO_RANDOM_ACCESS_MEMORY_PAGE, splashBitmap, splashBitmapLen);//Copies the image into the memory.
	DirectMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, splashPal, splashPalLen);//Copies the palette of the image into the memory.
	Sleep(3, TIMER_SECONED);//Waits 3 seconds before moving onwards.
}

void LoadGameBackground()//Loads the backgrounds into memory and sets them up correctly.
{
	DirectMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, backgroundSpritesPal, backgroundSpritesPalLen);//Copies the backgrounds palette into memory.

	DirectMemoryAccessWordCopy(TileBlockAddress(0), backgroundSpritesTiles, backgroundSpritesTilesLen);//Copies the background data into tile memory.

	//\===========================================================================================
	//\ Background 0 - Collision And Bushes. 
	//\===========================================================================================

	u16* pu16TileMapMemoryLocation = TileMapBlockAddress(16);//Where the tiles will be saved.
	u16* pu16MapLocation = (u16*)background1;//What tiles we want to load in.

	for (u32 u32I = 0; u32I < 128; ++u32I)//Iterates through the tiles.
	{
		DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, pu16MapLocation, 64);//Copies the correct tile to the correct memory location.
		pu16TileMapMemoryLocation += 32;//Increases the tile location by 32 as we have to load the maps in 32x32 chunks.
		pu16MapLocation += 64;//Increases the map location so the correct tile goes in the correct memory as the map is 32x64.
		if (u32I == 31)//If the iterator is at the end of a chunk.
		{
			pu16MapLocation = (u16*)background1 + 32;//Increase the map location.
		}
	}

	//\===========================================================================================
	//\ Background 1 - Hills.
	//\===========================================================================================

	pu16TileMapMemoryLocation = TileMapBlockAddress(18);//Where the tiles will be saved.
	pu16MapLocation = (u16*)background2;//What tiles we want to load in.

	for (u32 u32I = 0; u32I < 128; ++u32I)//Iterates through the tiles.
	{
		DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, pu16MapLocation, 64);//Copies the correct tile to the correct memory location.
		pu16TileMapMemoryLocation = pu16TileMapMemoryLocation + 32;//Increases the tile location by 32 as we have to load the maps in 32x32 chunks.
		pu16MapLocation += 64;//Increases the map location so the correct tile goes in the correct memory as the map is 32x64.
		if (u32I == 31)//If the iterator is at the end of a chunk.
		{
			pu16MapLocation = (u16*)background2 + 32;//Increase the map location.
		}
	}

	//\===========================================================================================
	//\ Background 2 - Clouds And Sky.
	//\===========================================================================================

	pu16TileMapMemoryLocation = TileMapBlockAddress(20);//Where the tiles will be saved.
	pu16MapLocation = (u16*)background3;//What tiles we want to load in.

	for (u32 u32I = 0; u32I < 128; ++u32I)//Iterates through the tiles.
	{
		DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, pu16MapLocation, 64);//Copies the correct tile to the correct memory location.
		pu16TileMapMemoryLocation = pu16TileMapMemoryLocation + 32;//Increases the tile location by 32 as we have to load the maps in 32x32 chunks.
		pu16MapLocation += 64;//Increases the map location so the correct tile goes in the correct memory as the map is 32x64.
		if (u32I == 31)//If the iterator is at the end of a chunk.
		{
			pu16MapLocation = (u16*)background3 + 32;//Increase the map location.
		}
	}

	DirectMemoryAccessWordCopy(&PALETTE_BACKGROUND_MEMORY[129], titleSplashPal, titleSplashPalLen);//Copies the splashTitle palette into memory.
	DirectMemoryAccessWordCopy(TileBlockAddress(129), titleSplashTiles, titleSplashTilesLen);//Copies the splashTitle tiles into memory.
	
	//\===========================================================================================
	//\ Background 3 - Splash Title.
	//\===========================================================================================

	pu16TileMapMemoryLocation = TileMapBlockAddress(22);//Where the tiles will be saved.
	pu16MapLocation = (u16*)background4;//What tiles we want to load in.

	for (u32 u32I = 0; u32I < 128; ++u32I)//Iterates through the tiles.
	{
		DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, pu16MapLocation, 64);//Copies the correct tile to the correct memory location.
		pu16TileMapMemoryLocation = pu16TileMapMemoryLocation + 32;//Increases the tile location by 32 as we have to load the maps in 32x32 chunks.
		pu16MapLocation += 64;//Increases the map location so the correct tile goes in the correct memory as the map is 32x64.
		if (u32I == 31)//If the iterator is at the end of a chunk.
		{
			pu16MapLocation = (u16*)background4 + 32;//Increase the map location.
		}
	}

	//\===========================================================================================
	//\ Background Control Register Set up
	//\===========================================================================================

	SetBackgroundControlRegister(0, 1, 0, 0, 0, 16, 0, BACKGROUND_REGISTRY_SIZE_64x32);//Sets up background 0.
	SetBackgroundControlRegister(1, 2, 0, 0, 0, 18, 0, BACKGROUND_REGISTRY_SIZE_64x32);//Sets up background 1.
	SetBackgroundControlRegister(2, 3, 0, 0, 0, 20, 0, BACKGROUND_REGISTRY_SIZE_64x32);//Sets up background 2.
	SetBackgroundControlRegister(3, 0, 129, 0, 0, 22, 0, BACKGROUND_REGISTRY_SIZE_64x32);//Sets up background 3.
	
	//\===========================================================================================
	//\ Changes Palette Of Background 3
	//\===========================================================================================

	for (u32 u32I = 0; u32I < 343; ++u32I)//Iterates through the tiles of the splash screen.
	{
		*(u16*)(VIDEO_RANDOM_ACCESS_MEMORY + ((22 * TILE_MAP_BLOCK_SIZE) + (u32I * 2))) = SetScreenEntry(u32I, 0, 8);//Sets the tiles of background 3 to use the correct palette bank.
	}

	//Move the maps the correct starting positions
	REGISTRY_BACKGROUND_OFF_SET[0].s16Y = 80;//Sets the offset of background 0.
	REGISTRY_BACKGROUND_OFF_SET[1].s16Y = 80;//Sets the offset of background 1.
	REGISTRY_BACKGROUND_OFF_SET[2].s16Y = 45;//Sets the offset of background 2.
	REGISTRY_BACKGROUND_OFF_SET[3].s16X = -32;//Sets the offset of background 3.
}

void UnloadGameBackground()//Clears all tile data from the backgrounds.
{
	u16* pu16TileMapMemoryLocation = TileMapBlockAddress(16);//Sets the location of the tiles to change to background 0.
	DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, 0, 64);//Sets the tiles data to be equal to 0;
	pu16TileMapMemoryLocation = TileMapBlockAddress(18);//Sets the location of the tiles to change to background 1.
	DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, 0, 64);//Sets the tiles data to be equal to 0;
	pu16TileMapMemoryLocation = TileMapBlockAddress(20);//Sets the location of the tiles to change to background 2.
	DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, 0, 64);//Sets the tiles data to be equal to 0;
	pu16TileMapMemoryLocation = TileMapBlockAddress(22);//Sets the location of the tiles to change to background 3.
	DirectMemoryAccessWordCopy(pu16TileMapMemoryLocation, 0, 64);//Sets the tiles data to be equal to 0;
}

#endif//#define __BACKGROUND_FUNCTIONS_H__
