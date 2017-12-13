//\===========================================================================================
//\ File: gba_graphics.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_graphics.h.
//\===========================================================================================

#include "Intellisense.h"
#include "gba_graphics.h"
#include "sinlut.h"


ObjectAttribute objectBuffer[128] = {};
ObjectAffine *const objectAffineBuffer = (ObjectAffine*)objectBuffer;

//\===========================================================================================
//\ Vertical Blank Testing Function
//\===========================================================================================

void verticalSync()//A function to allow for the drawing to be done on the vertical blank.
{
	while (REGISTRY_VERTICAL_COUNT >= 160);
	while (REGISTRY_VERTICAL_COUNT < 160);
}

//\===========================================================================================
//\ Functionality For Setting Up Page Flipping In Bitmap Rendering Modes
//\===========================================================================================

u16* videoPage = VIDEO_RANDOM_ACCESS_MEMORY_PAGE_BACK;

u16* pageFlip()//A function to flip the screen from the back page to the front and vice versa.
{
	videoPage = (u16*)((u32)videoPage ^ VIDEO_RANDOM_ACCESS_MEMORY_PAGE_SIZE);
	REGISTRY_DISPLAYCONTROL ^= VIDEO_RANDOM_ACCESS_MEMORY_PAGE_INDICATOR;	// update control register	

	return videoPage;
}

//\===========================================================================================
//\ Background Tiled Rendering
//\===========================================================================================

u16* paletteBackgroundBlockAddress(u32 a_blockNum)
{
	//each block is 16KB in size
	return (u16*)(PALETTE_BACKGROUND_MEMORY + (a_blockNum * 16));
}

u16* paletteSpriteBlockAddress(u32 a_blockNum)
{
	//each block is 16KB in size
	return (u16*)(PALETTE_SPRITE_MEMORY + (a_blockNum * 16));
}

u16* tileBlockAddress(u32 a_u32BlockNum)//Function to return the memory address (pointer) to one of the four tile block locations (0-3).
{
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (a_u32BlockNum * TILE_BLOCK_SIZE));//Each block is 16KB in size.
}

u16* tileMapBlockAddress(u32 a_u32BlockNum)//Function to return a pointer to address space for the tile map blocks location (0-31).
{
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (a_u32BlockNum * TILE_MAP_BLOCK_SIZE));//Each tile map block is 2KB in size.
}

void setBackgroundControlRegister(u8 a_u8RegNum, u8 a_u8Priority, u8 a_u8TileBlockID, u8 a_u8Mosaic, u8 a_u8ColorMode, u8 a_u8MapBlockID, u8 a_u8AffineWrap, u8 a_u8BackgroundSize)//Function to set a background control register's values.
{
	vu16 control = (a_u8Priority & BACKGROUND_COTNROL_PRIORITY_MASK) | ((a_u8TileBlockID & BACKGROUND_COTNROL_TILE_BLOCK_ID_MASK) << 2) | ((a_u8Mosaic & BACKGROUND_COTNROL_MOSIAC_MASK) << 6) | ((a_u8ColorMode & BACKGROUND_COTNROL_COLOR_MASK) << 7) |
		((a_u8MapBlockID & BACKGROUND_COTNROL_TILE_MAP_ID_MASK) << 8) | ((a_u8AffineWrap & BACKGROUND_COTNROL_AFINE_WRAP_MASK) << 13) | ((a_u8BackgroundSize & BACKGROUND_COTNROL_SIZE_MASK) << 14);
	REGISTRY_BACKGROUND_CONTROL[a_u8RegNum] = control;//Sets the background control register using the arguments passed in.
}

u16 setScreenEntry(int ti, u8 flip, u8 palBank)
{
	return (ti) | ((flip & SCREEN_ENTRY_FLIP_MASK) << 10) | ((palBank & SCREEN_ENTRY_PALETTE_BANK_MASK) << 12);
}

//====================================================================================
//Sprites & Object Attribute Memory
//====================================================================================

u16* spriteTileBlockAddress(u32 a_tile_number)
{
	//each block is 16KB in size sprites occur on block 4 of tile memory (blocks 0-3 are for bg tiles)
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (4 * TILE_BLOCK_SIZE) + ((a_tile_number & 0x3FF) * sizeof(TILE)));

}

u16 setAttribute0(u8 a_u8Y, u8 a_u8ObjectMode, u8 a_u8GfxMode, u8 a_u8mosiac, u8 a_u8ColorMode, u8 a_u8Shape)//Sets the attribute 0 of the sprite.
{
	u16 attrib0 = (a_u8Y & ATTRIBUTE0_YMASK) | ((a_u8ObjectMode & 0x3) << 8) | ((a_u8GfxMode & 0x3) << 10) |
		((a_u8mosiac & 0x1) << 12) | ((a_u8ColorMode & 0x1) << 13) | ((a_u8Shape & 0x3) << 14);
	return attrib0;
}

