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

/* a struct for the koopa's logic and behavior */
class Player
{
private:
public:
	/* the actual sprite attribute info */
	Sprite oSprite;

	/* the x and y postion */
	Vector2 v2Position;

	s32 s32XScroll;
	s32 s32YScroll;
	s32 s32Border;
	u16 u16Score;
	s32 s32JumpHeight;

	fixed fXSrollBackground2Offset;
	fixed fXSrollBackground3Offset;
	fixed fWalkSpeed;
	fixed fRunSpeed;
	fixed fXVelocity;
	fixed fYVelocity;
	fixed fGravity;

	u8 u8Frame;//which frame of the animation he is on 
	u8 u8AnimationDelay;//the number of frames to wait before flipping
	u8 u8FrameSkip;
	u8 u8Lives;
	u8 u8Counter;/* the animation counter counts how many frames until we flip */
	u8 u8WalkAnimationDelay;
	u8 u8RunAnimationDelay;

	/* whether the koopa is moving right now or not */
	BOOL bMove;
	BOOL bScreenRight;
	BOOL bScreenLeft;
	BOOL bFalling;
	BOOL bInvulnerable;

	//Particles
	fixed fParticleGravity;
	fixed fParticleFrameTime;
	fixed fParticelMeterToPixel;

	Emitter oEmitterJumpEffect;
	Particle oParticlesJumpEffect[32];
	ObjectAttribute oJumpParticleOAM;
	ObjectAttribute* poJumpParticleOAMStart;

