//\===========================================================================================
//\ File: gba_graphics.c
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the function information for the prototypes contained in gba_graphics.h.
//\===========================================================================================

#include "Intellisense.h"
#include "gba_graphics.h"
#include "sinlut.h"

ObjectAttribute ObjectBuffer[128] = {};
ObjectAffine *const c_pObjectAffineBuffer = (ObjectAffine*)ObjectBuffer;

//\===========================================================================================
//\ Vertical Blank Testing Function
//\===========================================================================================

void VerticalSync()//A function to allow for the drawing to be done on the vertical blank.
{
	while (REGISTRY_VERTICAL_COUNT >= 160);
	while (REGISTRY_VERTICAL_COUNT < 160);
}

//\===========================================================================================
//\ Functionality For Setting Up Page Flipping In Bitmap Rendering Modes
//\===========================================================================================

u16* VideoPage = VIDEO_RANDOM_ACCESS_MEMORY_PAGE_BACK;

u16* PageFlip()//A function to flip the screen from the back page to the front and vice versa.
{
	VideoPage = (u16*)((u32)VideoPage ^ VIDEO_RANDOM_ACCESS_MEMORY_PAGE_SIZE);
	REGISTRY_DISPLAYCONTROL ^= VIDEO_RANDOM_ACCESS_MEMORY_PAGE_INDICATOR;//Update control register	

	return VideoPage;
}

//\===========================================================================================
//\ Background Tiled Rendering
//\===========================================================================================

u16* PaletteBackgroundBlockAddress(u32 a_u32BlockNumber)
{
	return (u16*)(PALETTE_BACKGROUND_MEMORY + (a_u32BlockNumber * 16));//Each block is 16KB in size.
}

u16* PaletteSpriteBlockAddress(u32 a_u32BlockNumber)
{
	return (u16*)(PALETTE_SPRITE_MEMORY + (a_u32BlockNumber * 16));//Each block is 16KB in size.
}

u16* TileBlockAddress(u32 a_u32BlockNumber)//Function to return the memory address (pointer) to one of the four tile block locations (0-3).
{
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (a_u32BlockNumber * TILE_BLOCK_SIZE));//Each block is 16KB in size.
}

u16* TileMapBlockAddress(u32 a_u32BlockNumber)//Function to return a pointer to address space for the tile map blocks location (0-31).
{
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (a_u32BlockNumber * TILE_MAP_BLOCK_SIZE));//Each tile map block is 2KB in size.
}

void SetBackgroundControlRegister(u8 a_u8RegistryNumber, u8 a_u8Priority, u8 a_u8TileBlockID, u8 a_u8Mosaic, u8 a_u8ColorMode, u8 a_u8MapBlockID, u8 a_u8AffineWrap, u8 a_u8BackgroundSize)//Function to set a background control register's values.
{
	vu16 vu16Control = (a_u8Priority & BACKGROUND_COTNROL_PRIORITY_MASK) | ((a_u8TileBlockID & BACKGROUND_COTNROL_TILE_BLOCK_ID_MASK) << 2) | ((a_u8Mosaic & BACKGROUND_COTNROL_MOSIAC_MASK) << 6) | ((a_u8ColorMode & BACKGROUND_COTNROL_COLOR_MASK) << 7) |
		((a_u8MapBlockID & BACKGROUND_COTNROL_TILE_MAP_ID_MASK) << 8) | ((a_u8AffineWrap & BACKGROUND_COTNROL_AFINE_WRAP_MASK) << 13) | ((a_u8BackgroundSize & BACKGROUND_COTNROL_SIZE_MASK) << 14);
	REGISTRY_BACKGROUND_CONTROL[a_u8RegistryNumber] = vu16Control;//Sets the background control register using the arguments passed in.
}

u16 SetScreenEntry(u16 a_u16TileIndex, u8 a_u8Flip, u8 a_u8PaletteBank)//Allows for the changing of background tiles flip or palette bank.
{
	return (a_u16TileIndex) | ((a_u8Flip & SCREEN_ENTRY_FLIP_MASK) << 10) | ((a_u8PaletteBank & SCREEN_ENTRY_PALETTE_BANK_MASK) << 12);//Returns the a u16 that will indicate the changes to be made.
}

//====================================================================================
//Sprites & Object Attribute Memory
//====================================================================================

u16* SpriteTileBlockAddress(u32 a_u32TileNumber)
{
	return (u16*)(VIDEO_RANDOM_ACCESS_MEMORY + (4 * TILE_BLOCK_SIZE) + ((a_u32TileNumber & 0x3FF) * sizeof(TILE)));//Each block is 16KB in size sprites occur on block 4 of tile memory (blocks 0-3 are for background tiles).
}

u16 SetAttribute0(u8 a_u8Y, u8 a_u8ObjectMode, u8 a_u8GraphicsMode, u8 a_u8mosiac, u8 a_u8ColorMode, u8 a_u8Shape)//Sets the attribute 0 of the sprite.
{
	u16 u16Attribute0 = (a_u8Y & ATTRIBUTE0_YMASK) | ((a_u8ObjectMode & 0x3) << 8) | ((a_u8GraphicsMode & 0x3) << 10) |
		((a_u8mosiac & 0x1) << 12) | ((a_u8ColorMode & 0x1) << 13) | ((a_u8Shape & 0x3) << 14);
	return u16Attribute0;
}

