//\===========================================================================================
//\ File: gba_graphics.h
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the defines and functions to present graphics to the screen.
//\===========================================================================================

#ifndef __GBA_GRAPHICS_H__
#define __GBA_GRAPHICS_H__

#include "Intellisense.h"
#include "gba_registry.h"
#include "gba_types.h"
#include "gba_math.h"

//\===========================================================================================
//\ Defines For Display Control
//\===========================================================================================

#define REGISTRY_DISPLAYCONTROL							 *((vu32*)(REGISTRY_BASE))//Base address pointer for base register.

// --- Video Modes ---
#define DISPLAYCONTROL_VIDEOMODE_0					     0x0000//Mode 0; backgrounds 0-4: register. 
#define DISPLAYCONTROL_VIDEOMODE_1					     0x0001//Mode 1; backgrounds 0-1: register; background 2: affine.
#define DISPLAYCONTROL_VIDEOMODE_2					     0x0002//Mode 2; backgrounds 2-2: affine.
#define DISPLAYCONTROL_VIDEOMODE_3					     0x0003//Mode 3; background 2: 240x160\@16 bitmap.
#define DISPLAYCONTROL_VIDEOMODE_4					     0x0004//Mode 4; background 2: 240x160\@8 bitmap.
#define DISPLAYCONTROL_VIDEOMODE_5					     0x0005//Mode 5; background 2: 160x128\@16 bitmap.
													     
// --- Layers ---									     									     
#define DISPLAYCONTROL_BACKGROUNDMODE_0				     0x0100//Enable background mode 0.
#define DISPLAYCONTROL_BACKGROUNDMODE_1				     0x0200//Enable background mode 1.
#define DISPLAYCONTROL_BACKGROUNDMODE_2				     0x0400//Enable background mode 2.
#define DISPLAYCONTROL_BACKGROUNDMODE_3				     0x0800//Enable background mode 3.
#define DISPLAYCONTROL_OBJECT						     0x1000//Enable objects.
														
// --- Windows ---									     												     
#define DISPLAYCONTROL_WINDOW_0						     0x2000//Enable window 0.
#define DISPLAYCONTROL_WINDOW_1						     0x4000//Enable window 1.
#define DISPLAYCONTROL_WINDOW_OBJ						 0x8000//Enable object window.

// --- Controls ---						
#define DISPLAYCONTROL_GB								 0x0008//(R) GBC indicator.
#define DISPLAYCONTROL_PAGE_INDICATOR					 0x0010//Page indicator.
#define DISPLAYCONTROL_OBJECT_ATTRIBUTE_MEMORY_HBL		 0x0020//Allow OAM updates in HBlank
#define DISPLAYCONTROL_OBJECT_VIDEO_MEMORY_2D_MATRIX	 0//OBJ-VRAM as matrix
#define DISPLAYCONTROL_OBJECT_VIDEO_MEMORY_1D_ARRAY	     0x0040//OBJ-VRAM as array
#define DISPLAYCONTROL_FORCE_SCREEN_BLANK			     0x0080//Force screen blank

//\===========================================================================================
//\ Vertical Blank Testing Function
//\===========================================================================================

#define REGISTRY_VERTICAL_COUNT                         (*(vu16*)(REGISTRY_BASE + 0x06))//Vertical count is used for testing for vertical blank.

extern void verticalSync();//A function to allow for the drawing to be done on the vertical blank.

//\===========================================================================================
//\ Functionality For Setting Up Page Flipping In Bitmap Rendering Modes
//\===========================================================================================

#define VIDEO_RANDOM_ACCESS_MEMORY_PAGE_INDICATOR		0x0010//Page indicator.

#define VIDEO_RANDOM_ACCESS_MEMORY_PAGE_SIZE			0x0A000//How large the VRAM page is.
#define VIDEO_RANDOM_ACCESS_MEMORY_BACK					(VIDEO_RANDOM_ACCESS_MEMORY + VIDEO_RANDOM_ACCESS_MEMORY_PAGE_SIZE)//The end of the memory address for VRAM.

