//\===========================================================================================
//\ File: player.h
//\ Author: Morgan James
//\ Date Created: 27/11/2017
//\ Brief:
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
#include "particles.h"

#include "collisionMap.h"

/* a struct for the koopa's logic and behavior */
class Player
{
private:
public:

	/* the actual sprite attribute info */
	Sprite* sprite;

	/* the x and y postion */
	Vector2 position;

	s32 iXScroll;
	s32 iYScroll;
	fixed iXSrollBackground2Offset;
	fixed iXSrollBackground3Offset;

	int walkSpeed;

	int runSpeed;

	int walkAnimationDelay;

	int runAnimationDelay;

	int xvel;

	/* the koopa's y velocity in 1/256 pixels/second */
	int yvel;

	int jumpHeight;

	/* the koopa's y acceleration in 1/256 pixels/second^2 */
	int gravity;

	/* which frame of the animation he is on */
	int frame;

	/* the number of frames to wait before flipping */
	int animationDelay;

	/* the animation counter counts how many frames until we flip */
	int counter;

	/* whether the koopa is moving right now or not */
	int move;

	/* the number of pixels away from the edge of the screen the koopa stays */
	int border;
	/* if the koopa is currently falling */
	int falling;
	int xDir;
	int yDir;


	//Particles

	fixed g_gravity;
	fixed g_frameTime;
	fixed g_pixels2Meter;
	Emitter emitterJumpEffect;
	Particle particlesJumpEffect[64];
	ObjectAttribute particleOAM;
	ObjectAttribute* particleOAMStart;

	

	void playerInitialization()
	{
		sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[0];
		sprite->Attribute->attribute0 = setAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);
		sprite->Attribute->attribute1 = setAttribute1(120, 0, ATTRIBUTE1_SIZE_2);
		sprite->Attribute->attribute2 = setAttribute2(0, 0, 0);


		// --- Particles ---

		g_gravity = -0x9CC;
		g_frameTime = 0x04;
		g_pixels2Meter = integerToFixed(5);

	

