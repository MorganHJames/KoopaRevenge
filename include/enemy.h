//\===========================================================================================
//\ File: enemy.h
//\ Author: Morgan James
//\ Date Created: 08/12/2017
//\ Brief: A header that contains the class declaration and prototypes for the enemys.
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

/* a struct for the koopa's logic and behavior */
class Enemy
{
private:
public:
	/* the actual sprite attribute info */
	Sprite oSprite;

	/* the x and y postion */
	Vector2 v2Position;

	fixed fXVelocity;
	fixed fYVelocity;
	fixed fGravity;
	fixed fWalkSpeed;
	fixed fRunSpeed;

	s32 s32RunDistance;
	s32 s32JumpHeight;

	BOOL bMove;
	BOOL bFalling;
	BOOL bFlip;
	BOOL bAlive;
	BOOL bGotHit;
	
	u8 u8Counter;
	u8 u8Frame;
	u8 u8AnimationDelay;
	u8 u8WalkAnimationDelay;
	u8 u8RunAnimationDelay;

	//Particles
	fixed fParticleGravity;
	fixed fParticleFrameTime;
	fixed fParticelMeterToPixel;

	Emitter oEmitterCoinEffect;
	Particle oParticlesCoinEffect[1];
	ObjectAttribute oCoinParticleOAM;
	ObjectAttribute* poCoinParticleOAMStart;

	void EnemyInitialization(SpriteManager& a_rSpriteManager, Player a_player)
	{
		oSprite.poAttribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.ObjectAttributeMemoryFree()];
		oSprite.poAttribute->u16Attribute0 = SetAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		oSprite.poAttribute->u16Attribute1 = SetAttribute1(0, 0, ATTRIBUTE1_SIZE_1);
		
		SpawnEnemy(a_player);
	
		fXVelocity = 0;
		fYVelocity = 0;
		fGravity = 1;
		fWalkSpeed = 1;
		fRunSpeed = 2;

		s32JumpHeight = 11;
		s32RunDistance = 100;

		bFalling = 0;
		bMove = 0;
		bFlip = 0;
		bAlive = 1;
		bGotHit = 0;

		u8Counter = 0;
		u8Frame = 64;
		u8AnimationDelay = 8;
		u8WalkAnimationDelay = 8;
		u8RunAnimationDelay = 4;

		// --- Particles ---
		fParticleGravity = -0x9CC;
		fParticleFrameTime = 0x04;
		fParticelMeterToPixel = IntegerToFixed(5);