#define VIDEO_RANDOM_ACCESS_MEMORY_PAGE					((u16*)VIDEO_RANDOM_ACCESS_MEMORY)//The start of VRAM.
#define VIDEO_RANDOM_ACCESS_MEMORY_PAGE_FRONT			((u16*)VIDEO_RANDOM_ACCESS_MEMORY)//The start of VRAM.
#define VIDEO_RANDOM_ACCESS_MEMORY_PAGE_BACK			((u16*)VIDEO_RANDOM_ACCESS_MEMORY_BACK)//The end of VRAM.

extern u16* videoPage;//The current state of the video page.

extern u16* pageFlip();//A function to flip the screen from the back page to the front and vice versa.

//\===========================================================================================
//\ Control Register Defines For Background Tiled Rendering
//\===========================================================================================

#define BACKGROUND_CONTROL_ENABLE_OBJECTS		        0x1000//Enables objects in the background.
#define BACKGROUND_CONTROL_MAPPINGMODE_1D_ARRAY		    0x0040//Enables mapping mode 1D(array) for the background.
													    
#define REGISTRY_BACKGROUND_CONTROL					    ((vu16*)(REGISTRY_BASE+0x0008))//Define for a base registry address for the background controllers.
//accessing this as REG_BGCNT[0] is controller 0
//accessing this as REG_BGCNT[1] is controller 1 or memory address REG_BGCNT + (sizeof(vu16) * 1) = 0x0400:000A
//accessing this as REG_BGCNT[2] is controller 2 or memory address REG_BGCNT + (sizeof(vu16) * 2) = 0x0400:000C
//accessing this as REG_BGCNT[3] is controller 3 or memory address REG_BGCNT + (sizeof(vu16) * 3) = 0x0400:000E

typedef struct BackgroundOffsets//Structure to control background offset x & y flags.
{
	s16 s16X, s16Y;//The x and y offset for the background.
}__attribute__((packed, aligned(4))) BGOffset;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.

#define REGISTRY_BACKGROUND_OFF_SET					   ((BackgroundOffsets*)(REGISTRY_BASE+0x0010))//Define for REG_BG_OFS accessed as an array to access offset data for background modes 0-3. 
//[1].x accesses x .y accesses y value

#define TILE_BLOCK_SIZE								   0x4000//The size of a tile block.
#define TILE_MAP_BLOCK_SIZE							   0x0800//The size of a tile map block.
													   
// --- Background Controls ---						   
#define BACKGROUND_COTNROL_PRIORITY_MASK			   0x3//Indicates the current priority mask.
#define BACKGROUND_COTNROL_TILE_BLOCK_ID_MASK		   0x3//Indicates the current tile block ID mask.
#define BACKGROUND_COTNROL_MOSIAC_MASK				   0x1//Indicates whether or not to use mosaic tiling.
#define BACKGROUND_COTNROL_COLOR_MASK				   0x1//Defines whether we are in 4bit or 8bit color.
#define BACKGROUND_COTNROL_TILE_MAP_ID_MASK			   0x1F//Indicates the current tile map out of 32 options.
#define BACKGROUND_COTNROL_AFINE_WRAP_MASK			   0x1//Indicates If the affine will wrap around or not.
#define BACKGROUND_COTNROL_SIZE_MASK				   0x3//Indicates which of the four sizes the background will be.
													   
// --- Background Registry Sizes ---				   
#define BACKGROUND_REGISTRY_SIZE_32x32				   0x0//Size for background 32x32 using a non-affine mode.
#define BACKGROUND_REGISTRY_SIZE_64x32				   0x1//Size for background 64x32 using a non-affine mode.
#define BACKGROUND_REGISTRY_SIZE_32x64				   0x2//Size for background 32x64 using a non-affine mode.
#define BACKGROUND_REGISTRY_SIZE_64x64				   0x3//Size for background 64x64 using a non-affine mode.

extern u16* tileBlockAddress(u32 a_u32BlockNum);//Function to return the memory address (pointer) to one of the four tile block locations (0-3).