u16 SetAttribute1(u8 a_u8X, u8 a_u8Flip, u8 a_u8Size)//Sets the attribute 1 of the sprite.
{
	u16 u16Atribute1 = (a_u8X & ATTRIBUTE1_XMASK) | ((a_u8Flip & ATTRIBUTE1_FLIPMASK) << 12) | ((a_u8Size & 3) << 14);
	return u16Atribute1;
}

void SetAttribute1AffineIndex(ObjectAttribute* a_pObject, u8 a_u8Index)//Sets the attribute 1 affine index  of the sprite.
{
	a_pObject->u16Attribute1 = (a_pObject->u16Attribute1 & 0xC1FF) | ((a_u8Index & ATTRIBUTE1_AFF_INDEX_MASK) << 9);//Use 0xC1FF to strip out bits 9 -> D.
}

u16 SetAttribute2(u8 a_u8TileIndex, u8 a_u8Priority, u8 a_u8PaletteBank)//Sets the attribute 2 of the sprite.
{
	u16 u16Attribute2 = (a_u8TileIndex & 0x3FF) | ((a_u8Priority & 3) << 10) | ((a_u8PaletteBank & 0xF) << 12);
	return u16Attribute2;
}

void SetObjectPosition(ObjectAttribute* a_pObject, u8 a_u8X, u8 a_u8Y)//Sets the position of the sprite.
{
	a_pObject->u16Attribute0 = (a_pObject->u16Attribute0 & 0xFF00) | (a_u8Y  & 0x00FF);
	a_pObject->u16Attribute1 = (a_pObject->u16Attribute1 & 0xFE00) | (a_u8X & 0x01FF);
}

void ObjectHide(ObjectAttribute* a_pObject)//Hide a sprite.
{
	a_pObject->u16Attribute0 = (a_pObject->u16Attribute0 & ATTRIBUTE0_MODE_MASK) | (ATTRIBUTE0_MODE_HIDE << 8);//Object attribute 0 is where the hide flag is located, the argument changes the flag.
}
void ObjectUnhide(ObjectAttribute* a_pObject, u8 a_u8Mode)//Makes the sprite unhidden.
{
	a_pObject->u16Attribute0 = (a_pObject->u16Attribute0 & ATTRIBUTE0_MODE_MASK) | (a_u8Mode& 0x3 << 8);//Object attribute 0 is where the hide flag is located, the argument changes the flag. The mask with the 3 is to make sure we pass in the correct number less than 3.
}
void ObjectAttributeMemoryInitialize(ObjectAttribute* a_pObject, u8 a_u8Count)//Initialize object attribute memory.
{
	u32 u32ResetCount = a_u8Count;
	ObjectAttribute *pDestination = a_pObject;

	// Hide each object
	while (u32ResetCount--)//Whilst resetCount is greater than 0.
	{
		pDestination->u16Attribute0 = 0;//Sets destination attribute0 to 0.
		pDestination->u16Attribute1 = 0;//Sets destination attribute1 to 0.
		pDestination->u16Attribute2 = 0;//Sets destination attribute2 to 0.
		pDestination->s16Padding = 0;//Sets destination padding data to 0.
		ObjectHide(pDestination);//Hide the current object we are pointing at.
		++pDestination;//Point to the next destination in our object attribute space.
	}
	ObjectAttributeMemoryCopy(MEMORY_OBJECT_ATTRIBUTE_MEMORY, a_pObject, a_u8Count);//Initialize object attribute memory.
}

void ObjectAttributeMemoryCopy(ObjectAttribute* a_pDestination, ObjectAttribute* a_pSource, u8 a_u8Count)//Copies the object attribute memory from one place to another.
{
	u32 *pu32Destination = (u32*)a_pDestination, *pu32SourcePointer = (u32*)a_pSource;//Casts the destination pointer and the source pointer into 32 bit integers.
	while (a_u8Count--)//While count is above 0.
	{
		*pu32Destination++ = *pu32SourcePointer++;//Post increment to increment after the assignment operator.
		*pu32Destination++ = *pu32SourcePointer++;//Increments a second time to get the 2nd attribute and the padding data.
	}
}

void ObjectAffineIdentity(ObjectAffine* a_pObject)//Set the affine object matrix to an identity matrix.
{
	a_pObject->s16Pa = 0x01001; a_pObject->s16Pb = 0; a_pObject->s16Pc = 0; a_pObject->s16Pd = 0x0100;//Sets up identity matrix.
}

void ObjectAffineRotationScale(ObjectAffine* a_pObjectAffine, fixed a_fScaleX, fixed a_fScaleY, u16 a_u16Alpha)//Set the rotation and scale of the object uses the sine look up table to retrieve a value for sine & cosine.
{
	u32 sinValue = LookUpSin(a_u16Alpha), cosValue = LookUpCos(a_u16Alpha);//Sets the sin and cos values from putting the argument into the lookup tables.
	a_pObjectAffine->s16Pa = cosValue*a_fScaleX >> 12; 
	a_pObjectAffine->s16Pb = -sinValue*a_fScaleX >> 12;
	a_pObjectAffine->s16Pc = sinValue*a_fScaleY >> 12;
	a_pObjectAffine->s16Pd = cosValue*a_fScaleY >> 12;//Shifts values down 12 to account for fixed point multiply to keep values as .8 fixed.
}