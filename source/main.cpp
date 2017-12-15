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
#include "gameStates.h"
#include "text.h"
#include "textFunctions.h"
#include "gameManager.h"
#include "coin.h"

int main()
{
	SplashScreenLoad();//Loads the splash screen.

	REGISTRY_DISPLAYCONTROL = 
		DISPLAYCONTROL_BACKGROUNDMODE_0 | 
		DISPLAYCONTROL_BACKGROUNDMODE_1 | 
		DISPLAYCONTROL_BACKGROUNDMODE_2 | 
		DISPLAYCONTROL_BACKGROUNDMODE_3 | 
		ENABLE_OBJECTS | 
		DISPLAYCONTROL_VIDEOMODE_0
		| MAPPINGMODE_1D;//Set up the BG Control Register.

	TIMER_3_CONTROL = TIMER_ENABLE | TIMER_CASCADE;//Set up timer 3 control.

	SetupSprites();//clear all the sprites on screen now 

	SpriteManager oSpriteManager;//Creates a sprite manager.
	oSpriteManager.SpriteManagerInitialization();//Initialize the sprite manager.

	GameManager oGameManager;//Create a game manager.

	Player oPlayer;//Create the player.
	oPlayer.PlayerInitialization(oSpriteManager);//PLayer Initialization.

	Enemy oEnemy1, oEnemy2, oEnemy3;//Creates the enemies.
	oEnemy1.EnemyInitialization(oSpriteManager, oPlayer);//enemy1 Initialization.

	oEnemy2.EnemyInitialization(oSpriteManager, oPlayer);//enemy2 Initialization.

	oEnemy3.EnemyInitialization(oSpriteManager, oPlayer);//enemy3 Initialization.
	
	LoadGameBackground();//Loads the backgrounds.

	GameStates oGameState = GAME;//Sets the game state to GAME.

	// --- Player Memory ---
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(0), koopaPal, koopaPalLen);//Loads the player palette into memory.
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(0), koopaTiles, koopaTilesLen);//Loads the player tiles into memory.

	// --- Jump Particle Memory ---
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(1), smokePal, smokePalLen);//Loads the jump particle palette into memory.
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(32), smokeTiles, smokeTilesLen);//Loads the jump particle tiles into memory.

	// --- Enemy Memory ---
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(2), marioPal, marioPalLen);//Loads the Mario palette into memory.
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(3), luigiPal, luigiPalLen);//Loads the Luigi palette into memory.
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(64), marioTiles, marioTilesLen);//Loads the enemy tiles into memory.

	// --- Text Memory ---
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(4), textPal, textPalLen);//Loads the default text palette into memory.
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(5), textAlternatePal, textPalLen);//Loads the alternate text palette into memory.
	DirectMemoryAccessWordCopy(SpriteTileBlockAddress(96), textTiles, textTilesLen);//Loads the text tiles into memory.

	// --- Coin Particle Memory ---
	DirectMemoryAccessWordCopy(PaletteSpriteBlockAddress(6), coinPal, coinPalLen);//Loads the coin particle palette into memory.
    DirectMemoryAccessWordCopy(SpriteTileBlockAddress(160), coinTiles, coinTilesLen);//Loads the coin particle tiles into memory.

	Text oLivesText;
	oLivesText.TextInitialization(5, 8);
	char cLivesCharArray[5] = { 'L' , 'I' , 'V', 'E', 'S' };
	oLivesText.DrawText(cLivesCharArray, 0, 160, oSpriteManager, 4);

	Text oLivesLeftText;
	oLivesLeftText.TextInitialization(1, 8);
	char cLivesLeftCharArray[1] = { '3' };
	oLivesLeftText.DrawText(cLivesLeftCharArray, 0, 160, oSpriteManager, 4);

	Text oScoreText;
	oScoreText.TextInitialization(5, 8);
	char cScoreCharArray[5] = { 'S' , 'C' , 'O', 'R', 'E' };
	oScoreText.DrawText(cScoreCharArray, 0, 160, oSpriteManager, 4);

	Text oScoreValueText;
	oScoreValueText.TextInitialization(3, 8);
	char cScoreValueCharArray[3] = { '0', '0', '0' };
	oScoreValueText.DrawText(cScoreValueCharArray, 0, 160, oSpriteManager, 4);

	Text oTimeText;
	oTimeText.TextInitialization(4, 8);
	char cTimeCharArray[4] = { 'T', 'I', 'M', 'E' };
	oTimeText.DrawText(cTimeCharArray, 0, 160, oSpriteManager, 4);

	Text oTimeRemainingText;
	oTimeRemainingText.TextInitialization(3, 8);
	char cTimeRemainingCharArray[3] = { '3', '0', '0' };
	oTimeRemainingText.DrawText(cTimeRemainingCharArray, 0, 160, oSpriteManager, 4);

	Text oStartText;
	oStartText.TextInitialization(5, 8);
	char cStartCharArray[5] = { 'S', 'T', 'A', 'R', 'T' };
	oStartText.DrawText(cStartCharArray, 0, 160, oSpriteManager, 4);

	Text oHighText;
	oHighText.TextInitialization(4, 8);
	char cHighCharArray[4] = { 'H', 'I', 'G', 'H' };
	oHighText.DrawText(cHighCharArray, 0, 160, oSpriteManager, 4);

	Text oScore2Text;
	oScore2Text.TextInitialization(5, 8);
	oScore2Text.DrawText(cScoreCharArray, 0, 160, oSpriteManager, 4);

	Text oHighScoreText;
	oHighScoreText.TextInitialization(3, 8);
	oHighScoreText.DrawText(cScoreValueCharArray, 0, 160, oSpriteManager, 4);

	Delay(TIMER_SECONED);

	switch (oGameState)
	{
	case GAME:
	{
		u8 u8State = 0;
		u16 u16TimeLeft = 300;
		u16 u16HighScore = 0;
		s32 s32TitleScroll = 90;
		fixed fCloudScroll = 0;
		u32 u32SinPosition = 0;

		while (1)
		{
			if (u8State == 0)
			{
				oPlayer.oSprite.SpriteSetPosition(0, 160);
				oEnemy1.oSprite.SpriteSetPosition(0, 160);
				oEnemy2.oSprite.SpriteSetPosition(0, 160);
				oEnemy3.oSprite.SpriteSetPosition(0, 160);
				
				oHighText.UpdateText(cHighCharArray, 64, 136, oSpriteManager, 4);
				oScore2Text.UpdateText(cScoreCharArray, 104, 136, oSpriteManager, 4);
				char cHighScoreCharArray[3] = { (char)('0' + u16HighScore / 100 % 10), (char)('0' + u16HighScore / 10 % 10), (char)('0' + u16HighScore % 10) };
				oHighScoreText.UpdateText(cHighScoreCharArray, 152, 136, oSpriteManager, 4);

				u32SinPosition++;
				if (u32SinPosition == sin_lut_Size)
				{
					u32SinPosition = 0;
				}
				fCloudScroll = sin_lut[u32SinPosition];
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(fCloudScroll) + 20;


				if (s32TitleScroll > -16)
				{
					s32TitleScroll--;

					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = s32TitleScroll;
				}
				PollKeys();

				if (KeyDown(START))
				{
					oStartText.UpdateText(cStartCharArray, 100, 120, oSpriteManager, 5);
				}
				else
				{
					oStartText.UpdateText(cStartCharArray, 100, 120, oSpriteManager, 4);

				}
				if (KeyReleased(START) )
				{
					oStartText.HideText();
					oHighText.HideText();
					oScore2Text.HideText();
					oHighScoreText.HideText();
					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = 90;
					u8State = 1;
				}
				

				VerticalSync();
			}

			if (u8State == 1)
			{
				PollKeys();

				u32SinPosition++;
				if (u32SinPosition == sin_lut_Size)
				{
					u32SinPosition = 0;
				}
				fCloudScroll = sin_lut[u32SinPosition];
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(fCloudScroll) + 20;
				
				if (TIMER_1_DATA > 1)
				{
					u16TimeLeft--;
					StopDelay();
					Delay(TIMER_SECONED);
				}
				oPlayer.PlayerUpdate();
				
				oEnemy1.EnemyUpdate(oPlayer);
				oEnemy2.EnemyUpdate(oPlayer);
				oEnemy3.EnemyUpdate(oPlayer);
				oGameManager.HurtPlayer(oPlayer,oEnemy1,oEnemy2,oEnemy3);
				oTimeText.UpdateText(cTimeCharArray, 104, 2, oSpriteManager, 4);
				char cLivesLeftCharArray[3] = { (char)('0' + u16TimeLeft / 100 % 10), (char)('0' + u16TimeLeft / 10 % 10),  (char)('0' + u16TimeLeft % 10) };
				oTimeRemainingText.UpdateText(cLivesLeftCharArray, 108, 10, oSpriteManager, 4);
				oLivesText.UpdateText(cLivesCharArray, 1, 2, oSpriteManager, 4);
				char cLivesLeftChar[] = { (char)('0' + oPlayer.u8Lives), '\0' };
				oLivesLeftText.UpdateText(cLivesLeftChar, 17, 10, oSpriteManager, 4);
				oScoreText.UpdateText(cScoreCharArray, 199, 2, oSpriteManager, 4);
				char cScoreValueCharArray[3] = { (char)('0' + (oPlayer.u16Score / 100 % 10)),  (char)('0' + (oPlayer.u16Score / 10 % 10)),  (char)('0' + (oPlayer.u16Score % 10)) };
				oScoreValueText.UpdateText(cScoreValueCharArray, 207, 10, oSpriteManager, 4);

				if (oPlayer.u8Lives == 0 || u16TimeLeft == 0)
				{
					oTimeText.HideText();
					oTimeRemainingText.HideText();
					oScoreValueText.HideText();
					oLivesLeftText.HideText();
					oScoreText.HideText();
					oLivesText.HideText();

					u8State = 0;

					for (u32 u32I = 0; u32I < 32; ++u32I)
					{
						SetObjectPosition(&oPlayer.poJumpParticleOAMStart[u32I],0 , 160);//Move particle
					}
					
					if (oPlayer.u16Score > u16HighScore)
					{
						u16HighScore = oPlayer.u16Score;
					}

					oPlayer.u16Score = 0;
					oPlayer.u8Lives = 3;
					u16TimeLeft = 300;
					s32TitleScroll = 90;
					oEnemy1.SpawnEnemy(oPlayer);
					oEnemy2.SpawnEnemy(oPlayer);
					oEnemy3.SpawnEnemy(oPlayer);
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