//\===========================================================================================
//\ File: enemy.h
//\ Author: Morgan James
//\ Date Created: 08/12/2017
//\ Brief: A header that contains the class declaration and prototypes for the enemy.
//\===========================================================================================

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "sprite.h"
#include "gba_graphics.h"
#include "mario.h"
#include "gba_vector2.h"
#include "gba_input.h"
#include "backgroundFunctions.h"
#include "particleFunctions.h"
#include "particles.h"
#include "gba_vector4.h"
#include "gba_timers.h"
#include "collisionMap.h"

class Enemy//A class that will control the enemies in the game.
{
private:
public:
	Sprite oSprite;//The actual sprite attribute information.

	Vector2 v2Position;//The x and y position of the enemy.

	fixed fXVelocity;//How much force is acting on the enemy horizontally and the direction.
	fixed fYVelocity;//How much force is acting on the enemy vertically and the direction.
	fixed fGravity;//How much force is acting on the enemy downwards.
	fixed fWalkSpeed;//How force added horizontally to the enemy when walking.
	fixed fRunSpeed;//How force added horizontally to the enemy when running.

	s32 s32RunDistance;//How far away from the player the enemy has to be able to run.
	s32 s32JumpHeight;//How high the enemy can jump.

	BOOL bMove;//True if the enemy is moving.
	BOOL bFalling;//True if the enemy is falling.
	BOOL bAlive;//True if the enemy is alive.
	BOOL bGotHit;//True if the enemy has ever been hit so that the particle effect can become unhidden.
	
	u8 u8Counter;//The counter that will indicate the changing of the sprites frame.
	u8 u8Frame;//The current frame that the enemy sprite is on.
	u8 u8AnimationDelay;//How frequent the animation frame will change.
	u8 u8WalkAnimationDelay;//A preset frequency for which to change the animation delay by for when the enemy is walking.
	u8 u8RunAnimationDelay;//A preset frequency for which to change the animation delay by for when the enemy is running.

	// --- Particles ---
	fixed fParticleGravity;//The force to apply to the particles.
	fixed fParticleFrameTime;//How long to display each frame of animation on a particle.
	fixed fParticelMeterToPixel;//A measurement of distance for moving particles.

	Emitter oEmitterCoinEffect;//The emitter that the coin particle will disperse from.
	Particle oParticlesCoinEffect[1];//Creates the particles used in the coin effect.
	ObjectAttribute oCoinParticleOAM;//Where the particles OAM is.
	ObjectAttribute* poCoinParticleOAMStart;//The first particles OAM location.

