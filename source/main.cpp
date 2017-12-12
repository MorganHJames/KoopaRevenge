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
#include "text.h"
#include "textFunctions.h"
#include "spriteManager.h"

int main()
{
	splash();

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | DISPLAYCONTROL_BACKGROUNDMODE_1 | DISPLAYCONTROL_BACKGROUNDMODE_2 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.																						   //set up the BG Control Register
	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;
	setupSprites();//clear all the sprites on screen now 

	SpriteManager spriteManager;

	Player player;//Create the player.
	player.playerInitialization(spriteManager);//PLayer Initialization.

	Enemy enemy1;//Creates the first enemy.
	enemy1.enemyInitialization(spriteManager, player, 1);//enemy Initialization.

	Enemy2 enemy2;//Creates the seconed enemy.
	enemy2.enemyInitialization(spriteManager, player, 2);//enemy Initialization.

	Enemy3 enemy3;//Creates the third enemy.
	enemy3.enemyInitialization(spriteManager, player, 3);//enemy Initialization.

	
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

	//Text mem
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(4), textPal, textPalLen);//text colours
	directMemoryAccessWordCopy(paletteSpriteBlockAddress(5), textAlternatePal, textPalLen);//alternate  colours
	directMemoryAccessWordCopy(spriteTileBlockAddress(96), textTiles, textTilesLen);

	Text lives;
	lives.textInitialization(5, 8);
	lives.drawText("LIVES", 1, 2, spriteManager);
	Text livesLeft;
	livesLeft.textInitialization(1, 8);
	livesLeft.drawText("3", 17, 10, spriteManager);

	Text score;
	score.textInitialization(5, 8);
	score.drawText("SCORE", 199, 2, spriteManager);

	Text scoreValueUnits;
	scoreValueUnits.textInitialization(1, 8);
	scoreValueUnits.drawText("0", 223, 10, spriteManager);

	Text scoreValueTens;
	scoreValueTens.textInitialization(1, 8);
	scoreValueTens.drawText("0", 215, 10, spriteManager);

	Text scoreValueHundreds;
	scoreValueHundreds.textInitialization(1, 8);
	scoreValueHundreds.drawText("0", 207, 10, spriteManager);

	Text time;
	time.textInitialization(4, 8);
	time.drawText("TIME", 104, 2, spriteManager);

	while (1)//Loop forever.
	{
		switch (currentState)
		{

		case MENU:
		{
			pollKeys();


			player.playerUpdate();

			enemy1.enemyUpdate(player, enemy2, enemy3);
			enemy2.enemyUpdate(player);
			enemy3.enemyUpdate(player);


			time.updateText("TIME", 104, 2, spriteManager);

			lives.updateText("LIVES", 1, 2, spriteManager);
			char livesLeftChar[] = { '0' + player.lives, '\0' };
			livesLeft.updateText(livesLeftChar, 17, 10, spriteManager);

			score.updateText("SCORE", 199, 2, spriteManager);

			char scoreValueUnitsChar[] = { '0' + player.scoreUnits, '\0' };
			char scoreValueTensChar[] = { '0' + player.scoreTens, '\0' };
			char scoreValueHundredsChar[] = { '0' + player.scoreHundreds, '\0' }; 

			scoreValueUnits.updateText(scoreValueUnitsChar, 223, 10, spriteManager);
			scoreValueTens.updateText(scoreValueTensChar, 215, 10, spriteManager);
			scoreValueHundreds.updateText(scoreValueHundredsChar, 207, 10, spriteManager);


			verticalSync();

		}


		default:
			break;
		}
		

	}
	return 0;
}