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
	
	player.playerInitialization();//PLayer Initialization.

	loadBackground();

	while(1)//Loop forever.
	{
		pollKeys();

		player.playerUpdate();//Update the player.

		verticalSync();

		/* delay some */
		delay(200);
	}
	return 0;
}