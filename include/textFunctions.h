//\===========================================================================================
//\ File: textFunctions.h
//\ Author: Morgan James
//\ Date Created: 11/12/2017
//\ Brief: A header that contains the class declaration and prototypes for the Text that will appear on screen.
//\===========================================================================================

#ifndef __TEXT_FUNCTIONS_H__
#define __TEXT_FUNCTIONS_H__

#include "gba_types.h"
#include "textLookUpTable.h"
#include "sprite.h"

class Text
{
private:
public:
	u32 u32Length;
	s32 s32TextSpacing;
	s32 s32TileIndexStart;
	
	void TextInitialization(u32 a_u32Length, s32 a_s32TextSpacing)
	{
		u32Length = a_u32Length;
		s32TextSpacing = a_s32TextSpacing;
	}

	void DrawText(char a_cText[], u8 a_u8XPosition, u8 a_u8YPosition , SpriteManager& a_rSpriteManager, u8 a_u8PaletteBank)
	{
		u8 u8CharacterCode;
		u8 u8ObjectTilesPosition = 96;

		for (u32 u32I = 0; u32I < u32Length; u32I++)
		{
			u8CharacterCode = (u8)a_cText[u32I];
			
			for (u32 u32J = 0; u32J < textLookUpTableLen; u32J++)
			{
				if (u8CharacterCode == textLookUpTable[u32J])
				{
					u8ObjectTilesPosition = u32J + 96;
					break;
				}
			}

			ObjectAttribute* poObjectCharacter;
			s32TileIndexStart = a_rSpriteManager.ObjectAttributeMemoryFree();
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart];
			s32TileIndexStart = s32TileIndexStart - u32Length;
			poObjectCharacter->u16Attribute0 = SetAttribute0(a_u8YPosition, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
			poObjectCharacter->u16Attribute1 = SetAttribute1(a_u8XPosition + (s32TextSpacing * u32I), 0, ATTRIBUTE1_SIZE_0);
			poObjectCharacter->u16Attribute2 = SetAttribute2(768 + u8ObjectTilesPosition, 0, a_u8PaletteBank);

			u8ObjectTilesPosition = 96;
		}
	}

	void UpdateText(char a_cText[], u8 a_u8XPosition, u8 a_u8YPosition, SpriteManager& a_rSpriteManager, u8 a_u8PaletteBank)
	{
		u8 u8CharacterCode;
		u8 u8ObjectTilesPosition = 96;

		for (u32 u32I = 0; u32I < u32Length; ++u32I)
		{
			u8CharacterCode = (u8)a_cText[u32I];

			for (u32 u32J = 0; u32J < textLookUpTableLen; ++u32J)
			{
				if (u8CharacterCode == textLookUpTable[u32J])
				{
					u8ObjectTilesPosition = u32J + 96;
					break;
				}
			}

			ObjectAttribute* poObjectCharacter;
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart + u32I + 1];
			ObjectUnhide(poObjectCharacter, 0);
			poObjectCharacter->u16Attribute0 = SetAttribute0(a_u8YPosition, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
			poObjectCharacter->u16Attribute1 = SetAttribute1(a_u8XPosition + (s32TextSpacing * u32I), 0, ATTRIBUTE1_SIZE_0);
			poObjectCharacter->u16Attribute2 = SetAttribute2(768 + u8ObjectTilesPosition, 0, a_u8PaletteBank);
		}
	}

	void HideText()
	{
		for (u32 u32I = 0; u32I < u32Length; ++u32I)
		{
			ObjectAttribute* poObjectCharacter;
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart + u32I + 1];
			ObjectHide(poObjectCharacter);
		}
	}
};

#endif//__TEXT_FUNCTIONS_H__