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
#include "backgroundFunctions.h"
#include "gameStates.h"
#include "text.h"
#include "textFunctions.h"
#include "spriteManager.h"
#include "gameManager.h"

int main()
{
	SplashScreenLoad();

	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | DISPLAYCONTROL_BACKGROUNDMODE_1 | DISPLAYCONTROL_BACKGROUNDMODE_2 | DISPLAYCONTROL_BACKGROUNDMODE_3 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.																						   //set up the BG Control Register
	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;
	setupSprites();//clear all the sprites on screen now 

	SpriteManager spriteManager;
	spriteManager.SpriteManagerInitialization();

	GameManager gameManager;

	Player player;//Create the player.
	player.playerInitialization(spriteManager);//PLayer Initialization.

	Enemy enemy1;//Creates the first enemy.
	enemy1.EnemyInitialization(spriteManager, player);//enemy Initialization.

	Enemy enemy2;//Creates the seconed enemy.
	enemy2.EnemyInitialization(spriteManager, player);//enemy Initialization.

	Enemy enemy3;//Creates the third enemy.
	enemy3.EnemyInitialization(spriteManager, player);//enemy Initialization.
	
	LoadGameBackground();

	GameStates currentState = GAME;

	//payer mem
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(0), koopaPal, koopaPalLen);
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(0), koopaTiles, koopaTilesLen);

	//jump particle mem
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(1), smokePal, smokePalLen);
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(32), smokeTiles, smokeTilesLen);

	//enemy mem
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(2), marioPal, marioPalLen);//mario colours
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(3), luigiPal, luigiPalLen);//luigi  colours
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(64), marioTiles, marioTilesLen);

	//Text mem
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(4), textPal, textPalLen);//text colours
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(5), textAlternatePal, textPalLen);//alternate  colours
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(96), textTiles, textTilesLen);

	Text livesText;
	livesText.textInitialization(5, 8);
	char livesCharArray[5] = { 'L' , 'I' , 'V', 'E', 'S' };
	livesText.drawText(livesCharArray, 0, 160, spriteManager, 4);

	Text livesLeftText;
	livesLeftText.textInitialization(1, 8);
	char livesLeftCharArray[1] = { '3' };
	livesLeftText.drawText(livesLeftCharArray, 0, 160, spriteManager, 4);

	Text scoreText;
	scoreText.textInitialization(5, 8);
	char scoreCharArray[5] = { 'S' , 'C' , 'O', 'R', 'E' };
	scoreText.drawText(scoreCharArray, 0, 160, spriteManager, 4);

	Text scoreValueText;
	scoreValueText.textInitialization(3, 8);
	char scoreValueCharArray[3] = { '0', '0', '0' };
	scoreValueText.drawText(scoreValueCharArray, 0, 160, spriteManager, 4);

	Text timeText;
	timeText.textInitialization(4, 8);
	char timeCharArray[4] = { 'T', 'I', 'M', 'E' };
	timeText.drawText(timeCharArray, 0, 160, spriteManager, 4);

	Text timeRemainingText;
	timeRemainingText.textInitialization(3, 8);
	char timeRemainingCharArray[3] = { '3', '0', '0' };
	timeRemainingText.drawText(timeRemainingCharArray, 0, 160, spriteManager, 4);

	Text startText;
	startText.textInitialization(5, 8);
	char startCharArray[5] = { 'S', 'T', 'A', 'R', 'T' };
	startText.drawText(startCharArray, 0, 160, spriteManager, 4);

	Text highText;
	highText.textInitialization(4, 8);
	char highTCharArray[4] = { 'H', 'I', 'G', 'H' };
	highText.drawText(highTCharArray, 0, 160, spriteManager, 4);

	Text score2Text;
	score2Text.textInitialization(5, 8);
	score2Text.drawText(scoreCharArray, 0, 160, spriteManager, 4);

	Text highScoreText;
	highScoreText.textInitialization(3, 8);
	highScoreText.drawText(scoreValueCharArray, 0, 160, spriteManager, 4);

	Delay(TIMER_SECONED);

	switch (currentState)
	{
	case GAME:
	{
		int state = 0;
		int timeLeft = 300;
		int highScore = 0;
		int titleScroll = 90;
		fixed cloudScroll = 0;
		int i_sinPos = 0;

		while (1)
		{
			if (state == 0)
			{
				player.sprite.spriteSetPosition(0, 160);
				enemy1.oSprite.spriteSetPosition(0, 160);
				enemy2.oSprite.spriteSetPosition(0, 160);
				enemy3.oSprite.spriteSetPosition(0, 160);
				
				highText.updateText(highTCharArray, 64, 136, spriteManager, 4);
				score2Text.updateText(scoreCharArray, 104, 136, spriteManager, 4);
				char highScoreCharArray[3] = { (char)('0' + highScore / 100 % 10), (char)('0' + highScore / 10 % 10), (char)('0' + highScore % 10) };
				highScoreText.updateText(highScoreCharArray, 152, 136, spriteManager, 4);

				i_sinPos++;
				if (i_sinPos == sin_lut_Size)
				{
					i_sinPos = 0;
				}
				cloudScroll = sin_lut[i_sinPos];
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(cloudScroll) + 20;


				if (titleScroll > -16)
				{
					titleScroll--;

					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = titleScroll;
				}
				PollKeys();

				if (KeyDown(START))
				{
					startText.updateText(startCharArray, 100, 120, spriteManager, 5);
				}
				else
				{
					startText.updateText(startCharArray, 100, 120, spriteManager, 4);

				}
				if (KeyReleased(START) )
				{
					startText.hideText();
					highText.hideText();
					score2Text.hideText();
					highScoreText.hideText();
					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = 90;
					state = 1;
				}
				

				VerticalSync();
			}

			if (state == 1)
			{
				PollKeys();

				i_sinPos++;
				if (i_sinPos == sin_lut_Size)
				{
					i_sinPos = 0;
				}
				cloudScroll = sin_lut[i_sinPos];
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(cloudScroll) + 20;
				
				if (TIMER_1_DATA > 1)
				{
					timeLeft--;
					StopDelay();
					Delay(TIMER_SECONED);
				}
				player.playerUpdate();
				
				enemy1.EnemyUpdate(player);
				enemy2.EnemyUpdate(player);
				enemy3.EnemyUpdate(player);
				gameManager.HurtPlayer(player,enemy1,enemy2,enemy3);
				timeText.updateText(timeCharArray, 104, 2, spriteManager, 4);
				char livesLeftCharArray[3] = { (char)('0' + timeLeft / 100 % 10), (char)('0' + timeLeft / 10 % 10),  (char)('0' + timeLeft % 10) };
				timeRemainingText.updateText(livesLeftCharArray, 108, 10, spriteManager, 4);
				livesText.updateText(livesCharArray, 1, 2, spriteManager, 4);
				char livesLeftChar[] = { (char)('0' + player.lives), '\0' };
				livesLeftText.updateText(livesLeftChar, 17, 10, spriteManager, 4);
				scoreText.updateText(scoreCharArray, 199, 2, spriteManager, 4);
				char scoreValueCharArray[3] = { (char)('0' + (player.score / 100 % 10)),  (char)('0' + (player.score / 10 % 10)),  (char)('0' + (player.score % 10)) };
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
						SetObjectPosition(&player.jumpParticleOAMStart[i],0 , 160);//Move particle
					}
					
					if (player.score > highScore)
					{
						highScore = player.score;
					}
					player.score = 0;
					player.lives = 3;
					timeLeft = 300;
					titleScroll = 90;
					enemy1.SpawnEnemy(player);
					enemy2.SpawnEnemy(player);
					enemy3.SpawnEnemy(player);
				}
				DelayNoTimer(300);
				VerticalSync();
			}
			
		}
		break;
	}
	
	default:
		break;
	}



	return 0;
}