//\===========================================================================================
//\ File: backgroundFunctions.h
//\ Author: Morgan James
//\ Date Created: 28/11/2017
//\ Brief: 
//\===========================================================================================

#ifndef __BACKGROUND_FUNCTIONS_H__
#define __BACKGROUND_FUNCTIONS_H__

#include "gba_dma.h"
#include "background.h"
#include "map.h"
#include "gba_graphics.h"

void loadBackground()
{
	dma_word_cpy(PALETTE_BACKGROUND_MEMORY, background_palette, background_paletteLen);
	u16* tileMemoryLocation = tileBlockAddress(0);
	dma_word_cpy(tileMemoryLocation, background_data, background_dataLen);
	u16* tileMapMemoryLocation = tileMapBlockAddress(16);
	dma_word_cpy(tileMapMemoryLocation, map, map_dataLen);

	setBackgroundControlRegister(0, 0, 0, 0, 1, 16, 0, BACKGROUND_REGISTRY_SIZE_32x32);

}

#endif//#define __BACKGROUND_FUNCTIONS_H__
