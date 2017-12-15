//\===========================================================================================
//\ File: player.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief: A header that contains the class declaration and prototypes for the player.
//\===========================================================================================

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sprite.h"
#include "gba_graphics.h"
#include "koopa.h"
#include "gba_vector2.h"
#include "gba_input.h"
#include "backgroundFunctions.h"
#include "particleFunctions.h"
#include "smoke.h"
#include "sinlut.h"
#include "collisionMap.h"
#include "spriteManager.h"

class Player//A class that will control the player in the game.
{
private:
public:
	Sprite oSprite;//The actual sprite attribute information.

	Vector2 v2Position;//The x and y position of the enemy.

	s32 s32XScroll;//The offset of the map in the x direction.
	s32 s32YScroll;//The offset of the map in the y direction.
	s32 s32Border;//How far the player can be away form the side of the screen without it scrolling.
	u16 u16Score;//The score of the player indicated at the top of the screen.
	s32 s32JumpHeight;//How high the player can jump.

	fixed fXSrollBackground2Offset;//The offset of background 2 in the x direction.
	fixed fXSrollBackground3Offset;//The offset of background 3 in the x direction.
	fixed fWalkSpeed;//How force added horizontally to the player when walking.
	fixed fRunSpeed;//How force added horizontally to the player when running.
	fixed fXVelocity;//How much force is acting on the player horizontally and the direction.
	fixed fYVelocity;//How much force is acting on the player vertically and the direction.
	fixed fGravity;//How much force is acting on the player downwards.

	u8 u8Counter;//The counter that will indicate the changing of the sprites frame.
	u8 u8Frame;//The current frame that the player sprite is on.
	u8 u8AnimationDelay;//How frequent the animation frame will change.
	u8 u8WalkAnimationDelay;//A preset frequency for which to change the animation delay by for when the enemy is walking.
	u8 u8RunAnimationDelay;//A preset frequency for which to change the animation delay by for when the enemy is running.
	u8 u8FrameSkip;//How far to move the frame of animation for the player.
	u8 u8Lives;//How many lives the player has currently got.

	BOOL bMove;//True when the player is moving.
	BOOL bInvulnerable;//True when the player is invulnerable.
	BOOL bScreenRight;//True when the player is moving right and touching the border.
	BOOL bScreenLeft;//true when the player is moving left and touching the border.
	BOOL bFalling;
	
	// --- Particles ---
	fixed fParticleGravity;//The force to apply to the particles.
	fixed fParticleFrameTime;//How long to display each frame of animation on a particle.
	fixed fParticelMeterToPixel;//A measurement of distance for moving particles.

	Emitter oEmitterJumpEffect;//The emitter that the jump particle will disperse from.
	Particle oParticlesJumpEffect[32];//Creates the particles used in the jump effect.
	ObjectAttribute oJumpParticleOAM;//Where the particles OAM is.
	ObjectAttribute* poJumpParticleOAMStart;//The first particles OAM location.

