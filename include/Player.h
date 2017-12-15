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
#include "smoke.h"
#include "sinlut.h"
#include "collisionMap.h"
#include "spriteManager.h"

/* a struct for the koopa's logic and behavior */
class Player
{
private:
public:

	/* the actual sprite attribute info */
	Sprite sprite;

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
	int frameSkip;
	int invulnerable;
	int lives;
	int score;
	int emitCoin;

	//Particles

	fixed g_gravity;
	fixed g_frameTime;
	fixed g_pixels2Meter;

	Emitter emitterJumpEffect;
	Particle particlesJumpEffect[32];
	ObjectAttribute jumpParticleOAM;
	ObjectAttribute* jumpParticleOAMStart;

	//passed infor to enemy
	int screenRight;
	int screenLeft;

	void playerInitialization(SpriteManager& a_spriteManager)
	{
		sprite.Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_spriteManager.objectAttributeMemoryFree()];
		sprite.Attribute->u16Attribute0 = SetAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);
		sprite.Attribute->u16Attribute1 = SetAttribute1(120, 0, ATTRIBUTE1_SIZE_2);
		sprite.Attribute->u16Attribute2 = SetAttribute2(0, 1, 0);


		// --- Particles ---

		g_gravity = -0x9CC;
		g_frameTime = 0x04;
		g_pixels2Meter = IntegerToFixed(5);

		emitterJumpEffect.fY = 0;
		emitterJumpEffect.fX = 0;

		jumpParticleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[96];
	
		// --- ---
		position.fX = 120;
		position.fY = 100;
		xvel = 0;
		yvel = 0;
		jumpHeight = 11;
		walkSpeed = 1;
		runSpeed = 2;
		lives = 3;
		iXScroll = 0;
		iYScroll = 80;
		iXSrollBackground2Offset = FixedDivide(IntegerToFixed(75), IntegerToFixed(100));
		iXSrollBackground3Offset = FixedDivide(IntegerToFixed(5), IntegerToFixed(10));
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


		score = 0;



		frameSkip = 8;
		invulnerable = 0;
		//passed info to enemys
		screenRight = 0;
		screenLeft = 0;


	}


	/* move the Player left or right returns if it is at edge of the screen */
	int playerMoveLeft()
	{
		/* face left */
		sprite.spriteSetHorizontalFlip(1);
		move = 1;

		/* if we are at the left end, just scroll the screen */
		if (position.fX < border)
		{
			return 1;
		}
		else
		{
			/* else move left */
			position.fX -= xvel;
			return 0;
		}
	}

	int playerMoveRight()
	{
		/* face right */
		sprite.spriteSetHorizontalFlip(0);
		move = 1;

		/* if we are at the right end, just scroll the screen */
		if (position.fX > (240 - 16 - border))
		{
			return 1;
		}
		else
		{
			/* else move right */
			position.fX += xvel;
			return 0;
		}
	}

	void playerStop()
	{
		move = 0;
		frame = 0;
		counter = 7;
		xvel = 0;
		sprite.spriteSetOffset(frame);
	}

	/* start the koopa jumping, unless already fgalling */
	void playerJump()
	{
		if (!falling)
		{
			yvel = -jumpHeight;
			falling = 1;

			emitterJumpEffect.fX = IntegerToFixed(position.fX + 7);//Move the emiter to the players x pos.
			emitterJumpEffect.fY = IntegerToFixed(position.fY + 31);//Move the emiter to the players y pos.
			for (int i = 0; i < 32; ++i)
			{
				ParticleEmit(particlesJumpEffect[i], emitterJumpEffect);
				jumpParticleOAMStart[i] = jumpParticleOAM;
			}
		}
	}
	void playerBounce()
	{
		yvel = -(jumpHeight >> 1) ;

	}

	

	void playerCollision()
	{
		s32 pX = ((position.fX + xvel) >> 3) + (iXScroll >> 3);
		s32 pY = ((position.fY + yvel) >> 3) + (iYScroll >> 3);


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
			//position.fY--;
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


		if (KeyDown(A))
		{
			playerJump();
			

			
		}

		s32 xDir = GetAxis(HORIZONTAL);


		screenRight = 0;
		screenLeft = 0;


		switch (xDir)
		{
			// Moving Right
		case 1:
		{

			if (KeyDown(B))
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.fX;
				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					if (playerMoveRight())
					{
						iXScroll += xvel;
						screenRight = 1;

						//Keep the particles in the same spot
						for (int i = 0; i < 32; ++i)
						{

							particlesJumpEffect[i].fX -= IntegerToFixed(xvel);
							SetObjectPosition(&jumpParticleOAMStart[i], FixedToInteger(particlesJumpEffect[i].fX), FixedToInteger(particlesJumpEffect[i].fY));//Move particle

						}

					}
				}
			}
			else if (playerMoveRight())
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.fX;
				}
				else
				{
					xvel = walkSpeed;
					iXScroll += xvel;
					screenRight = 1;
					animationDelay = walkAnimationDelay;

					//Keep the particles in the same spot
					for (int i = 0; i < 32; ++i)
					{
						particlesJumpEffect[i].fX -= IntegerToFixed(xvel);
						SetObjectPosition(&jumpParticleOAMStart[i], FixedToInteger(particlesJumpEffect[i].fX), FixedToInteger(particlesJumpEffect[i].fY));//Move particle
					}
				}
			}
			else 
			{
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 || collisionMap[IITR] > 0 || collisionMap[IIBR] > 0)
				{
					--position.fX;
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
			if (KeyDown(B))
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.fX;
				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					if (playerMoveLeft())
					{
						iXScroll -= xvel;
						screenLeft = 1;
						//Keep the particles in the same spot
						for (int i = 0; i < 32; ++i)
						{

							particlesJumpEffect[i].fX += IntegerToFixed(xvel);
							SetObjectPosition(&jumpParticleOAMStart[i], FixedToInteger(particlesJumpEffect[i].fX), FixedToInteger(particlesJumpEffect[i].fY));//Move particle

						}
					}
				}
			}
			else if (playerMoveLeft())
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.fX;
				}
				else
				{
					xvel = walkSpeed;
					iXScroll -= xvel;
					screenLeft = 1;
					animationDelay = walkAnimationDelay;

					//Keep the particles in the same spot
					for (int i = 0; i < 32; ++i)
					{
						particlesJumpEffect[i].fX += IntegerToFixed(xvel);
						SetObjectPosition(&jumpParticleOAMStart[i], FixedToInteger(particlesJumpEffect[i].fX), FixedToInteger(particlesJumpEffect[i].fY));//Move particle
					}
				}
			}
			else
			{
				//Left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0 || collisionMap[IITL] > 0 || collisionMap[IIBL] > 0)
				{
					++position.fX;
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
			if (invulnerable == 0)
			{
				playerStop(); 
			}

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
			position.fY += yvel;
			yvel += gravity;
		}

		if (move || invulnerable)
		{
			counter++;
			if (counter >= animationDelay)
			{
				frame = frame + frameSkip;
				if (frame > frameSkip)
				{
					frame = 0;
				}
				sprite.spriteSetOffset(frame);
				counter = 0;
			}
		}
		

		//Jump particle update.
		for (int i = 0; i < 32; ++i)
		{
			UpdateParticleOneShot(particlesJumpEffect[i], emitterJumpEffect, g_frameTime, g_pixels2Meter, g_gravity);//Updates each particle.
		
			SetObjectPosition(&jumpParticleOAMStart[i], FixedToInteger(particlesJumpEffect[i].fX), FixedToInteger(particlesJumpEffect[i].fY));//Move particle
		
			u32 jumpFrameID = (1 << 9) - particlesJumpEffect[i].u32Lifespan;//Set the frame ID based on the particles life.
			jumpFrameID = jumpFrameID << 4 >> 9;//Set the frame ID based on the particles life.
			jumpParticleOAMStart[i].u16Attribute2 = SetAttribute2(32 + jumpFrameID, 0, 1);//Change the particle frame.

			if (particlesJumpEffect[i].fY < 160)//Stops the particles appearing at the top of the screen.
			{
				particlesJumpEffect[i].fY = 160;
				particlesJumpEffect[i].fX = 0;
			}
		
		}

		playerCollision();
		sprite.spriteSetPosition(position.fX, position.fY);

		REGISTRY_BACKGROUND_OFF_SET[0].s16X = iXScroll;
		REGISTRY_BACKGROUND_OFF_SET[0].s16Y = iYScroll;
		REGISTRY_BACKGROUND_OFF_SET[1].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(iXScroll), iXSrollBackground2Offset));
		REGISTRY_BACKGROUND_OFF_SET[2].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(iXScroll), iXSrollBackground3Offset));
		
	}



};

#endif//__PLAYER_H__