	void EnemyInitialization(SpriteManager& a_rSpriteManager, Player a_player)//A function to initialize the enemy.
	{
		oSprite.poAttribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.ObjectAttributeMemoryFree()];//Indicates where the enemy's OAM is located.
		oSprite.poAttribute->u16Attribute0 = SetAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);//Sets the enemy's attribute 0 so that the sprite is rendered in 4BPP color mode and square.
		oSprite.poAttribute->u16Attribute1 = SetAttribute1(0, 0, ATTRIBUTE1_SIZE_1);//Sets the size of the enemy.
		
		SpawnEnemy(a_player);//Spawns the enemy off the screen to the right or left of the player.
	
		fXVelocity = 0;//Initializes the x velocity to 0.
		fYVelocity = 0;//Initializes the y velocity to 0.
		fGravity = 1;//Initializes gravity to 1.
		fWalkSpeed = 1;//Initializes walk speed to 1.
		fRunSpeed = 2;//Initializes run speed to 2.

		s32JumpHeight = 11;//Initializes jump height to 11.
		s32RunDistance = 100;//Initializes run distance to 100.

		bFalling = 0;//Initializes falling to be false.
		bMove = 0;//Initializes moving to be false.
		bAlive = 1;//Initializes alive to be true.
		bGotHit = 0;//Initializes got hit to be false.

		u8Counter = 0;//Initializes the counter to be 0.
		u8Frame = 64;//Initializes the frame to be 64.
		u8AnimationDelay = 8;//Initializes the animation delay to be 8.
		u8WalkAnimationDelay = 8;//Initializes the walking animation delay to be 8.
		u8RunAnimationDelay = 4;//Initializes the running animation delay to be 8.

		// --- Particles ---
		fParticleGravity = -0x9CC;//Initializes the particle gravity.
		fParticleFrameTime = 0x04;//Initializes the particle frame time.
		fParticelMeterToPixel = IntegerToFixed(5);//Initializes the particle meter to pixel distance.

		oEmitterCoinEffect.fY = 0;//Initializes the coin emitters y position.
		oEmitterCoinEffect.fX = 0;//Initializes the coin emitters x position.
		poCoinParticleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.ObjectAttributeMemoryFree()];//Indicates where the particle's OAM is located.
		ObjectHide(poCoinParticleOAMStart);//Hides the particle effect so that it doesn't appear on the screen until we want it to.
	}

	void SpawnEnemy(Player a_player)//Spawns the enemy with a random palette and location of screen.
	{
		u8 u8Palette = 0;//The palette that the enemy will use.
		v2Position.fY = 0;//Sets the enemy's y to be 0 so its at the top of the screen and wont spawn in any terrain.

		s32 s32Side = QuasiRandomRange(0, 1000);//Picks a side for the player to spawn on.

		if (s32Side > 500)//Left side chosen.
		{
			s32Side = QuasiRandomRange(-1000, -300);//Set a distance for the player to spawn away from the player.
		}
		else//Right side chosen.
		{
			s32Side = QuasiRandomRange(300, 1000);//Set a distance for the player to spawn away from the player.
		}
		if (s32Side % 2 == 0)//If the number chosen is divisible by 2.
		{
			u8Palette = 2;//Set the palette so that the enemy looks like Mario.
		}
		else
		{
			u8Palette = 3;//Set the palette so that the enemy looks like Luigi.
		}

		oSprite.poAttribute->u16Attribute2 = SetAttribute2(64, 1, u8Palette);//Sets the enemy's palette.
		v2Position.fX = s32Side;//Sets the enemy's x position.
	}

	void EnemyMoveLeft()//Moves the enemy left.
	{
		oSprite.SpriteSetHorizontalFlip(1);//Flips the sprite to face left.
		v2Position.fX -= fXVelocity;//Decreases the enemy's position by its horizontal velocity.
	}

	void EnemyMoveRight()//Moves the enemy right.
	{
		oSprite.SpriteSetHorizontalFlip(0);//Flips the sprite to face right.
		v2Position.fX += fXVelocity;//Increases the enemy's position by its horizontal velocity.
	}

	void EnemyJump()//Makes the enemy jump.
	{
		if (!bFalling)//If the enemy is not falling.
		{
			bMove = 0;//Indicates to stop animating the enemy.
			u8Frame = 80;//Sets the frame of the sprite so it looks like Mario is jumping.
			fYVelocity = -s32JumpHeight;//Decreases the vertical velocity of the enemy so that it will move upwards.
			bFalling = 1;//Indicates that the enemy is now falling.
		}
	}

	void EnemyStop()//Stops the animation of the enemy.
	{
		bMove = 0;//Indicates that the enemy is not moving.
		u8Frame = 64;//Sets the frame of the enemy so that it looks like he is standing still.
		u8Counter = 7;//Sets the counter of the frame increasing so that it won't increase.
		fXVelocity = 0;//Sets the enemy's horizontal velocity to be 0.
		oSprite.SpriteSetOffset(u8Frame);//Changes the sprites animation frame to be that of standing.
	}

	void GotHit(Player& a_rPlayer)//Checks if the enemy has gotten hit by the player.
	{
		Vector4 v4PlayerFeet = { a_rPlayer.v2Position.fX, a_rPlayer.v2Position.fY + 32, 16 , 8 };//A vector4 indicating the player's feet bounding box.
		Vector4 v4EnemyHead = { v2Position.fX, v2Position.fY, 16 , 8 };//A vector4 indicating the enemy's head bounding box.
		//Hurt by player
		if (v4PlayerFeet.fX < v4EnemyHead.fX + v4EnemyHead.fW &&
			v4PlayerFeet.fX + v4PlayerFeet.fW > v4EnemyHead.fX &&
			v4PlayerFeet.fY < v4EnemyHead.fY + v4EnemyHead.fH &&
			v4PlayerFeet.fH + v4PlayerFeet.fY > v4EnemyHead.fY  && (a_rPlayer.fYVelocity != 0))//If the player's feet are inside the enemy's head.
		{
			bAlive = 0;//Indicate that the enemy is not alive.
			a_rPlayer.PlayerBounce();//Makes the player do a half jump.
			bMove = 0;//Indicates that the enemy is not moving.
			a_rPlayer.u16Score++;//Increases the score.
			u8Frame = 84;//Set the frame of the enemy to the death frame.
			bFalling = 1;//Indicate that the enemy is falling.
			fYVelocity = -s32JumpHeight;//Moves the enemy up.

			oEmitterCoinEffect.fX = IntegerToFixed(v2Position.fX + 4);//Move the emitter to the enemy's x position.
			oEmitterCoinEffect.fY = IntegerToFixed(v2Position.fY - 63);//Move the emitter to the enemy's y position.

			CoinParticleEmit(oParticlesCoinEffect[0], oEmitterCoinEffect);//Emit the coin particle.
			poCoinParticleOAMStart[0] = oCoinParticleOAM;//Indicates what particle to change.
			
			bGotHit = 1;//Indicates that the enemy has been hit.
		}
	}

	void EnemyAI(Player& a_rPlayer)//A function that will control enemy behavior and collision with the world.
	{
		fixed fEnemyWorldX = ((v2Position.fX + fXVelocity) >> 3) + (a_rPlayer.s32XScroll >> 3);//A fixed indicating the enemy's x position in world space.
		fixed fEnemyWorldY = ((v2Position.fY + fYVelocity) >> 3) + (a_rPlayer.s32YScroll >> 3);//A fixed indicating the enemy's y position in world space.

		// --- Account For Wraparound ---
		while (fEnemyWorldX >= collisionMapWidth)//Whilst the enemy's x world position is larger or equal to the map width.
		{
			fEnemyWorldX -= collisionMapWidth;//Decrease the enemy's x world position by the map width.
		}
		while (fEnemyWorldY >= collisionMapHeight)//Whilst the enemy's y world position is larger or equal to the map height.
		{
			fEnemyWorldY -= collisionMapHeight;//Decrease the enemy's y world position by the map height.
		}
		while (fEnemyWorldX < 0)//Whilst the enemy's x world position is less than 0.
		{
			fEnemyWorldX += collisionMapWidth;//Increase the enemy's x world position by the map width.
		}
		while (fEnemyWorldY < 0)//Whilst the enemy's y world position is less than 0.
		{
			fEnemyWorldY += collisionMapHeight;//Increase the enemy's y world position by the map height.
		}

		fEnemyWorldY *= collisionMapWidth;//Multiply the enemy's y world position by the map width.

		fixed fTopLeft = fEnemyWorldX + fEnemyWorldY;//The top left of the enemy.
		fixed fTopRight = (fEnemyWorldX + fEnemyWorldY) + 2;//The top right of the enemy.

		fixed fBottomLeft = fEnemyWorldX + fEnemyWorldY + (collisionMapWidth << 1);//The bottom left of the enemy.
		fixed fBottomRight = fEnemyWorldX + fEnemyWorldY + (collisionMapWidth << 1) + 2;//The bottom right of the enemy.

		fixed fInnerTopLeft = fEnemyWorldX + fEnemyWorldY;//The inner top left of the enemy. 
		fixed fInnerBottomLeft = fEnemyWorldX + fEnemyWorldY + collisionMapWidth;//The inner bottom left of the enemy.

		fixed fInnerTopRight = fEnemyWorldX + fEnemyWorldY + 2;//The inner top right of the enemy.
		fixed fInnerBottomRight = fEnemyWorldX + fEnemyWorldY + collisionMapWidth + 2;//The inner bottom right of the enemy.

		if (bAlive)//If the enemy is alive.
		{
			GotHit(a_rPlayer);//Check if is being hit by the player.
		}
		if (bAlive)//If the enemy is alive.
		{
			// --- Down collision ---
			if (collisionMap[fBottomLeft] > 0 || 
				collisionMap[fBottomRight] > 0)//If the enemy's feet are on the ground.
			{
				fYVelocity = 0;//Set the vertical velocity to 0.
				bFalling = 0;//Indicate the enemy is not falling.
				bMove = 1;//Indicate the enemy is not moving.
			}
			else//Else if the enemy is not touching the ground.
			{
				bFalling = 1;//Indicate the enemy is falling.
			}
			
			// --- Up collision ---
			if (collisionMap[fTopLeft] > 0 || 
				collisionMap[fTopRight] > 0)//If the enemy's head is touching something.
			{
				fYVelocity = 0;//Set the vertical velocity to 0.
			}

			// --- Running right ---
			if (a_rPlayer.v2Position.fX - s32RunDistance > v2Position.fX)//If the player is more that run distance away.
			{
				// --- Right collision ---
				if (collisionMap[fInnerTopRight] > 0 || 
					collisionMap[fInnerBottomRight] > 0)//If the right side of the enemy is colliding.
				{
					--v2Position.fX;//Decrease the enemy's x position.
					EnemyJump();//Make the enemy jump.
				}
				else//If the right side of the enemy is not colliding.
				{
					fXVelocity = fRunSpeed;//Set the horizontal velocity of the enemy to be equal to the running speed.
					u8AnimationDelay = u8RunAnimationDelay;//Change the animation delay to the running animation delay.
					EnemyMoveRight();//Moves the enemy to the right.
				}
			}
			// --- Walk right ---		
			else if (a_rPlayer.v2Position.fX > v2Position.fX)//If not running and the enemy is to the left of the player.
			{
				// --- Right collision ---
				if (collisionMap[fInnerTopRight] > 0 || 
					collisionMap[fInnerBottomRight] > 0)//If the right side of the enemy is touching a wall.
				{
					--v2Position.fX;//Decrease the enemy's x position.
					EnemyJump();//Make the enemy jump.
				}
				else//If the right side of the enemy is not touching something but is to the left of the player.
				{
					fXVelocity = fWalkSpeed;//Set the horizontal velocity to be equal to walking speed.
					u8AnimationDelay = u8WalkAnimationDelay;//Set the animation delay of the enemy to the walking delay.
					EnemyMoveRight();//Move the enemy right.
				}
			}
			// --- Stop ---
			else if (a_rPlayer.v2Position.fX == v2Position.fX)//If the enemy is at the same x position as the player.
			{
				EnemyStop();//Stop the enemy.
			}

			// --- Running left ---
			if (FixedToInteger(a_rPlayer.v2Position.fX) + s32RunDistance < FixedToInteger(v2Position.fX))//If the enemy is on the right side of the player.
			{
				// --- Left collision ---
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0)//If the left side of the enemy is touching a wall.
				{
					++v2Position.fX;//Increase the x position of the enemy.
					EnemyJump();//Make the enemy jump.
				}
				else//If the enemy is to the right of the player and not colliding with a wall.
				{
					fXVelocity = fRunSpeed;//Set the horizontal velocity to be equal to the running speed.
					u8AnimationDelay = u8RunAnimationDelay;//Set the animation delay equal to the run delay.
					EnemyMoveLeft();//Move the enemy left.
				}
			}
			// --- Walk left ---
			else if (a_rPlayer.v2Position.fX < v2Position.fX)//If the enemy is to the right of the player.
			{
				// --- Left collision ---
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0)//If the left side of the player is colliding with a wall.
				{
					++v2Position.fX;//Increase the enemy's x position.
					EnemyJump();//Makes the enemy jump.
				}
				else//If the enemy is to the right of the player and not colliding with a wall.
				{
					fXVelocity = fWalkSpeed;//Set the horizontal velocity of the enemy to the walk speed.
					u8AnimationDelay = u8WalkAnimationDelay;//Set the animation delay equal to the walk delay.
					EnemyMoveLeft();//Move the enemy left.
				}
			}
			// --- Stop ---
			else if (a_rPlayer.v2Position.fX == v2Position.fX)//If the enemy is at the same x position as the player.
			{
				EnemyStop();//Stop the enemy.
			}
		}
	}

	void EnemyUpdate(Player& a_rPlayer)//Updates the enemy.
	{
		EnemyAI(a_rPlayer);//Checks if the enemy is colliding.
		
		if (bMove)//If the enemy is moving.
		{
			u8Counter++;//Increase the frame counter.
			if (u8Counter >= u8AnimationDelay)//If the counter is larger or equal to the animation delay.
			{
				u8Frame += 4;//Increase the frame of animation.

				if (u8Frame > 76)//If the frame is at the end of the walking animation frames.
				{
					u8Frame = 68;//Sets the frame to the start of the walking cycle frames.
				}
				u8Counter = 0;//Reset the counter.
			}
		}

		if (bFalling)//If the enemy is falling.
		{
			v2Position.fY += fYVelocity;//Increase the y position of the enemy by the vertical velocity.
			fYVelocity += fGravity;//Increase the vertical velocity of the enemy.
		}

		if (a_rPlayer.bScreenLeft)//If the screen is moving to the left.
		{
			v2Position.fX += a_rPlayer.fXVelocity;//Set the x position of the enemy to keep it in accordance.
		}
		if (a_rPlayer.bScreenRight)//If the screen is moving to the right.
		{
			v2Position.fX -= a_rPlayer.fXVelocity;//Set the x position of the enemy to keep it in accordance.
		}
		if (v2Position.fX >= 0 && v2Position.fX <= 240)//If the enemy is on screen.
		{
			oSprite.SpriteSetPosition(v2Position.fX, v2Position.fY);//Move the sprite to the correct location.
		}
		else//If the enemy is off screen.
		{
			oSprite.SpriteSetPosition(0, 160);//Move the sprite so it doesn't appear on the screen.
		}
		if (v2Position.fY > 150)//If the enemy falls close to the bottom of the screen.
		{
			SpawnEnemy(a_rPlayer);//Re-spawn the enemy.
			bAlive = 1;//Indicate that the enemy is alive.
		}

		oSprite.SpriteSetOffset(u8Frame);//Set the offset of the sprites frame.

		// --- Coin particle update ---
		if (bGotHit)
		{
			UpdateCoinParticleOneShot(oParticlesCoinEffect[0], oEmitterCoinEffect, fParticleFrameTime, fParticelMeterToPixel, fParticleGravity);//Updates each particle.
			poCoinParticleOAMStart[0].u16Attribute1 = SetAttribute1(FixedToInteger(oParticlesCoinEffect[0].fX), 0, ATTRIBUTE1_SIZE_1);//Sets the x position and size of the particle.
			poCoinParticleOAMStart[0].u16Attribute0 = SetAttribute0(FixedToInteger(oParticlesCoinEffect[0].fY), 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);//Sets the y position, color mode and shape of the particle.

			u32 u32CoinFrameID = (1 << 9) - oParticlesCoinEffect[0].u32Lifespan;//Set the frame ID based on the particles life.
			u32CoinFrameID = u32CoinFrameID << 4 >> 9;//Set the frame ID based on the particles life.
			poCoinParticleOAMStart[0].u16Attribute2 = SetAttribute2(160 + u32CoinFrameID, 0, 6);//Change the particle frame.

			if (a_rPlayer.bScreenLeft)//If the screen is moving left.
			{
				oParticlesCoinEffect[0].fX += a_rPlayer.fXVelocity;//Sets the particle position in accordance to the screens movement.
				SetObjectPosition(&poCoinParticleOAMStart[0], FixedToInteger(oParticlesCoinEffect[0].fX), FixedToInteger(oParticlesCoinEffect[0].fY));//Move particle.
			}
			if (a_rPlayer.bScreenRight)//If the screen is moving right.
			{
				oParticlesCoinEffect[0].fX -= a_rPlayer.fXVelocity;//Sets the particle position in accordance to the screens movement.
				SetObjectPosition(&poCoinParticleOAMStart[0], FixedToInteger(oParticlesCoinEffect[0].fX), FixedToInteger(oParticlesCoinEffect[0].fY));//Move particle.
			}
		}
	}
};

#endif//__ENEMY_H__