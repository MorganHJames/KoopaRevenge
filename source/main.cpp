//\===========================================================================================
//\ File: main.cpp
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the start point for the game.
//\===========================================================================================

#include "Intellisense.h"
#include "gba.h"
#include <string.h>

#include "player.h"
#include "backgroundFunctions.h"


int main()
{
	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.

	//setupBackground();//setup the background 0.
	setupSprites();//clear all the sprites on screen now 

	Player player;//Create the player.
	//playerInitialize(&player);//Initialize the player

	player.playerSetupSpriteImage();//Setup the sprite image data.	

	//PLayer Initialization.
	player.playerInitialization();

	loadBackground();

	s32 iXScroll = 0;//Set initial scroll to 0.

	while(1)//Loop forever.
	{
		pollKeys();
		player.playerUpdate();//Update the player.

		// now the arrow keys move the koopa 

		REGISTRY_BACKGROUND_OFF_SET->s16X = iXScroll;

		if (keyDown(RIGHT))
		{
			if (player.playerMoveRight())
			{
				iXScroll++;
			}
		}
		else if (keyDown(LEFT))
		{
			if (player.playerMoveLeft())
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