		oEmitterCoinEffect.fY = 160;
		oEmitterCoinEffect.fX = 0;
		poCoinParticleOAMStart = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.ObjectAttributeMemoryFree()];
		ObjectHide(&MEMORY_OBJECT_ATTRIBUTE_MEMORY[2]);
		ObjectHide(&MEMORY_OBJECT_ATTRIBUTE_MEMORY[4]);
		ObjectHide(&MEMORY_OBJECT_ATTRIBUTE_MEMORY[6]);
	}

	void SpawnEnemy(Player a_player)
	{
		u8 u8Palette = 0;
		v2Position.fY = 0;//Sets the enemy's y to be 0 so its at the top of the screen and wont spawn in any terrain.

		s32 s32Side = QuasiRandomRange(0, 1000);//Picks a side for the player to spawn on.

		if (s32Side > 500)//Left side chosen.
		{
			s32Side = QuasiRandomRange(-1000, -300);
		}
		else//Right side chosen.
		{
			s32Side = QuasiRandomRange(300, 1000);
		}
		if (s32Side % 2 == 0)
		{
			u8Palette = 2;
		}
		else
		{
			u8Palette = 3;
		}

		oSprite.poAttribute->u16Attribute2 = SetAttribute2(64, 1, u8Palette);
		v2Position.fX = s32Side;
	}

	void EnemyMoveLeft()
	{
		/* face left */
		bFlip = 1;
		//move = 1;
		v2Position.fX -= fXVelocity;
	}

	void EnemyMoveRight()
	{
		/* face right */
		bFlip = 0;
		//move = 1;
		v2Position.fX += fXVelocity;
	}

	void EnemyJump()
	{
		if (!bFalling)
		{
			bMove = 0;
			u8Frame = 80;
			fYVelocity = -s32JumpHeight;
			bFalling = 1;
		}
	}

	void EnemyStop()
	{
		bMove = 0;
		u8Frame = 64;
		u8Counter = 7;
		fXVelocity = 0;
		oSprite.SpriteSetOffset(u8Frame);
	}

	void GotHit(Player& a_rPlayer)
	{
		Vector4 v4PlayerFeet = { a_rPlayer.v2Position.fX, a_rPlayer.v2Position.fY + 32, 16 , 8 };
		Vector4 v4EnemyHead = { v2Position.fX, v2Position.fY, 16 , 8 };
		//Hurt by player
		if (v4PlayerFeet.fX < v4EnemyHead.fX + v4EnemyHead.fW &&
			v4PlayerFeet.fX + v4PlayerFeet.fW > v4EnemyHead.fX &&
			v4PlayerFeet.fY < v4EnemyHead.fY + v4EnemyHead.fH &&
			v4PlayerFeet.fH + v4PlayerFeet.fY > v4EnemyHead.fY  && (a_rPlayer.fYVelocity != 0))
		{
			bAlive = 0;
			// collision detected!
			a_rPlayer.PlayerBounce();
			bMove = 0;
			a_rPlayer.u16Score++;
			u8Frame = 84;
			bFalling = 1;
			fYVelocity = -s32JumpHeight;

			oEmitterCoinEffect.fX = IntegerToFixed(v2Position.fX + 7);//Move the emiter to the players x pos.
			oEmitterCoinEffect.fY = IntegerToFixed(v2Position.fY - 63);//Move the emiter to the players y pos.
			for (u32 u32I = 0; u32I < 1; ++u32I)
			{
				CoinParticleEmit(oParticlesCoinEffect[u32I], oEmitterCoinEffect);
				poCoinParticleOAMStart[u32I] = oCoinParticleOAM;
			}
			bGotHit = 1;
		}
	}

	void EnemyAI(Player& a_rPlayer)
	{
		fixed fEnemyWorldX = ((v2Position.fX + fXVelocity) >> 3) + (a_rPlayer.s32XScroll >> 3);
		fixed fEnemyWorldY = ((v2Position.fY + fYVelocity) >> 3) + (a_rPlayer.s32YScroll >> 3);

		/* account for wraparound */
		while (fEnemyWorldX >= collisionMapWidth)
		{
			fEnemyWorldX -= collisionMapWidth;
		}
		while (fEnemyWorldY >= collisionMapHeight)
		{
			fEnemyWorldY -= collisionMapHeight;
		}
		while (fEnemyWorldX < 0)
		{
			fEnemyWorldX += collisionMapWidth;
		}
		while (fEnemyWorldY < 0)
		{
			fEnemyWorldY += collisionMapHeight;
		}

		fEnemyWorldY *= collisionMapWidth;

		fixed fTopLeft = fEnemyWorldX + fEnemyWorldY;
		fixed fTopRight = (fEnemyWorldX + fEnemyWorldY) + 2;

		fixed fBottomLeft = fEnemyWorldX + fEnemyWorldY + (collisionMapWidth << 1);
		fixed fBottomRight = fEnemyWorldX + fEnemyWorldY + (collisionMapWidth << 1) + 2;

		fixed fInnerTopLeft = fEnemyWorldX + fEnemyWorldY;
		fixed fInnerBottomLeft = fEnemyWorldX + fEnemyWorldY + collisionMapWidth;

		fixed fInnerTopRight = fEnemyWorldX + fEnemyWorldY + 2;
		fixed fInnerBottomRight = fEnemyWorldX + fEnemyWorldY + collisionMapWidth + 2;

		if (bAlive)
		{
			GotHit(a_rPlayer);
		}
		if (bAlive)
		{
			GotHit(a_rPlayer);
			//Down collision
			if (collisionMap[fBottomLeft] > 0 || 
				collisionMap[fBottomRight] > 0)
			{
				fYVelocity = 0;
				bFalling = 0;
				bMove = 1;
				//position.fY--;
			}
			else
			{
				/* he is falling now */
				bFalling = 1;
			}

			////Up collision
			if (collisionMap[fTopLeft] > 0 || 
				collisionMap[fTopRight] > 0)
			{
				fYVelocity = 0;
			}

			//Running right
			if (a_rPlayer.v2Position.fX - s32RunDistance > v2Position.fX)
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 || 
					collisionMap[fInnerBottomRight] > 0)
				{
					--v2Position.fX;
					EnemyJump();
				}
				else
				{
					fXVelocity = fRunSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					EnemyMoveRight();
				}
			}
			//Walk right
			else if (a_rPlayer.v2Position.fX > v2Position.fX)
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 || 
					collisionMap[fInnerBottomRight] > 0)
				{
					--v2Position.fX;
					EnemyJump();
				}
				else
				{
					fXVelocity = fWalkSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					EnemyMoveRight();
				}
			}
			//Stop
			else if (a_rPlayer.v2Position.fX == v2Position.fX)
			{
				EnemyStop();
			}

			//Running left
			if (FixedToInteger(a_rPlayer.v2Position.fX) + s32RunDistance < FixedToInteger(v2Position.fX))
			{
				//left collision
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0)
				{
					++v2Position.fX;
					EnemyJump();
				}
				else
				{
					fXVelocity = fRunSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					EnemyMoveLeft();
				}
			}
			//Walk left
			else if (a_rPlayer.v2Position.fX < v2Position.fX)
			{
				//left collision
				if (collisionMap[fInnerTopLeft] > 0 || 
					collisionMap[fInnerBottomLeft] > 0)
				{
					++v2Position.fX;
					EnemyJump();
				}
				else
				{
					fXVelocity = fWalkSpeed;
					u8AnimationDelay = u8RunAnimationDelay;
					EnemyMoveLeft();
				}
			}
			//Stop
			else if (a_rPlayer.v2Position.fX == v2Position.fX)
			{
				EnemyStop();
			}
		}
	}

	/* update the koopa */
	void EnemyUpdate(Player& a_rPlayer)
	{
		//Coin particle update.
		if (bGotHit)
		{
			for (u32 u32I = 0; u32I < 1; ++u32I)
			{
				UpdateCoinParticleOneShot(oParticlesCoinEffect[u32I], oEmitterCoinEffect, fParticleFrameTime, fParticelMeterToPixel, fParticleGravity);//Updates each particle.
				poCoinParticleOAMStart[u32I].u16Attribute1 = SetAttribute1(FixedToInteger(oParticlesCoinEffect[u32I].fX), 0, ATTRIBUTE1_SIZE_1);
				poCoinParticleOAMStart[u32I].u16Attribute0 = SetAttribute0(FixedToInteger(oParticlesCoinEffect[u32I].fY), 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);

				u32 u32CoinFrameID = (1 << 9) - oParticlesCoinEffect[u32I].u32Lifespan;//Set the frame ID based on the particles life.
				u32CoinFrameID = u32CoinFrameID << 4 >> 9;//Set the frame ID based on the particles life.
				poCoinParticleOAMStart[u32I].u16Attribute2 = SetAttribute2(160 + u32CoinFrameID, 0, 6);//Change the particle frame.
				if (oParticlesCoinEffect[u32I].fY < 160)//Stops the particles appearing at the top of the screen.
				{
					oParticlesCoinEffect[u32I].fY = 160;
					oParticlesCoinEffect[u32I].fX = 0;
				}
			}
		}

		//sprite flip didn't work for the enemy for some unannounced reason.
		oSprite.poAttribute->u16Attribute1 = SetAttribute1(v2Position.fX, bFlip, ATTRIBUTE1_SIZE_1);
		
		EnemyAI(a_rPlayer);
		
		if (bMove)
		{
			u8Counter++;
			if (u8Counter >= u8AnimationDelay)
			{
				u8Frame += 4;

				if (u8Frame > 76)
				{
					u8Frame = 68;
				}
				u8Counter = 0;
			}
		}

		/* update y position and speed if falling */
		if (bFalling)
		{
			v2Position.fY += fYVelocity;
			fYVelocity += fGravity;
		}

		if (a_rPlayer.bScreenLeft)
		{
			v2Position.fX += a_rPlayer.fXVelocity;
		}
		if (a_rPlayer.bScreenRight)
		{
			v2Position.fX -= a_rPlayer.fXVelocity;
		}
		if (v2Position.fX >= 0 && v2Position.fX <= 240)
		{
			oSprite.SpriteSetPosition(v2Position.fX, v2Position.fY);
		}
		else
		{
			oSprite.SpriteSetPosition(0, 160);
		}
		if (v2Position.fY > 150)
		{
			SpawnEnemy(a_rPlayer);
			bAlive = 1;
		}
		oSprite.SpriteSetOffset(u8Frame);
	}
};

#endif//__ENEMY_H__