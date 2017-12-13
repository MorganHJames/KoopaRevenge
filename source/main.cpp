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

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | DISPLAYCONTROL_BACKGROUNDMODE_1 | DISPLAYCONTROL_BACKGROUNDMODE_2 | DISPLAYCONTROL_BACKGROUNDMODE_3 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.																						   //set up the BG Control Register
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

	GameStates currentState = GAME;

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

	Text livesText;
	livesText.textInitialization(5, 8);
	livesText.drawText("LIVES", 0, 160, spriteManager, 4);
	Text livesLeftText;
	livesLeftText.textInitialization(1, 8);
	livesLeftText.drawText("3", 0, 160, spriteManager, 4);

	Text scoreText;
	scoreText.textInitialization(5, 8);
	scoreText.drawText("SCORE", 0, 160, spriteManager, 4);

	Text scoreValueText;
	scoreValueText.textInitialization(3, 8);
	scoreValueText.drawText("000", 0, 160, spriteManager, 4);

	Text timeText;
	timeText.textInitialization(4, 8);
	timeText.drawText("TIME", 0, 160, spriteManager, 4);

	Text timeRemainingText;
	timeRemainingText.textInitialization(3, 8);
	timeRemainingText.drawText("300", 0, 160, spriteManager, 4);

	Text startText;
	startText.textInitialization(5, 8);
	startText.drawText("START", 0, 160, spriteManager, 4);

	Text highText;
	highText.textInitialization(4, 8);
	highText.drawText("HIGH", 0, 160, spriteManager, 4);

	Text score2Text;
	score2Text.textInitialization(5, 8);
	score2Text.drawText("SCORE", 0, 160, spriteManager, 4);

	Text highScoreText;
	highScoreText.textInitialization(3, 8);
	highScoreText.drawText("000", 0, 160, spriteManager, 4);

	Delay(TIMER_SECONED);

	switch (currentState)
	{
	case GAME:
	{
		int state = 0;
		int timeLeft = 300;
		int highScore = 0;
		int titleScroll = 90;

		while (1)
		{
			if (state == 0)
			{
				player.sprite->spriteSetPosition(0, 160);
				enemy1.sprite->spriteSetPosition(0, 160);
				enemy2.sprite->spriteSetPosition(0, 160);
				enemy3.sprite->spriteSetPosition(0, 160);
				
				highText.updateText("HIGH", 64, 136, spriteManager, 4);
				score2Text.updateText("SCORE", 104, 136, spriteManager, 4);
				char highScoreCharArray[3] = { '0' + highScore / 100 % 10, '0' + highScore / 10 % 10, '0' + highScore % 10 };
				highScoreText.updateText(highScoreCharArray, 152, 136, spriteManager, 4);

				

				if (titleScroll > -16)
				{
					titleScroll--;

					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = titleScroll;
				}

				pollKeys();

				if (keyDown(START))
				{
					startText.updateText("START", 100, 120, spriteManager, 5);
				}
				else
				{
					startText.updateText("START", 100, 120, spriteManager, 4);

				}
				if (keyReleased(START))
				{
					startText.hideText();
					highText.hideText();
					score2Text.hideText();
					highScoreText.hideText();
					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = 90;
					state = 1;
				}

				verticalSync();
			}

			if (state == 1)
			{
				pollKeys();
			
				
				if (TIMER_1_DATA > 1)
				{
					timeLeft--;
					stopDelay();
					Delay(TIMER_SECONED);
				}
				player.playerUpdate();
				
				enemy1.enemyUpdate(player, enemy2, enemy3);
				enemy2.enemyUpdate(player);
				enemy3.enemyUpdate(player);

				timeText.updateText("TIME", 104, 2, spriteManager, 4);
				char livesLeftCharArray[3] = { '0' + timeLeft / 100 % 10, '0' + timeLeft / 10 % 10, '0' + timeLeft % 10 };
				timeRemainingText.updateText(livesLeftCharArray, 108, 10, spriteManager, 4);
				livesText.updateText("LIVES", 1, 2, spriteManager, 4);
				char livesLeftChar[] = { '0' + player.lives, '\0' };
				livesLeftText.updateText(livesLeftChar, 17, 10, spriteManager, 4);
				scoreText.updateText("SCORE", 199, 2, spriteManager, 4);
				char scoreValueCharArray[3] = { '0' + player.score / 100 % 10, '0' + player.score / 10 % 10, '0' + player.score % 10 };
				scoreValueText.updateText(scoreValueCharArray, 207, 10, spriteManager, 4);

				if (player.lives == 0 || timeLeft == 0)
				{
					timeText.hideText();
					timeRemainingText.hideText();
					scoreValueText.hideText();
					livesLeftText.hideText();
					scoreText.hideText();
					livesText.hideText();

					state = 0;

					for (int i = 0; i < 32; ++i)
					{
						setObjectPosition(&player.jumpParticleOAMStart[i],0 , 160);//Move particle
					}
					

					if (player.score > highScore)
					{
						highScore = player.score;
					}
					player.score = 0;
					player.lives = 3;
					timeLeft = 300;
					titleScroll = 90;
					enemy1.spawnEnemy(player);
					enemy2.spawnEnemy(player);
					enemy3.spawnEnemy(player);
				}
				delay(300);
				verticalSync();
			}
			
		}
		break;
	}
	
	default:
		break;
	}



	return 0;
}