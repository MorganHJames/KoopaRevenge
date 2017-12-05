//\===========================================================================================
//\ File: game.h
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: 
//\===========================================================================================

#ifndef __GAME_H__
#define __GAME_H__

#include "Intellisense.h"
#include "gba.h"
#include <string.h>
#include "player.h"
#include "backgroundFunctions.h"
#include "gameStates.h"
#include "splash.h"



void splash()
{
	//\===========================================================================================
	//\ SPLASH Setup 
	//\===========================================================================================

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_VIDEOMODE_4 | DISPLAYCONTROL_BACKGROUNDMODE_2;

	directMemoryAccessWordCopy(VIDEO_RANDOM_ACCESS_MEMORY_PAGE, splashBitmap, splashBitmapLen);
	directMemoryAccessWordCopy(PALETTE_BACKGROUND_MEMORY, splashPal, splashPalLen);
	sleep(3, TIMER_SECONED);
}

class Game
{
private:
public:

	//\===========================================================================================
	//\ Initialization
	//\===========================================================================================

	Player player;//Create the player.

	GameState currentState;//Defines the first state of the game.


	void initialize()
	{
		splash();
		REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | DISPLAYCONTROL_BACKGROUNDMODE_1 | DISPLAYCONTROL_BACKGROUNDMODE_2 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.																						   //set up the BG Control Register

		setupSprites();//clear all the sprites on screen now 

		Player player;//Create the player.

		player.playerInitialization();//PLayer Initialization.

		loadGameBackground();

		while (1)//Loop forever.
		{
			pollKeys();

			player.playerUpdate();
			verticalSync();

		}
	}


	

};

#endif //__GAME_H__