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
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "backgroundFunctions.h"
#include "gameStates.h"

int main()
{
	splash();

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | DISPLAYCONTROL_BACKGROUNDMODE_1 | DISPLAYCONTROL_BACKGROUNDMODE_2 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.																						   //set up the BG Control Register
	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;
	setupSprites();//clear all the sprites on screen now 

	Player player;//Create the player.

	Enemy enemy1;//Creates the first enemy.
	Enemy2 enemy2;//Creates the seconed enemy.
	Enemy3 enemy3;//Creates the third enemy.
	enemy1.enemyInitialization(player, 65);//enemy Initialization.
	enemy2.enemyInitialization(player, 66);//enemy Initialization.
	enemy3.enemyInitialization(player, 67);//enemy Initialization.
	player.playerInitialization();//PLayer Initialization.

	loadGameBackground();

	GameStates currentState = MENU;

	//payer mem
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(0), koopaPal, koopaPalLen);
	directMemoryAccessWordCopy(spriteTileBlockAddress(0), koopaTiles, koopaTilesLen);

	//jump particle mem
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(1), smokePal, smokePalLen);
	directMemoryAccessWordCopy(spriteTileBlockAddress(32), smokeTiles, smokeTilesLen);

	//enemy mem
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(2), marioPal, marioPalLen);//mario colours
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(3), luigiPal, luigiPalLen);//luigi  colours
	directMemoryAccessWordCopy(spriteTileBlockAddress(64), marioTiles, marioTilesLen);

	while (1)//Loop forever.
	{
		switch (currentState)
		{

		case MENU:
		{

			pollKeys();

			player.playerUpdate();

			
			enemy2.enemyUpdate(player);
			enemy3.enemyUpdate(player);
			enemy1.enemyUpdate(player, enemy2, enemy3);

			verticalSync();

		}


		default:
			break;
		}
		

	}
	return 0;
}