	void playerInitialization(SpriteManager& a_spriteManager)
	{
		oSprite.poAttribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_spriteManager.ObjectAttributeMemoryFree()];
		oSprite.poAttribute->u16Attribute0 = SetAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);
		oSprite.poAttribute->u16Attribute1 = SetAttribute1(120, 0, ATTRIBUTE1_SIZE_2);
		oSprite.poAttribute->u16Attribute2 = SetAttribute2(0, 1, 0);

	
		v2Position.fX = 120;
		v2Position.fY = 100;

		fXVelocity = 0;
		fYVelocity = 0;
		fWalkSpeed = 1;
		fRunSpeed = 2;
		fXSrollBackground2Offset = FixedDivide(IntegerToFixed(75), IntegerToFixed(100));
		fXSrollBackground3Offset = FixedDivide(IntegerToFixed(5), IntegerToFixed(10));
		fGravity = 1;

		s32JumpHeight = 11;
		s32XScroll = 0;
		s32YScroll = 80;
		s32Border = 40;
		u16Score = 0;

		u8Lives = 3;
		u8WalkAnimationDelay = 8;
		u8RunAnimationDelay = 4;
		u8Frame = 0;
		u8AnimationDelay = 8;
		u8FrameSkip = 8;

		bMove = 0;
		u8Counter = 0;
		bFalling = 0;
		bInvulnerable = 0;
		//passed info to enemys
		bScreenRight = 0;
		bScreenLeft = 0;

		// --- Particles ---
		fParticleGravity = -0x9CC;
		fParticleFrameTime = 0x04;
		fParticelMeterToPixel = IntegerToFixed(5);

		oEmitterJumpEffect.fY = 0;
		oEmitterJumpEffect.fX = 0;
		poJumpParticleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[96];

	}

	/* move the Player left or right returns if it is at edge of the screen */
	int PlayerMoveLeft()
	{
		/* face left */
		oSprite.SpriteSetHorizontalFlip(1);
		bMove = 1;

		/* if we are at the left end, just scroll the screen */
		if (v2Position.fX < s32Border)
		{
			return 1;
		}
		else
		{
			/* else move left */
			v2Position.fX -= fXVelocity;
			return 0;
		}
	}

	int PlayerMoveRight()
	{
		/* face right */
		oSprite.SpriteSetHorizontalFlip(0);
		bMove = 1;

		/* if we are at the right end, just scroll the screen */
		if (v2Position.fX > (240 - 16 - s32Border))
		{
			return 1;
		}
		else
		{
			/* else move right */
			v2Position.fX += fXVelocity;
			return 0;
		}
	}

	void PlayerStop()
	{
		bMove = 0;
		u8Frame = 0;
		u8Counter = 7;
		fXVelocity = 0;
		oSprite.SpriteSetOffset(u8Frame);
	}

	/* start the koopa jumping, unless already fgalling */
	void PlayerJump()
	{
		if (!bFalling)
		{
			fYVelocity = -s32JumpHeight;
			bFalling = 1;

			oEmitterJumpEffect.fX = IntegerToFixed(v2Position.fX + 7);//Move the emiter to the players x pos.
			oEmitterJumpEffect.fY = IntegerToFixed(v2Position.fY + 31);//Move the emiter to the players y pos.
			for (u32 u32I = 0; u32I < 32; ++u32I)
			{
				ParticleEmit(oParticlesJumpEffect[u32I], oEmitterJumpEffect);
				poJumpParticleOAMStart[u32I] = oJumpParticleOAM;
			}
		}
	}

	void PlayerBounce()
	{
		fYVelocity = -(s32JumpHeight >> 1) ;
	}

	void PlayerCollision()
	{
		fixed fPlayerWorldX = ((v2Position.fX + fXVelocity) >> 3) + (s32XScroll >> 3);
		fixed fPlayerWorldY = ((v2Position.fY + fYVelocity) >> 3) + (s32YScroll >> 3);

		/* account for wraparound */
		while (fPlayerWorldX >= collisionMapWidth)
		{
			fPlayerWorldX -= collisionMapWidth;
		}
		while (fPlayerWorldY >= collisionMapHeight)
		{
			fPlayerWorldY -= collisionMapHeight;
		}
		while (fPlayerWorldX < 0)
		{
			fPlayerWorldX += collisionMapWidth;
		}
		while (fPlayerWorldY < 0)
		{
			fPlayerWorldY += collisionMapHeight;
		}

		fPlayerWorldY *= collisionMapWidth;


		fixed fTopLeft = fPlayerWorldX + fPlayerWorldY;
		fixed fTopRight = (fPlayerWorldX + fPlayerWorldY) + 2;

		fixed fBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 2);
		fixed fBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 2) + 2;

		fixed fInnerTopLeft = fPlayerWorldX + fPlayerWorldY;
		fixed fInnerBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + collisionMapWidth;

		fixed fInnerInnerTopLeft = fPlayerWorldX + fPlayerWorldY + collisionMapWidth;
		fixed fInnerInnerBottomLeft = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1);

		fixed fInnerTopRight = fPlayerWorldX + fPlayerWorldY + 2;
		fixed fInnerBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + collisionMapWidth + 2;

		fixed fInnerInnerTopRight = fPlayerWorldX + fPlayerWorldY + 2 + collisionMapWidth;
		fixed fInnerInnerBottomRight = fPlayerWorldX + fPlayerWorldY + (collisionMapWidth << 1) + 2;

		//Down collision
		if (collisionMap[fBottomLeft] > 0 
			|| collisionMap[fBottomRight] > 0 )
		{
			fYVelocity = 0;
			bFalling = 0;
			//position.fY--;
		}
		else
		{
			/* he is falling now */
			bFalling = 1;
		}
		
		//Up collision
		if (collisionMap[fTopLeft] > 0 
			|| collisionMap[fTopRight] > 0)
		{
			fYVelocity = 0;
		}

		if (KeyDown(A))
		{
			PlayerJump();
		}

		s32 s32XDirection = GetAxis(HORIZONTAL);

		bScreenRight = 0;
		bScreenLeft = 0;

		switch (s32XDirection)
		{
		// Moving Right
		case 1:
		{
			if (KeyDown(B))
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 ||
					collisionMap[fInnerInnerBottomRight] > 0)
				{
					--v2Position.fX;
				}
				else
				{
					fXVelocity = fRunSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					if (PlayerMoveRight())
					{
						s32XScroll += fXVelocity;
						bScreenRight = 1;

						//Keep the particles in the same spot
						for (u32 u32I = 0; u32I < 32; ++u32I)
						{
							oParticlesJumpEffect[u32I].fX -= IntegerToFixed(fXVelocity);
							SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle
						}
					}
				}
			}
			else if (PlayerMoveRight())
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 || 
					collisionMap[fInnerInnerBottomRight] > 0)
				{
					--v2Position.fX;
				}
				else
				{
					fXVelocity = fWalkSpeed;
					s32XScroll += fXVelocity;
					bScreenRight = 1;
					u8AnimationDelay = u8WalkAnimationDelay;

					//Keep the particles in the same spot
					for (u32 u32I = 0; u32I < 32; ++u32I)
					{
						oParticlesJumpEffect[u32I].fX -= IntegerToFixed(fXVelocity);
						SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle
					}
				}
			}
			else 
			{
				if (collisionMap[fInnerTopRight] > 0 ||
					collisionMap[fInnerBottomRight] > 0 ||
					collisionMap[fInnerInnerTopRight] > 0 ||
					collisionMap[fInnerInnerBottomRight] > 0)
				{
					--v2Position.fX;
				}
				else
				{
					fXVelocity = fWalkSpeed;
					u8AnimationDelay = u8WalkAnimationDelay;
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
				if (collisionMap[fInnerTopLeft] > 0 ||
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)
				{
					++v2Position.fX;
				}
				else
				{
					fXVelocity = fRunSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					if (PlayerMoveLeft())
					{
						s32XScroll -= fXVelocity;
						bScreenLeft = 1;
						//Keep the particles in the same spot
						for (u32 u32I = 0; u32I < 32; ++u32I)
						{
							oParticlesJumpEffect[u32I].fX += IntegerToFixed(fXVelocity);
							SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle
						}
					}
				}
			}
			else if (PlayerMoveLeft())
			{
				//Left collision
				if (collisionMap[fInnerTopLeft] > 0 ||
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)
				{
					++v2Position.fX;
				}
				else
				{
					fXVelocity = fWalkSpeed;
					s32XScroll -= fXVelocity;
					bScreenLeft = 1;
					u8AnimationDelay = u8WalkAnimationDelay;

					//Keep the particles in the same spot
					for (u32 u32I = 0; u32I < 32; ++u32I)
					{
						oParticlesJumpEffect[u32I].fX += IntegerToFixed(fXVelocity);
						SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle
					}
				}
			}
			else
			{
				//Left collision
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0 ||
					collisionMap[fInnerInnerTopLeft] > 0 ||
					collisionMap[fInnerInnerBottomLeft] > 0)
				{
					++v2Position.fX;
				}
				else
				{
					fXVelocity = fWalkSpeed;
					u8AnimationDelay = u8WalkAnimationDelay;
				}
			}
			break;
		}
		// Not moving
		case 0:
		{
			if (bInvulnerable == 0)
			{
				PlayerStop(); 
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
	void PlayerUpdate()
	{
		/* update y position and speed if falling */
		if (bFalling)
		{
			v2Position.fY += fYVelocity;
			fYVelocity += fGravity;
		}

		if (bMove || bInvulnerable)
		{
			u8Counter++;
			if (u8Counter >= u8AnimationDelay)
			{
				u8Frame = u8Frame + u8FrameSkip;
				if (u8Frame > u8FrameSkip)
				{
					u8Frame = 0;
				}
				oSprite.SpriteSetOffset(u8Frame);
				u8Counter = 0;
			}
		}

		//Jump particle update.
		for (u32 u32I = 0; u32I < 32; ++u32I)
		{
			UpdateParticleOneShot(oParticlesJumpEffect[u32I], oEmitterJumpEffect, fParticleFrameTime, fParticelMeterToPixel, fParticleGravity);//Updates each particle.
		
			SetObjectPosition(&poJumpParticleOAMStart[u32I], FixedToInteger(oParticlesJumpEffect[u32I].fX), FixedToInteger(oParticlesJumpEffect[u32I].fY));//Move particle
		
			u32 u32JumpFrameID = (1 << 9) - oParticlesJumpEffect[u32I].u32Lifespan;//Set the frame ID based on the particles life.
			u32JumpFrameID = u32JumpFrameID << 4 >> 9;//Set the frame ID based on the particles life.
			poJumpParticleOAMStart[u32I].u16Attribute2 = SetAttribute2(32 + u32JumpFrameID, 0, 1);//Change the particle frame.

			if (oParticlesJumpEffect[u32I].fY < 160)//Stops the particles appearing at the top of the screen.
			{
				oParticlesJumpEffect[u32I].fY = 160;
				oParticlesJumpEffect[u32I].fX = 0;
			}
		
		}

		PlayerCollision();
		oSprite.SpriteSetPosition(v2Position.fX, v2Position.fY);

		REGISTRY_BACKGROUND_OFF_SET[0].s16X = s32XScroll;
		REGISTRY_BACKGROUND_OFF_SET[0].s16Y = s32YScroll;
		REGISTRY_BACKGROUND_OFF_SET[1].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(s32XScroll), fXSrollBackground2Offset));
		REGISTRY_BACKGROUND_OFF_SET[2].s16X = FixedToInteger(FixedMultiply(IntegerToFixed(s32XScroll), fXSrollBackground3Offset));
	}
};

#endif//__PLAYER_H__