extern u16* tileMapBlockAddress(u32 a_u32BlockNum);//Function to return a pointer to address space for the tile map blocks location (0-31).

extern void setBackgroundControlRegister(u8 a_u8RegNum, u8 a_u8Priority, u8 a_u8TileBlockID, u8 a_u8Mosaic, u8 a_u8ColorMode, u8 a_u8MapBlockID, u8 a_u8AffineWrap, u8 a_u8BackgroundSize);//Function to set a background control register's values.

//\===========================================================================================
//\ Defines For Palette Locations
//\===========================================================================================

#define PALETTE_SIZE					256//Palette is always 256 colors.
#define MEMORY_PALETTE					0x05000000//The memory address for the palette locations.
#define PALETTE_BACKGROUND_MEMORY		((u16*)MEMORY_PALETTE)//The palette background memory.
#define PALETTE_SPRITE_MEMORY			((u16*)(MEMORY_PALETTE + 0x200))//The sprite pallet memory.

//\===========================================================================================
//\ Defines And Functionality For Sprites & Object Attribute Memory
//\===========================================================================================

// --- Defines and structures to map tiles in to memory blocks ---
typedef struct TILE 
{ 
	u32 data[8];//4 bits per pixel 8x8 tile structure.
}__attribute__((packed, aligned(4)))TILE, TILE4;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.

typedef struct TILE8//8 bits per pixel 8x8 tile structure. 
{ 
	u32 data[16]; 
}__attribute__((packed, aligned(4)))TILE8;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.

typedef TILE TILEBLOCK[512];//A collection of tiles that use 4 bits per pixel.
typedef TILE8 TILEBLOCK8[256];//A collection of tiles that use 8 bits per pixel.

#define TILEBLOCK_MEMORY	 ((TILEBLOCK*)0x06000000)//Where the 4 bits per pixel tile block memory is located.
#define TILEBLOCK8_MEMORY	 ((TILEBLOCK8*)0x06000000)//Where the 8 bits per pixel tile block memory is located.

#define ENABLE_OBJECTS		 0x1000//Sets a flag in video IO to use sprites.
#define MAPPINGMODE_1D		 0x40//Sets a flag in video IO to read the sprites from and array.

typedef struct ObjectAttribute//A structure that makes up a sprite.
{
	u16 attribute0;//The first attribute of the sprite.
	u16 attribute1;//The second attribute of the sprite.
	u16 attribute2;//The third attribute of the sprite.
	s16 padding;//The padding for the structure.
}__attribute__((packed, aligned(4)))ObjectAttribute;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.

typedef struct ObjectAffine//A structure for a sprite that can have affine transformations applied to it.
{
	u16 fill0[3];//The first fill for the structure.
	s16 pa;//8.8 fixed point numbers that form the actual matrix.
	u16 fill1[3];//The second fill for the structure.
	s16 pb;//8.8 fixed point numbers that form the actual matrix.
	u16 fill2[3];//The third fill for the structure.
	s16 pc;//8.8 fixed point numbers that form the actual matrix.
	u16 fill3[3];//The fourth fill for the structure.
	s16 pd;//8.8 fixed point numbers that form the actual matrix.
}__attribute__((packed, aligned(4)))ObjectAffine;//Data structure padding. So the computer reads the correct data as computers read in word sized chunks.

#define NUMBER_SPRITES		128//There are 128 sprites on the GBA.

extern ObjectAttribute	objectBuffer[128];//The buffer in which all sprites would be contained within.
extern ObjectAffine		*const objectAffineBuffer;//The buffer in which all affine sprites would be contained within.

#define MEMORY_OBJECT_ATTRIBUTE_MEMORY  ((ObjectAttribute*) 0x07000000)//Memory address for object attribute memory.
#define MEMORY_AFFINE_OBJECT_ATTRIBUTE_MEMORY ((ObjectAffine*) 0x07000000)//Memory address for affine object attribute memory.

