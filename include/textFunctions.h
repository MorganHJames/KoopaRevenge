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

class Text//A class for drawing text to the screen.
{
private:
public:
	u32 u32Length;//How long the word is.
	s32 s32TextSpacing;//How much space there should be between each letter.
	s32 s32TileIndexStart;//The OAM position of the first letter in a word.
	
	void TextInitialization(u32 a_u32Length, s32 a_s32TextSpacing)//Initializes the text variables.
	{
		u32Length = a_u32Length;//Sets length to be equal to the argument passed in.
		s32TextSpacing = a_s32TextSpacing;//Sets text spacing to be equal to the argument passed in.
	}

	void DrawText(char a_cText[], u8 a_u8XPosition, u8 a_u8YPosition , SpriteManager& a_rSpriteManager, u8 a_u8PaletteBank)//Draws text to the screen.
	{
		u8 u8CharacterCode;//The ASCII value of the character.
		u8 u8ObjectTilesPosition = 96;//The start of the alphabet in object tiles.

		for (u32 u32I = 0; u32I < u32Length; u32I++)//For the length of the word.
		{
			u8CharacterCode = (u8)a_cText[u32I];//Set the character code to be equal to the characters.
			
			for (u32 u32J = 0; u32J < textLookUpTableLen; u32J++)//For the length of the text look up table.
			{
				if (u8CharacterCode == textLookUpTable[u32J])//If the character code equals the ASCII value.
				{
					u8ObjectTilesPosition = u32J + 96;//Set the object tile position to be equal to the ASCII value position in the table plus the start of the object tiles alphabet.
					break;//Break out early.
				}
			}

			ObjectAttribute* poObjectCharacter;//Creates an object attribute pointer.
			s32TileIndexStart = a_rSpriteManager.ObjectAttributeMemoryFree();//Sets the tile index start to be equal to the first free OAM spot.
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart];//Sets the object attribute pointer to equal the OAM memory.
			s32TileIndexStart -= u32Length;//Decreases the tile index start by length. 
			poObjectCharacter->u16Attribute0 = SetAttribute0(a_u8YPosition, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);//Set attribute 0 of the character so that it is square and is at the correct y position.
			poObjectCharacter->u16Attribute1 = SetAttribute1(a_u8XPosition + (s32TextSpacing * u32I), 0, ATTRIBUTE1_SIZE_0);//Set attribute 1 of the character so that x position of the character is in the correct position and its size is 0.
			poObjectCharacter->u16Attribute2 = SetAttribute2(768 + u8ObjectTilesPosition, 0, a_u8PaletteBank);//Sets attribute 2 of the character so that has the correct offset in object tiles and is using the correct palette bank.

			u8ObjectTilesPosition = 96;//Set the object tile position back to 96.
		}
	}

	void UpdateText(char a_cText[], u8 a_u8XPosition, u8 a_u8YPosition, SpriteManager& a_rSpriteManager, u8 a_u8PaletteBank)
	{
		u8 u8CharacterCode;//The ASCII value of the character.
		u8 u8ObjectTilesPosition = 96;//The start of the alphabet in object tiles.

		for (u32 u32I = 0; u32I < u32Length; u32I++)//For the length of the word.
		{
			u8CharacterCode = (u8)a_cText[u32I];//Set the character code to be equal to the characters.

			for (u32 u32J = 0; u32J < textLookUpTableLen; u32J++)//For the length of the text look up table.
			{
				if (u8CharacterCode == textLookUpTable[u32J])//If the character code equals the ASCII value.
				{
					u8ObjectTilesPosition = u32J + 96;//Set the object tile position to be equal to the ASCII value position in the table plus the start of the object tiles alphabet.
					break;//Break out early.
				}
			}

			ObjectAttribute* poObjectCharacter;//Creates an object attribute pointer.
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart + u32I + 1];//Sets the object attribute pointer to equal the OAM memory.
			ObjectUnhide(poObjectCharacter, 0);//Reveals the character.
			poObjectCharacter->u16Attribute0 = SetAttribute0(a_u8YPosition, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);//Set attribute 0 of the character so that it is square and is at the correct y position.
			poObjectCharacter->u16Attribute1 = SetAttribute1(a_u8XPosition + (s32TextSpacing * u32I), 0, ATTRIBUTE1_SIZE_0);//Set attribute 1 of the character so that x position of the character is in the correct position and its size is 0.
			poObjectCharacter->u16Attribute2 = SetAttribute2(768 + u8ObjectTilesPosition, 0, a_u8PaletteBank);//Sets attribute 2 of the character so that has the correct offset in object tiles and is using the correct palette bank.

		}
	}

	void HideText()//Hides the text.
	{
		for (u32 u32I = 0; u32I < u32Length; ++u32I)//For all characters in the word.
		{
			ObjectAttribute* poObjectCharacter;//Create an object pointer.
			poObjectCharacter = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[s32TileIndexStart + u32I + 1];//Select the correct OAM.
			ObjectHide(poObjectCharacter);//Hide the sprite.
		}
	}
};

#endif//__TEXT_FUNCTIONS_H__