	void PlayerInitialization(SpriteManager& a_rSpriteManager)//A function to initialize the player.
	{
		oSprite.poAttribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.ObjectAttributeMemoryFree()];//Indicates where the players OAM is located.
		oSprite.poAttribute->u16Attribute0 = SetAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);//Sets the players attribute 0 so that the sprite is rendered in 4BPP color mode and tall.
		oSprite.poAttribute->u16Attribute1 = SetAttribute1(120, 0, ATTRIBUTE1_SIZE_2);//Sets the size of the player.
		oSprite.poAttribute->u16Attribute2 = SetAttribute2(0, 1, 0);//Sets attribute 2 of the sprite to indicate the palette bank.

		v2Position.fX = 120;//Sets the x position of the player so he will appear at that location when the game is playing.
		v2Position.fY = 100;//Sets the y position of the player so he will appear at that location when the game is playing.

		oSprite.SpriteSetPosition(0, 160);//Move the player sprite out of site so you don't see it when the game first loads up.

		fXVelocity = 0;//Initializes the x velocity to 0.
		fYVelocity = 0;//Initializes the y velocity to 0.
		fWalkSpeed = 1;//Initializes walk speed to 1.
		fRunSpeed = 2;//Initializes run speed to 2.
		fXSrollBackground2Offset = FixedDivide(IntegerToFixed(75), IntegerToFixed(100));//Sets background 2 to be at an x offset of 75% of background0.
		fXSrollBackground3Offset = FixedDivide(IntegerToFixed(5), IntegerToFixed(10));//Sets background 3 to be at an x offset of 50% of background0.
		fGravity = 1;//Initializes gravity to 1.

		s32JumpHeight = 11;//Initializes jump height to 11.
		s32XScroll = 0;//The starting offset of background 0 in the x direction.
		s32YScroll = 80;//The starting offset of background 0 in the y direction.
		s32Border = 40;//Sets the border of the screen to be 40 pixel from each side.
		u16Score = 0;//Sets the score of the player to 0 to start.

		u8Lives = 3;//Sets the starting lives of the player to be 3.
		u8WalkAnimationDelay = 8;//Initializes the walking animation delay to be 8.
		u8RunAnimationDelay = 4;//Initializes the running animation delay to be 8.
		u8Frame = 0;//Initializes the frame to be 0.
		u8AnimationDelay = 8;//Initializes the animation delay to be 8.
		u8FrameSkip = 8;//Initializes the frame skip to 8.
		u8Counter = 0;

		bMove = 0;//Initializes moving to be false.
		bFalling = 0;//Initializes falling to be false.
		bInvulnerable = 0;//Initializes invulnerability to be false.
		bScreenRight = 0;//Initializes screen moving right to be false.
		bScreenLeft = 0;//Initializes screen moving left to be false.

		// --- Particles ---
		fParticleGravity = -0x9CC;//Initializes the particle gravity.
		fParticleFrameTime = 0x04;//Initializes the particle frame time.
		fParticelMeterToPixel = IntegerToFixed(5);//Initializes the particle meter to pixel distance.

		oEmitterJumpEffect.fY = 0;//Initializes the jump emitters y position.
		oEmitterJumpEffect.fX = 0;//Initializes the jump emitters x position.
		poJumpParticleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[96];//The start of the 32 OAM locations.
	}

	u8 PlayerMoveLeft()//Moves the player left.
	{
		oSprite.SpriteSetHorizontalFlip(1);//Flips the sprite to face left.
		bMove = 1;//Indicates the player is moving.

		if (v2Position.fX < s32Border)//If the player is at the border.
		{
			return 1;//Returns 1.
		}
		else//If the player is not at the border.
		{
			v2Position.fX -= fXVelocity;//Decreases the players x position by horizontal velocity.
			return 0;//Returns 0.
		}
	}

	u8 PlayerMoveRight()//Moves the player right.
	{
		oSprite.SpriteSetHorizontalFlip(0);//Flips the sprite to face right.
		bMove = 1;//Indicates the player is moving.

		if (v2Position.fX > (240 - 16 - s32Border))//If the player is at the border.
		{
			return 1;//Returns 1.
		}
		else//If the player is not at the border.
		{
			v2Position.fX += fXVelocity;//Increases the players x position by horizontal velocity.
			return 0;//Returns 0.
		}
	}

	void PlayerStop()//Stops the animation of the player.
	{
		bMove = 0;//Indicates that the player is not moving.
		u8Frame = 0;//Sets the frame of the player so that it looks like he is standing still.
		u8Counter = 7;//Sets the counter of the frame increasing so that it won't increase.
		fXVelocity = 0;//Sets the players horizontal velocity to be 0.
		oSprite.SpriteSetOffset(u8Frame);//Changes the sprites animation frame to be that of standing.
	}

	void PlayerJump()//Makes the player jump.
	{
		if (!bFalling)//If the player is not falling.
		{
			fYVelocity = -s32JumpHeight;//Decreases the vertical velocity of the player so that it will move upwards.
			bFalling = 1;//Indicates that the player is now falling.

			oEmitterJumpEffect.fX = IntegerToFixed(v2Position.fX + 7);//Move the emitter to the players x position.
			oEmitterJumpEffect.fY = IntegerToFixed(v2Position.fY + 31);//Move the emitter to the players y position.
			for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
			{
				JumpParticleEmit(oParticlesJumpEffect[u32I], oEmitterJumpEffect);//Emits a jump particle.
				poJumpParticleOAMStart[u32I] = oJumpParticleOAM;//Indicates what particle to change.
			}
		}
	}

	void PlayerBounce()//A function to make the player do a half jump when landing on an enemy.
	{
		fYVelocity = -(s32JumpHeight >> 1);//Decreases the vertical velocity of the player so that it will move upwards.
	}

	void PlayerCollision()//Checks if the player is colliding with the terrain.
	{
		fixed fPlayerWorldX = ((v2Position.fX + fXVelocity) >> 3) + (s32XScroll >> 3);//A fixed indicating the players x position in world space.
		fixed fPlayerWorldY = ((v2Position.fY + fYVelocity) >> 3) + (s32YScroll >> 3);//A fixed indicating the players y position in world space.

		// --- Account For Wraparound ---
		while (fPlayerWorldX >= collisionMapWidth)//Whilst the players x world position is larger or equal to the map width.
		{
			fPlayerWorldX -= collisionMapWidth;//Decrease the players x world position by the map width.
		}
		while (fPlayerWorldY >= collisionMapHeight)//Whilst the players y world position is larger or equal to the map height.
		{
			fPlayerWorldY -= collisionMapHeight;//Decrease the players y world position by the map height.
		}
		while (fPlayerWorldX < 0)//Whilst the players x world position is less than 0.
		{
			fPlayerWorldX += collisionMapWidth;//Increase the players x world position by the map width.
		}
		while (fPlayerWorldY < 0)//Whilst the players y world position is less than 0.
		{
			fPlayerWorldY += collisionMapHeight;//Increase the players y world position by the map height.
		}

		fPlayerWorldY *= collisionMapWidth;//Multiply the players y world position by the map width.


		fixed fTopLeft = fPlayerWorldX + fPlayerWorldY;//The top left of the player.
		fixed fTopRight = (fPlayerWorldX + fPlayerWorldY) + 2;//The top right of the player.

		fixed fBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 2);//The bottom left of the player.
		fixed fBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 2) + 2;//The bottom right of the player.

		fixed fInnerTopLeft = fPlayerWorldX + fPlayerWorldY;//The inner top left of the player.
		fixed fInnerBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + collisionMapWidth;//The inner bottom left of the player.

		fixed fInnerInnerTopLeft = fPlayerWorldX + fPlayerWorldY + collisionMapWidth;//The inner^2 top left of the player.
		fixed fInnerInnerBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1);//The inner^2 bottom left of the player.

		fixed fInnerTopRight = fPlayerWorldX + fPlayerWorldY + 2;//The inner top right of the player.
		fixed fInnerBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + collisionMapWidth + 2;//The inner bottom right of the player.

		fixed fInnerInnerTopRight = fPlayerWorldX + fPlayerWorldY + 2 + collisionMapWidth;//The inner^2 top right of the player.
		fixed fInnerInnerBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + 2;//The inner^2 bottom right of the player.

		// --- Down collision ---
		if (collisionMap[fBottomLeft] > 0 
			|| collisionMap[fBottomRight] > 0 )//If the players feet are on the ground.
		{
			fYVelocity = 0;//Set the vertical velocity to 0.
			bFalling = 0;//Indicate the player is not falling.
		}
		else//Else if the players is not touching the ground.
		{
			bFalling = 1;//Indicate the player is falling.
		}

		// --- Up collision ---
		if (collisionMap[fTopLeft] > 0 
			|| collisionMap[fTopRight] > 0)//If the players head is touching something.
		{
			fYVelocity = 0;//Set the vertical velocity to 0.
		}

		if (KeyDown(A))//If the A key is down.
		{
			PlayerJump();//Make the player jump.
		}

		s32 s32XDirection = GetAxis(HORIZONTAL);//Sets the direction to be -1 if the user presses left and 1 for if they press right otherwise it's 0.

		bScreenRight = 0;//Indicates that the screen is not moving right.
		bScreenLeft = 0;//Indicates that the screen is not moving left.

		switch (s32XDirection)//Changes depending on which part of D-Pad the user presses.
		{
		// --- Moving Right ---
		case 1://If the user presses on the right side of the D-pad.
		{
			// --- Running right ---
			if (KeyDown(B))//If the user is holding down the B key.
			{
				// --- Right collision ---
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 ||
					collisionMap[fInnerInnerBottomRight] > 0)//If the right side of the player is colliding.
				{
					--v2Position.fX;//Decrease the players x position.
				}
				else//If the right side of the player is not colliding.
				{
					fXVelocity = fRunSpeed;//Set the horizontal velocity of the player to be equal to the running speed.
					u8AnimationDelay = u8RunAnimationDelay;//Change the animation delay to the running animation delay.
					if (PlayerMoveRight())//If the player is at the border.
					{
						s32XScroll += fXVelocity;//Scroll the map on the x direction equal to horizontal velocity.
						bScreenRight = 1;//Indicate the screen is moving right.

						// --- Keep the particles in the same spot ---
						for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
						{
							oParticlesJumpEffect[u32I].fX -= fXVelocity;//Set the particles position in accordance with the screen
							SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Moves the particle.
						}
					}
				}
			}
			// --- Walk right ---	
			else if (PlayerMoveRight())//If the player is not holding B.
			{
				// --- Right collision ---
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 || 
					collisionMap[fInnerInnerBottomRight] > 0)//If the right side of the player is touching a wall.
				{
					--v2Position.fX;//Decrease the players x position.
				}
				else//If the right side of the player is not touching something.
				{
					fXVelocity = fWalkSpeed;//Set the horizontal velocity to be equal to walking speed.
					s32XScroll += fXVelocity;//Increase the x offset of backgroun0 by the player horizontal velocity.
					bScreenRight = 1;//Indicate that the screen is moving right.
					u8AnimationDelay = u8WalkAnimationDelay;//Set the animation delay of the player to the walking delay.

					// --- Keep the particles in the same spot ---
					for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
					{
						oParticlesJumpEffect[u32I].fX -= fXVelocity;//Set the particles position in accordance with the screen
						SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Moves the particle.
					}
				}
			}
			else//If the player is not at the border.
			{
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 ||
					collisionMap[fInnerInnerBottomRight] > 0)//If the right side of the player is colliding.
				{
					--v2Position.fX;//Decrease the x position of the player.
				}
				else//Else if the player's right side is not colliding.
				{
					fXVelocity = fWalkSpeed;//Set the horizontal velocity of the player to be equal to the walking speed.
					u8AnimationDelay = u8RunAnimationDelay;//Set the animation delay equal to the run delay.
				}
			}
			break;
		}
		// --- Moving left ---
		case -1:
		{
			// --- Running left ---
			if (KeyDown(B))//If the user is holding the B button.
			{
				// --- Left collision ---
				if (collisionMap[fInnerTopLeft] > 0 ||
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)//If the left side of the player is touching a wall.
				{
					++v2Position.fX;//Increase the x position of the player.
				}
				else//If the left side of the player is not colliding with a wall.
				{
					fXVelocity = fRunSpeed;//Set the horizontal velocity of the player to be that of running speed.
					u8AnimationDelay = u8RunAnimationDelay;//Set the animation delay of the player to be that of the running animation delay.
					if (PlayerMoveLeft())//If the player is at the border.
					{
						s32XScroll -= fXVelocity;//Decrease the offset of background0 by the player's horizontal velocity.
						bScreenLeft = 1;//Indicate the screen is moving left.

						// --- Keep the particles in the same spot ---
						for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
						{
							oParticlesJumpEffect[u32I].fX += fXVelocity;//Set the particles position in accordance with the screen
							SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move the particle.
						}
					}
				}
			}
			// --- Walk left ---
			else if (PlayerMoveLeft())//If the player is at the border.
			{
				// --- Left collision ---
				if (collisionMap[fInnerTopLeft] > 0 ||
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)//If the left side of the player is touching a wall.
				{
					++v2Position.fX;//Increase the x position of the player.
				}
				else//If the left side of the player is not colliding with a wall.
				{
					fXVelocity = fWalkSpeed;//Set the horizontal velocity of the player to be that of walking speed.
					s32XScroll -= fXVelocity;//Decrease the offset of background0 by the player's horizontal velocity.
					bScreenLeft = 1;//Indicate the screen is moving left.
					u8AnimationDelay = u8WalkAnimationDelay;//Set the animation delay of the player to be that of the walking animation delay.

					// --- Keep the particles in the same spot ---
					for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles.
					{
						oParticlesJumpEffect[u32I].fX += fXVelocity;//Set the particles position in accordance with the screen
						SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move the particle.
					}
				}
			}
			else
			{
				// --- Left collision ---
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)//If the left side of the player is touching a wall.
				{
					++v2Position.fX;//Increase the x position of the player.
				}
				else
				{

					fXVelocity = fWalkSpeed;//Set the horizontal velocity of the player to be that of walking speed.
					u8AnimationDelay = u8WalkAnimationDelay;//Set the animation delay of the player to be that of the walking animation delay.
				}
			}
			break;
		}
		// --- Stop ---
		case 0:
		{
			if (bInvulnerable == 0)//If the player is vulnerable.
			{
				PlayerStop();//Stop moving the player.
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void PlayerUpdate()//Updates the player.
	{
		if (bFalling)//If the player is falling
		{
			v2Position.fY += fYVelocity;//Increase the y position of the player by the vertical velocity.
			fYVelocity += fGravity;//Increase the vertical velocity of the player.
		}

		if (bMove || bInvulnerable)//If the player is moving or is invulnerable.
		{
			u8Counter++;//Increase the counter.
			if (u8Counter >= u8AnimationDelay)//If the counter is larger or equal to the animation delay.
			{
				u8Frame += u8FrameSkip;//Increase the frame of animation by frame skip.

				if (u8Frame > u8FrameSkip)//If the frame is at the past frame skip.
				{
					u8Frame = 0;//Set the frame to 0.
				}
				oSprite.SpriteSetOffset(u8Frame);//Set the offset of the sprite to be equal to the frame.
				u8Counter = 0;//Reset the counter.
			}
		}

		// --- Jump particle update ---
		for (u32 u32I = 0; u32I < 32; ++u32I)//For all particles
		{
			UpdateJumpParticleOneShot(oParticlesJumpEffect[u32I], oEmitterJumpEffect, fParticleFrameTime, fParticelMeterToPixel, fParticleGravity);//Updates each particle.
			SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle.
		
			u32 u32JumpFrameID = (1 << 9) - oParticlesJumpEffect[u32I].u32Lifespan;//Set the frame ID based on the particles life.
			u32JumpFrameID = u32JumpFrameID << 4 >> 9;//Set the frame ID based on the particles life.
			poJumpParticleOAMStart[u32I].u16Attribute2 = SetAttribute2(32 + u32JumpFrameID, 0, 1);//Change the particle frame.

			if (oParticlesJumpEffect[u32I].fY < 160)//If particle is below the screen.
			{
				oParticlesJumpEffect[u32I].fY = 160;//Set the y position of the particle to be that of off screen.
				oParticlesJumpEffect[u32I].fX = 0;//Set the x position of the particle to be that of off screen.
			}
		
		}

		PlayerCollision();//Check if the player is colliding.
		oSprite.SpriteSetPosition(v2Position.fX, v2Position.fY);//Moves the sprite of the player.

		REGISTRY_BACKGROUND_OFF_SET[0].s16X = s32XScroll;//Off sets background 0 x by the horizontal scroll.
		REGISTRY_BACKGROUND_OFF_SET[0].s16Y = s32YScroll;//Off sets background 0 y by the vertical scroll.
		
		// --- Parallax ---
		REGISTRY_BACKGROUND_OFF_SET[1].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(s32XScroll), fXSrollBackground2Offset));//Offset background1 x by a percentage of background0's x offset.
		REGISTRY_BACKGROUND_OFF_SET[2].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(s32XScroll), fXSrollBackground3Offset));//Offset background2 x by a percentage of background0's x offset.
	}
};

#endif//__PLAYER_H__