//\===========================================================================================
//\ Attribute 0 Defines
//\===========================================================================================

#define ATTRIBUTE0_YMASK				0xFF//Attribute 0 Y mask.
#define ATTRIBUTE0_MODE_MASK			0xFCFF//Attribute 0 mode mask.

#define ATTRIBUTE0_MODE_REGULAR			0x00//Attribute 0 object mode regular.
#define ATTRIBUTE0_MODE_AFFINE			0x01//Attribute 0 object mode affine.
#define ATTRIBUTE0_MODE_HIDE			0x02//Attribute 0 object mode hide.
#define ATTRIBUTE0_MODE_AFFINE_DOUBLE	0x03//Attribute 0 object mode affine double.

#define ATTRIBUTE0_COLOR_4BPP			0x0//Attribute 0 color mode 4 bits per pixel.
#define ATTRIBUTE0_COLOR_8BPP			0x1//Attribute 0 color mode 8 bits per pixel.

#define ATTRIBUTE0_SQUARE				0x00//Attribute 0 sprite shape square.
#define ATTRIBUTE0_WIDE					0x01//Attribute 0 sprite shape wide.
#define ATTRIBUTE0_TALL					0x02//Attribute 0 sprite shape tall.

//\===========================================================================================
//\ Attribute 1 Defines
//\===========================================================================================

#define ATTRIBUTE1_XMASK 0x1FF			//Attribute 1 X mask.
#define ATTRIBUTE1_FLIPMASK 0x3			//Attribute 1 flip mask.
#define ATTRIBUTE1_SIZE_0 0x00			//Attribute 1 size 0.
#define ATTRIBUTE1_SIZE_1 0x01			//Attribute 1 size 1.
#define ATTRIBUTE1_SIZE_2 0x02			//Attribute 1 size 2.
#define ATTRIBUTE1_SIZE_3 0x03			//Attribute 1 size 3.
#define ATTRIBUTE1_AFF_INDEX_MASK 0x1F	//Attribute 1 affine index mask.

//\===========================================================================================
//\ Set Attributes Functions
//\===========================================================================================

extern u16 setAttribute0(u8 a_u8Y, u8 a_u8ObjectMode, u8 a_u8GfxMode, u8 a_u8mosiac, u8 a_u8ColorMode, u8 a_u8Shape);//Sets the attribute 0 of the sprite.
extern u16 setAttribute1(u8 a_u8X, u8 a_u8Flip, u8 a_u8Size);//Sets the attribute 1 of the sprite.
extern void setAttribute1AffineIndex(ObjectAttribute* a_oaObject, u8 a_u8Index);//Sets the attribute 1 affine index  of the sprite.
extern u16 setAttribute2(u8 a_u8TileIndex, u8 a_u8Priority, u8 a_u8PaletteBank);//Sets the attribute 2 of the sprite.

//\===========================================================================================
//\ Object Functions
//\===========================================================================================

extern void setObjectPosition(ObjectAttribute* a_oaObject, u8 a_u8X, u8 a_u8Y);//Sets the position of the sprite.
extern void objectHide(ObjectAttribute* a_oaObject);//Hide a sprite.
extern void objectUnhide(ObjectAttribute* a_oaObject, u8 a_u8Mode);//Makes the sprite unhidden.
extern void objectAttributeMemoryInitialize(ObjectAttribute* a_oaObject, u8 a_u8Count);//Initialize object attribute memory.
extern void objectAttributeMemoryCopy(ObjectAttribute* a_oaDestination, ObjectAttribute* a_oaSource, u8 a_u8Count);//Copies the object attribute memory from one place to another.
extern void objectAffineIdentity(ObjectAffine* a_oaObject);//Set the affine object matrix to an identity matrix.
extern void objectAffineRotationScale(ObjectAffine* a_oaObjectAffine, fixed a_fScaleX, fixed a_fScaleY, u16 a_u16Alpha);//Set the rotation and scale of the object uses the sine look up table to retrieve a value for sine & cosine.	

#endif//__GBA_GRAPHICS_H__