//\===========================================================================================
//\ File: main.cpp
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the start point for the game.
//\===========================================================================================

#include "Intellisense.h"
#include "gba.h"
#include <string.h>

#include "Player.h"
#include "backgroundFunctions.h"


int main()
{
	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.

	//setupBackground();//setup the background 0.
	setupSprites();//clear all the sprites on screen now 

	struct Player player;//Create the player.
	//playerInitialize(&player);//Initialize the player

	playerSetupSpriteImage();//Setup the sprite image data.	

	//PLayer Initialization.
	{
		playerInitialization(&player);
		player.sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[0];
		player.sprite->Attribute->attribute0 = setAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);
		player.sprite->Attribute->attribute1 = setAttribute1(120, 0, ATTRIBUTE1_SIZE_2);
		player.sprite->Attribute->attribute2 = setAttribute2(0, 0, 0);
	}

	loadBackground();

	s32 iXScroll = 0;//Set initial scroll to 0.

	while(1)//Loop forever.
	{
		pollKeys();
		playerUpdate(&player);//Update the player.

		// now the arrow keys move the koopa 

		REGISTRY_BACKGROUND_OFF_SET->s16X = iXScroll;

		if (keyHeld(RIGHT))
		{
			if (playerMoveRight(&player))
			{
				iXScroll++;
			}
		}
		else if (keyHeld(LEFT))
		{
			if (playerMoveLeft(&player))
			{
				iXScroll--;
			}
		}

		verticalSync();

		/* delay some */
		delay(200);

	}

	return 0;
}