	    particleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[1];

	
		// --- ---
		position.x = 120;
		position.y = 100;
		xvel = 0;
		yvel = 0;
		jumpHeight = 11;
		walkSpeed = 1;
		runSpeed = 2;
		iXScroll = 0;
		iYScroll = 80;
		iXSrollBackground2Offset = fixedDivide(integerToFixed(75), integerToFixed(100));
		iXSrollBackground3Offset = fixedDivide(integerToFixed(5), integerToFixed(10));
		walkAnimationDelay = 8;
		runAnimationDelay = 4;
		gravity = 1;
		border = 40;
		frame = 0;
		move = 0;
		counter = 0;
		falling = 0;
		animationDelay = 8;
		xDir = 0;
		yDir = 0;


	}

	/* move the Player left or right returns if it is at edge of the screen */
	int playerMoveLeft()
	{
		/* face left */
		sprite->spriteSetHorizontalFlip(1);
		move = 1;

		/* if we are at the left end, just scroll the screen */
		if (position.x < border)
		{
			return 1;
		}
		else
		{
			/* else move left */
			position.x -= xvel;
			return 0;
		}
	}

	int playerMoveRight()
	{
		/* face right */
		sprite->spriteSetHorizontalFlip(0);
		move = 1;

		/* if we are at the right end, just scroll the screen */
		if (position.x > (240 - 16 - border))
		{
			return 1;
		}
		else
		{
			/* else move right */
			position.x += xvel;
			return 0;
		}
	}

	void playerStop()
	{
		move = 0;
		frame = 0;
		counter = 7;
		xvel = 0;
		sprite->spriteSetOffset(frame);
	}

	/* start the koopa jumping, unless already fgalling */
	void playerJump()
	{
		if (!falling)
		{
			yvel = -jumpHeight;
			falling = 1;
		}
	}


	void playerCollision()
	{
		s32 pX = ((position.x + xvel) >> 3) + (iXScroll >> 3);
		s32 pY = ((position.y + (yvel  )) >> 3) + (iYScroll >> 3);


		/* account for wraparound */
		while (pX >= collisionMapWidth)
		{
			pX -= collisionMapWidth;
		}
		while (pY >= collisionMapHeight)
		{
			pY -= collisionMapHeight;
		}
		while (pX < 0)
		{
			pX += collisionMapWidth;
		}
		while (pY < 0)
		{
			pY += collisionMapHeight;
		}

		pY *= collisionMapWidth;


		s32 TL = pX + pY;
		s32 TR = (pX + pY) + 2;

		s32 BL = pX + pY + (collisionMapWidth << 2);
		s32 BR = pX + pY + (collisionMapWidth << 2) + 2;

		s32 ITL = pX + pY ;
		s32 IBL = pX + pY + (collisionMapWidth << 1) + collisionMapWidth;

		s32 IITL = pX + pY + collisionMapWidth;
		s32 IIBL = pX + pY + (collisionMapWidth << 1);

		s32 ITR = pX + pY + 2;
		s32 IBR = pX + pY + (collisionMapWidth << 1) + collisionMapWidth + 2;

		s32 IITR = pX + pY + 2 + collisionMapWidth;
		s32 IIBR = pX + pY + (collisionMapWidth << 1) + 2;

		//Down collision
		if (collisionMap[BL] > 0 || collisionMap[BR] > 0 )
		{
			yvel = 0;
			falling = 0;
			//position.y--;
		}
		else
		{
			/* he is falling now */
			falling = 1;
		}
		
		//Up collision
		if (collisionMap[TL] > 0 || collisionMap[TR] > 0)
		{
			yvel = 0;
			
		}


		if (keyDown(A))
		{
			emitterJumpEffect.x = integerToFixed(position.x + 7);//Move the emiter to the players x pos.
			emitterJumpEffect.y = integerToFixed(position.y + 31);//Move the emiter to the players y pos.
			for (int i = 0; i < 64; ++i)
			{
				EmitParticle(particlesJumpEffect[i], emitterJumpEffect);
				particleOAMStart[i] = particleOAM;
			}

			playerJump();
		}

		s32 xDir = getAxis(HORIZONTAL);
		switch (xDir)
		{
			// Moving Right
		case 1:
		{

			if (keyDown(B))
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.x;
				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					if (playerMoveRight())
					{
						iXScroll += xvel;

						//Keep the particles in the same spot
						for (int i = 0; i < 64; ++i)
						{

							particlesJumpEffect[i].x -= integerToFixed(xvel);
							setObjectPosition(&particleOAMStart[i], fixedToInteger(particlesJumpEffect[i].x), fixedToInteger(particlesJumpEffect[i].y));//Move particle

						}

					}
				}
			}
			else if (playerMoveRight())
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.x;
				}
				else
				{
					xvel = walkSpeed;
					iXScroll += xvel;
					animationDelay = walkAnimationDelay;

					//Keep the particles in the same spot
					for (int i = 0; i < 64; ++i)
					{

						particlesJumpEffect[i].x -= integerToFixed(xvel);
						setObjectPosition(&particleOAMStart[i], fixedToInteger(particlesJumpEffect[i].x), fixedToInteger(particlesJumpEffect[i].y));//Move particle

					}
				}
			}
			else 
			{
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.x;
				}
				else
				{
					xvel = walkSpeed;
					animationDelay = walkAnimationDelay;
				}
			}

			break;
		}
		// Moving left
		case -1:
		{
			if (keyDown(B))
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.x;
				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					if (playerMoveLeft())
					{
						iXScroll -= xvel;

						//Keep the particles in the same spot
						for (int i = 0; i < 64; ++i)
						{

							particlesJumpEffect[i].x += integerToFixed(xvel);
							setObjectPosition(&particleOAMStart[i], fixedToInteger(particlesJumpEffect[i].x), fixedToInteger(particlesJumpEffect[i].y));//Move particle

						}
					}
				}
			}
			else if (playerMoveLeft())
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.x;
				}
				else
				{
					xvel = walkSpeed;
					iXScroll -= xvel;
					animationDelay = walkAnimationDelay;

					//Keep the particles in the same spot
					for (int i = 0; i < 64; ++i)
					{

						particlesJumpEffect[i].x += integerToFixed(xvel);
						setObjectPosition(&particleOAMStart[i], fixedToInteger(particlesJumpEffect[i].x), fixedToInteger(particlesJumpEffect[i].y));//Move particle

					}
				}
			}
			else
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.x;
				}
				else
				{
					xvel = walkSpeed;
					animationDelay = walkAnimationDelay;
				}
			}

			break;
		}
		// Not moving
		case 0:
		{
			playerStop();

			break;
		}
		default:
		{
			break;
		}
		}

	}


	/* update the koopa */
	void playerUpdate()
	{
	

		/* update y position and speed if falling */
		if (falling)
		{
			position.y += yvel;
			yvel += gravity;
		}

		if (move)
		{
			counter++;
			if (counter >= animationDelay)
			{
				frame = frame + 8;
				if (frame > 8)
				{
					frame = 0;
				}
				sprite->spriteSetOffset(frame);
				counter = 0;
			}
		}
		

		//Particle update.
		for (int i = 0; i < 64; ++i)
		{

			UpdateParticleOneShot(particlesJumpEffect[i], emitterJumpEffect, g_frameTime, g_pixels2Meter, g_gravity);//Updates each particle.

			setObjectPosition(&particleOAMStart[i], fixedToInteger(particlesJumpEffect[i].x), fixedToInteger(particlesJumpEffect[i].y));//Move particle

			u32 frameID = (1 << 9) - particlesJumpEffect[i].life;//Set the frame ID based on the particles life.
			frameID = frameID << 4 >> 9;//Set the frame ID based on the particles life.
			particleOAMStart[i].attribute2 = setAttribute2(32 + frameID, 0, 1);//Change the particle frame.

		}

		playerCollision();
		sprite->spriteSetPosition(position.x, position.y);

		REGISTRY_BACKGROUND_OFF_SET[0].s16X = iXScroll;
		REGISTRY_BACKGROUND_OFF_SET[0].s16Y = iYScroll;
		REGISTRY_BACKGROUND_OFF_SET[1].s16X = fixedToInteger(fixedMultiply(integerToFixed(iXScroll), iXSrollBackground2Offset));
		REGISTRY_BACKGROUND_OFF_SET[2].s16X = fixedToInteger(fixedMultiply(integerToFixed(iXScroll), iXSrollBackground3Offset));

	}



};

#endif//__PLAYER_H__