u16 setAttribute1(u8 a_u8X, u8 a_u8Flip, u8 a_u8Size)//Sets the attribute 1 of the sprite.
{
	u16 attrib1 = (a_u8X & ATTRIBUTE1_XMASK) | ((a_u8Flip & ATTRIBUTE1_FLIPMASK) << 12) | ((a_u8Size & 3) << 14);
	return attrib1;
}

void setAttribute1AffineIndex(ObjectAttribute* a_oaObject, u8 a_u8Index)//Sets the attribute 1 affine index  of the sprite.
{
	a_oaObject->attribute1 = (a_oaObject->attribute1 & 0xC1FF) | ((a_u8Index & ATTRIBUTE1_AFF_INDEX_MASK) << 9);//Use 0xC1FF to strip out bits 9 -> D.
}

u16 setAttribute2(u8 a_u8TileIndex, u8 a_u8Priority, u8 a_u8PaletteBank)//Sets the attribute 2 of the sprite.
{
	u16 attribute2 = (a_u8TileIndex & 0x3FF) | ((a_u8Priority & 3) << 10) | ((a_u8PaletteBank & 0xF) << 12);
	return attribute2;
}

void setObjectPosition(ObjectAttribute* a_oaObject, u8 a_u8X, u8 a_u8Y)//Sets the position of the sprite.
{
	a_oaObject->attribute0 = (a_oaObject->attribute0 & 0xFF00) | (a_u8Y  & 0x00FF);
	a_oaObject->attribute1 = (a_oaObject->attribute1 & 0xFE00) | (a_u8X & 0x01FF);
}

void objectHide(ObjectAttribute* a_oaObject)//Hide a sprite.
{
	a_oaObject->attribute0 = (a_oaObject->attribute0 & ATTRIBUTE0_MODE_MASK) | (ATTRIBUTE0_MODE_HIDE << 8);//Object attribute 0 is where the hide flag is located, the argument changes the flag.
}
void objectUnhide(ObjectAttribute* a_oaObject, u8 a_u8Mode)//Makes the sprite unhidden.
{
	a_oaObject->attribute0 = (a_oaObject->attribute0 & ATTRIBUTE0_MODE_MASK) | (a_u8Mode& 0x3 << 8);//Object attribute 0 is where the hide flag is located, the argument changes the flag. The mask with the 3 is to make sure we pass in the correct number less than 3.
}
void objectAttributeMemoryInitialize(ObjectAttribute* a_oaObject, u8 a_u8Count)//Initialize object attribute memory.
{
	u32 resetCount = a_u8Count;
	ObjectAttribute *destination = a_oaObject;

	// Hide each object
	while (resetCount--)//Whilst resetCount is greater than 0.
	{
		destination->attribute0 = 0;//Sets destination attribute0 to 0.
		destination->attribute1 = 0;//Sets destination attribute1 to 0.
		destination->attribute2 = 0;//Sets destination attribute2 to 0.
		destination->padding = 0;//Sets destination padding data to 0.
		objectHide(destination);//Hide the current object we are pointing at.
		++destination;//Point to the next destination in our object attribute space.
	}
	objectAttributeMemoryCopy(MEMORY_OBJECT_ATTRIBUTE_MEMORY, a_oaObject, a_u8Count);//Initialize object attribute memory.
}

void objectAttributeMemoryCopy(ObjectAttribute* a_oaDestination, ObjectAttribute* a_oaSource, u8 a_u8Count)//Copies the object attribute memory from one place to another.
{
	u32 *destinationPointer = (u32*)a_oaDestination, *sourcePointer = (u32*)a_oaSource;//Casts the destination pointer and the source pointer into 32 bit integers.
	while (a_u8Count--)//While count is above 0.
	{
		*destinationPointer++ = *sourcePointer++;//Post increment to increment after the assignment operator.
		*destinationPointer++ = *sourcePointer++;//Increments a second time to get the 2nd attribute and the padding data.
	}
}

void objectAffineIdentity(ObjectAffine* a_oaObject)//Set the affine object matrix to an identity matrix.
{
	a_oaObject->pa = 0x01001; a_oaObject->pb = 0; a_oaObject->pc = 0; a_oaObject->pd = 0x0100;//Sets up identity matrix.
}

void objectAffineRotationScale(ObjectAffine* a_oaObjectAffine, fixed a_fScaleX, fixed a_fScaleY, u16 a_u16Alpha)//Set the rotation and scale of the object uses the sine look up table to retrieve a value for sine & cosine.
{
	int sinValue = lookUpSin(a_u16Alpha), cosValue = lookUpCos(a_u16Alpha);//Sets the sin and cos values from putting the argument into the lookup tables.
	a_oaObjectAffine->pa = cosValue*a_fScaleX >> 12; a_oaObjectAffine->pb = -sinValue*a_fScaleX >> 12; a_oaObjectAffine->pc = sinValue*a_fScaleY >> 12;	a_oaObjectAffine->pd = cosValue*a_fScaleY >> 12;//Shifts values down 12 to account for fixed point multiply to keep values as .8 fixed.
}