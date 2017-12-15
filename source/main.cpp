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

	Text oLivesText;//Creates a text object.
	oLivesText.TextInitialization(5, 8);//Initializes the text object.
	char cLivesCharArray[5] = { 'L' , 'I' , 'V', 'E', 'S' };//Creates a character array that contains the characters to be displayed.
	oLivesText.DrawText(cLivesCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oLivesLeftText;//Creates a text object.
	oLivesLeftText.TextInitialization(1, 8);//Initializes the text object.
	char cLivesLeftCharArray[1] = { '3' };//Creates a character array that contains the characters to be displayed.
	oLivesLeftText.DrawText(cLivesLeftCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oScoreText;//Creates a text object.
	oScoreText.TextInitialization(5, 8);//Initializes the text object.
	char cScoreCharArray[5] = { 'S' , 'C' , 'O', 'R', 'E' };//Creates a character array that contains the characters to be displayed.
	oScoreText.DrawText(cScoreCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oScoreValueText;//Creates a text object.
	oScoreValueText.TextInitialization(3, 8);//Initializes the text object.
	char cScoreValueCharArray[3] = { '0', '0', '0' };//Creates a character array that contains the characters to be displayed.
	oScoreValueText.DrawText(cScoreValueCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oTimeText;//Creates a text object.
	oTimeText.TextInitialization(4, 8);//Initializes the text object.
	char cTimeCharArray[4] = { 'T', 'I', 'M', 'E' };//Creates a character array that contains the characters to be displayed.
	oTimeText.DrawText(cTimeCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oTimeRemainingText;//Creates a text object.
	oTimeRemainingText.TextInitialization(3, 8);//Initializes the text object.
	char cTimeRemainingCharArray[3] = { '3', '0', '0' };//Creates a character array that contains the characters to be displayed.
	oTimeRemainingText.DrawText(cTimeRemainingCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oStartText;//Creates a text object.
	oStartText.TextInitialization(5, 8);//Initializes the text object.
	char cStartCharArray[5] = { 'S', 'T', 'A', 'R', 'T' };//Creates a character array that contains the characters to be displayed.
	oStartText.DrawText(cStartCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oHighText;//Creates a text object.
	oHighText.TextInitialization(4, 8);//Initializes the text object.
	char cHighCharArray[4] = { 'H', 'I', 'G', 'H' };//Creates a character array that contains the characters to be displayed.
	oHighText.DrawText(cHighCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Text oHighScoreText;//Creates a text object.
	oHighScoreText.TextInitialization(3, 8);//Initializes the text object.
	oHighScoreText.DrawText(cScoreValueCharArray, 0, 160, oSpriteManager, 4);//Draws text to the screen.

	Delay(TIMER_SECONED);//Starts the delay timer for the timer.

	switch (oGameState)//Changes depending on the game state.
	{
	case GAME://If the game state is GAME.
	{
		u8 u8State = 0;//A state to determine if the game should display the title screen or not.
		u16 u16TimeLeft = 300;//How long the player has left.
		u16 u16HighScore = 0;//The highest score a user has gotten since turning the game boy on.
		s32 s32TitleScroll = 90;//The starting y offset for the title.
		fixed fCloudScroll = 0;//The value of the sin look up table.
		u32 u32SinPosition = 0;//The position through the sin look up table.

		while (1)//Loop.
		{
			if (u8State == 0)//If the state equals 0.
			{
				oPlayer.oSprite.SpriteSetPosition(0, 160);//Moves sprite off screen.
				oEnemy1.oSprite.SpriteSetPosition(0, 160);//Moves sprite off screen.
				oEnemy2.oSprite.SpriteSetPosition(0, 160);//Moves sprite off screen.
				oEnemy3.oSprite.SpriteSetPosition(0, 160);//Moves sprite off screen.
				
				oHighText.UpdateText(cHighCharArray, 64, 136, oSpriteManager, 4);//Update the "high" text.
				oScoreText.UpdateText(cScoreCharArray, 104, 136, oSpriteManager, 4);//Update the "score" text.
				char cHighScoreCharArray[3] = { (char)('0' + u16HighScore / 100 % 10), (char)('0' + u16HighScore / 10 % 10), (char)('0' + u16HighScore % 10) };//Creates a character array that contains the characters to be displayed.
				oHighScoreText.UpdateText(cHighScoreCharArray, 152, 136, oSpriteManager, 4);//Update the value the high score text.

				u32SinPosition++;//Increment the position through the sin look up table.

			    // --- Clamping the iterator ---
				if (u32SinPosition == sin_lut_Size)//If the sin iterator is at the end of the look up table.
				{
					u32SinPosition = 0;//Set the sin iterator back to 0.
				}

				fCloudScroll = sin_lut[u32SinPosition];//Set cloud scroll to be equal to the sin value.
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(fCloudScroll) + 20;//Set the y offset of the clouds to be equal to sin.

				if (s32TitleScroll > -16)//If the title is not at the correct position.
				{
					s32TitleScroll--;//Move the title down.

					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = s32TitleScroll;//Set the y off set of the title.
				}

				PollKeys();//Poll the keys to see what is being pressed.

				if (KeyDown(START))//If start is being held.
				{
					oStartText.UpdateText(cStartCharArray, 100, 120, oSpriteManager, 5);//Change the palette of the "start" text to the alternative one.
				}
				else//If start is not being held.
				{
					oStartText.UpdateText(cStartCharArray, 100, 120, oSpriteManager, 4);//Update the "start" text with the default palette.

				}
				if (KeyReleased(START))//If the start key is released.
				{
					oStartText.HideText();//Hide the "start" text.
					oHighText.HideText();//Hide the "high" text.
					oHighScoreText.HideText();//Hide the high score text.
					REGISTRY_BACKGROUND_OFF_SET[3].s16Y = 90;//Set the title y offset to be that of one of which is off screen.
					u8State = 1;//Change the state of game.
				}

				VerticalSync();//Only make changes to the screen during the vertical blank.
			}

			if (u8State == 1)//If the state is equal to 1.
			{
				PollKeys();//Poll the keys to see what the use is pressing.

				// --- Clamping the iterator ---
				if (u32SinPosition == sin_lut_Size)//If the sin iterator is at the end of the look up table.
				{
					u32SinPosition = 0;//Set the sin iterator back to 0.
				}

				fCloudScroll = sin_lut[u32SinPosition];//Set cloud scroll to be equal to the sin value.
				REGISTRY_BACKGROUND_OFF_SET[2].s16Y = FixedToInteger(fCloudScroll) + 20;//Set the y offset of the clouds to be equal to sin.
				
				if (TIMER_1_DATA > 1)//Every second.
				{
					u16TimeLeft--;//Decrease the time left.
					StopDelay();//Stop the delay.
					Delay(TIMER_SECONED);//Restart the delay.
				}

				oPlayer.PlayerUpdate();//Update the player.
				
				oEnemy1.EnemyUpdate(oPlayer);//Update the enemy.
				oEnemy2.EnemyUpdate(oPlayer);//Update the enemy.
				oEnemy3.EnemyUpdate(oPlayer);//Update the enemy.
				
				oGameManager.HurtPlayer(oPlayer,oEnemy1,oEnemy2,oEnemy3);//Check to see if the player is being hurt.
				oTimeText.UpdateText(cTimeCharArray, 104, 2, oSpriteManager, 4);//Update the "time" text.
				char cLivesLeftCharArray[3] = { (char)('0' + u16TimeLeft / 100 % 10), (char)('0' + u16TimeLeft / 10 % 10),  (char)('0' + u16TimeLeft % 10) };//Creates a character array that contains the characters to be displayed.
				oTimeRemainingText.UpdateText(cLivesLeftCharArray, 108, 10, oSpriteManager, 4);//Update the time remaining text"
				oLivesText.UpdateText(cLivesCharArray, 1, 2, oSpriteManager, 4);//Update the "lives" text.
				char cLivesLeftChar[] = { (char)('0' + oPlayer.u8Lives), '\0' };//Creates a character array that contains the characters to be displayed.
				oLivesLeftText.UpdateText(cLivesLeftChar, 17, 10, oSpriteManager, 4);//Update the lives remaining text.
				oScoreText.UpdateText(cScoreCharArray, 199, 2, oSpriteManager, 4);//Update the "score" text.
				char cScoreValueCharArray[3] = { (char)('0' + (oPlayer.u16Score / 100 % 10)),  (char)('0' + (oPlayer.u16Score / 10 % 10)),  (char)('0' + (oPlayer.u16Score % 10)) };//Creates a character array that contains the characters to be displayed.
				oScoreValueText.UpdateText(cScoreValueCharArray, 207, 10, oSpriteManager, 4);//Update the score value text.

				if (oPlayer.u8Lives == 0 || u16TimeLeft == 0)//If the player has no lives left or the timer has run out.
				{
					oTimeText.HideText();//Hide the "time" text.
					oTimeRemainingText.HideText();//Hide the time remaining text.
					oScoreValueText.HideText();//Hide the score value text.
					oLivesLeftText.HideText();//Hide the lives remaining text.
					oLivesText.HideText();//Hide the "lives" text.

					u8State = 0;//Change the state to 0.

					for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
					{
						SetObjectPosition(&oPlayer.poJumpParticleOAMStart[u32I],0 , 160);//Move particle off screen.
					}
					SetObjectPosition(oEnemy1.poCoinParticleOAMStart, 0, 160);//Move particle off screen.
					SetObjectPosition(oEnemy2.poCoinParticleOAMStart, 0, 160);//Move particle off screen.
					SetObjectPosition(oEnemy3.poCoinParticleOAMStart, 0, 160);//Move particle off screen.

					if (oPlayer.u16Score > u16HighScore)//If the current score is higher than the high score.
					{
						u16HighScore = oPlayer.u16Score;//Set the high score to be equal to the current score.
					}

					oPlayer.u16Score = 0;//Reset the score.
					oPlayer.u8Lives = 3;//Reset the lives.
					u16TimeLeft = 300;//Reset the time left.
					s32TitleScroll = 90;//Reset the title scroll.
					oEnemy1.SpawnEnemy(oPlayer);//Re spawn the enemy.
					oEnemy2.SpawnEnemy(oPlayer);//Re spawn the enemy.
					oEnemy3.SpawnEnemy(oPlayer);//Re spawn the enemy.
				}
				DelayNoTimer(300);//Delay the background scrolling.
				VerticalSync();//Only change the screen on the vertical blanks.
			}
		}
		break;//Break early.
	}
	
	default://If there is no case.
		break;//Break early.
	}
	return 0;//Return 0.
}