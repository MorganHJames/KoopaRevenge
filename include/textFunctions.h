//\===========================================================================================
//\ File: textFunctions.h
//\ Author: Morgan James
//\ Date Created: 11/12/2017
//\ Brief:
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
	int length;
	int textSpacing;
	int tileIndexStart;
	
	void textInitialization(int a_length, int a_textSpacing)
	{
		length = a_length;
		textSpacing = a_textSpacing;
	}

	void drawText(char a_text[], u8 a_xPos, u8 a_yPos , SpriteManager& a_spriteManager, u8 a_paletteBank)
	{
		u8 characterCode;
		u8 objectTilesPosition = 96;

		for (u8 i = 0; i < length; i++)
		{
			characterCode = (u8)a_text[i];
			
			for (u8 j = 0; j < textLookUpTableLen; j++)
			{
				if (characterCode == textLookUpTable[j])
				{
					objectTilesPosition = j + 96;
					break;
				}
			}

			ObjectAttribute* objectCharacter;
			tileIndexStart = a_spriteManager.objectAttributeMemoryFree();
			objectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[tileIndexStart];
			tileIndexStart = tileIndexStart - length;
			objectCharacter->u16Attribute0 = SetAttribute0(a_yPos, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
			objectCharacter->u16Attribute1 = SetAttribute1(a_xPos + (textSpacing * i), 0, ATTRIBUTE1_SIZE_0);
			objectCharacter->u16Attribute2 = SetAttribute2(768 + objectTilesPosition, 0, a_paletteBank);

			objectTilesPosition = 96;
		}
	}

	void updateText(char a_text[], u8 a_xPos, u8 a_yPos, SpriteManager& a_spriteManager, u8 a_paletteBank)
	{
		u8 characterCode;
		u8 objectTilesPosition = 96;

		for (u8 i = 0; i < length; ++i)
		{
			characterCode = (u8)a_text[i];

			for (u8 j = 0; j < textLookUpTableLen; ++j)
			{
				if (characterCode == textLookUpTable[j])
				{
					objectTilesPosition = j + 96;
					break;
				}
			}

			ObjectAttribute* objectCharacter;
			objectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[tileIndexStart + i + 1];
			ObjectUnhide(objectCharacter, 0);
			objectCharacter->u16Attribute0 = SetAttribute0(a_yPos, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
			objectCharacter->u16Attribute1 = SetAttribute1(a_xPos + (textSpacing * i), 0, ATTRIBUTE1_SIZE_0);
			objectCharacter->u16Attribute2 = SetAttribute2(768 + objectTilesPosition, 0, a_paletteBank);
		}
	}
	void hideText()
	{
		for (u8 i = 0; i < length; ++i)
		{
			ObjectAttribute* objectCharacter;
			objectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[tileIndexStart + i + 1];
			ObjectHide(objectCharacter);
		}
	}
};

#endif//__TEXT_FUNCTIONS_H__