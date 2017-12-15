//\===========================================================================================
//\ File: enemy.h
//\ Author: Morgan James
//\ Date Created: 08/12/2017
//\ Brief:
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
#include "enemy2.h"
#include "enemy3.h"


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
	
	u8 u8Counter;
	u8 u8Frame;
	u8 u8AnimationDelay;
	u8 u8WalkAnimationDelay;
	u8 u8RunAnimationDelay;

	void EnemyInitialization(SpriteManager& a_rSpriteManager, Player a_player)
	{
		oSprite.Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_rSpriteManager.objectAttributeMemoryFree()];
		oSprite.Attribute->u16Attribute0 = SetAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		oSprite.Attribute->u16Attribute1 = SetAttribute1(0, 0, ATTRIBUTE1_SIZE_1);
		
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

		u8Counter = 0;
		u8Frame = 64;
		u8AnimationDelay = 8;
		u8WalkAnimationDelay = 8;
		u8RunAnimationDelay = 4;
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

		oSprite.Attribute->u16Attribute2 = SetAttribute2(64, 1, u8Palette);
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
		oSprite.spriteSetOffset(u8Frame);
	}

	void GotHit(Player& a_rPlayer)
	{
		Vector4 v4PlayerFeet = { a_rPlayer.position.fX, a_rPlayer.position.fY + 32, 16 , 8 };
		Vector4 v4EnemyHead = { v2Position.fX, v2Position.fY, 16 , 8 };
		//Hurt by player
		if (v4PlayerFeet.fX < v4EnemyHead.fX + v4EnemyHead.fW &&
			v4PlayerFeet.fX + v4PlayerFeet.fW > v4EnemyHead.fX &&
			v4PlayerFeet.fY < v4EnemyHead.fY + v4EnemyHead.fH &&
			v4PlayerFeet.fH + v4PlayerFeet.fY > v4EnemyHead.fY  && (a_rPlayer.yvel != 0))
		{
			bAlive = 0;
			// collision detected!
			a_rPlayer.playerBounce();
			bMove = 0;
			a_rPlayer.score++;
			u8Frame = 84;
			bFalling = 1;
			fYVelocity = -s32JumpHeight;
		}
	}

	void EnemyAI(Player& a_rPlayer)
	{
		fixed fPX = ((v2Position.fX + fXVelocity) >> 3) + (a_rPlayer.iXScroll >> 3);
		fixed fPY = ((v2Position.fY + fYVelocity) >> 3) + (a_rPlayer.iYScroll >> 3);

		/* account for wraparound */
		while (fPX >= collisionMapWidth)
		{
			fPX -= collisionMapWidth;
		}
		while (fPY >= collisionMapHeight)
		{
			fPY -= collisionMapHeight;
		}
		while (fPX < 0)
		{
			fPX += collisionMapWidth;
		}
		while (fPY < 0)
		{
			fPY += collisionMapHeight;
		}

		fPY *= collisionMapWidth;

		fixed fTopLeft = fPX + fPY;
		fixed fTopRight = (fPX + fPY) + 2;

		fixed fBottomLeft = fPX + fPY + (collisionMapWidth << 1);
		fixed fBottomRight = fPX + fPY + (collisionMapWidth << 1) + 2;

		fixed fInnerTopLeft = fPX + fPY;
		fixed fInnerBottomLeft = fPX + fPY + collisionMapWidth;

		fixed fInnerTopRight = fPX + fPY + 2;
		fixed fInnerBottomRight = fPX + fPY + collisionMapWidth + 2;

		if (bAlive)
		{
			GotHit(a_rPlayer);
		}
		if (bAlive)
		{
			GotHit(a_rPlayer);
			//Down collision
			if (collisionMap[fBottomLeft] > 0 || collisionMap[fBottomRight] > 0)
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
			if (collisionMap[fTopLeft] > 0 || collisionMap[fTopRight] > 0)
			{
				fYVelocity = 0;
			}

			//Running right
			if (a_rPlayer.position.fX - s32RunDistance > v2Position.fX)
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 || collisionMap[fInnerBottomRight] > 0)
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
			else if (a_rPlayer.position.fX > v2Position.fX)
			{
				//Right collision
				if (collisionMap[fInnerTopRight] > 0 || collisionMap[fInnerBottomRight] > 0)
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
			else if (a_rPlayer.position.fX == v2Position.fX)
			{
				EnemyStop();
			}

			//Running left
			if (FixedToInteger(a_rPlayer.position.fX) + s32RunDistance < FixedToInteger(v2Position.fX))
			{
				//left collision
				if (collisionMap[fInnerTopLeft] > 0 || collisionMap[fInnerBottomLeft] > 0)
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
			else if (a_rPlayer.position.fX < v2Position.fX)
			{
				//left collision
				if (collisionMap[fInnerTopLeft] > 0 || collisionMap[fInnerBottomLeft] > 0)
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
			else if (a_rPlayer.position.fX == v2Position.fX)
			{
				EnemyStop();
			}
		}
	}

	void HurtPlayer(Player& a_rPlayer, Enemy2& a_rEnemy2, Enemy3& a_rEnemy3 )
	{
		Vector4 v4Player = { a_rPlayer.position.fX, a_rPlayer.position.fY, 16 , 32 };
		Vector4 v4Enemy = { v2Position.fX, v2Position.fY, 16 , 16 };
		Vector4 v4Enemy2 = { a_rEnemy2.v2Position.fX, a_rEnemy2.v2Position.fY, 16 , 16 };
		Vector4 v4Enemy3 = { a_rEnemy3.v2Position.fX, a_rEnemy3.v2Position.fY, 16 , 16 };
		//Hurt by player
		if (
			(v4Player.fX < v4Enemy.fX + v4Enemy.fW &&
			v4Player.fX + v4Player.fW > v4Enemy.fX &&
			v4Player.fY < v4Enemy.fY + v4Enemy.fH &&
			v4Player.fH + v4Player.fY > v4Enemy.fY && bAlive == 1 )
			
			||

			(v4Player.fX < v4Enemy2.fX + v4Enemy2.fW &&
			v4Player.fX + v4Player.fW > v4Enemy2.fX &&
			v4Player.fY < v4Enemy2.fY + v4Enemy2.fH &&
			v4Player.fH + v4Player.fY > v4Enemy2.fY && a_rEnemy2.bAlive == 1 )
			
			||

			(v4Player.fX < v4Enemy3.fX + v4Enemy3.fW &&
			v4Player.fX + v4Player.fW > v4Enemy3.fX &&
			v4Player.fY < v4Enemy3.fY + v4Enemy3.fH &&
			v4Player.fH + v4Player.fY > v4Enemy3.fY && a_rEnemy3.bAlive == 1)
			
			)
		{
			if (a_rPlayer.invulnerable == 0)
			{
				a_rPlayer.lives--;
				a_rPlayer.frameSkip = 16;
				a_rPlayer.invulnerable = 1;
			}
		}
		else
		{
			a_rPlayer.frameSkip = 8;
			a_rPlayer.invulnerable = 0;
		}
	}
		
	/* update the koopa */
	void EnemyUpdate(Player& a_rPlayer, Enemy2& a_rEnemy2, Enemy3& a_rEnemy3)
	{
		//sprite flip didn't work for the enemy for some unannounced reason.
		oSprite.Attribute->u16Attribute1 = SetAttribute1(v2Position.fX, bFlip, ATTRIBUTE1_SIZE_1);
		
		EnemyAI(a_rPlayer);
		HurtPlayer(a_rPlayer, a_rEnemy2, a_rEnemy3);
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

		if (a_rPlayer.screenLeft)
		{
			v2Position.fX += a_rPlayer.xvel;
		}
		if (a_rPlayer.screenRight)
		{
			v2Position.fX -= a_rPlayer.xvel;
		}
		if (v2Position.fX >= 0 && v2Position.fX <= 240)
		{
			oSprite.spriteSetPosition(v2Position.fX, v2Position.fY);
		}
		else
		{
			oSprite.spriteSetPosition(0, 160);
		}
		if (v2Position.fY > 150)
		{
			SpawnEnemy(a_rPlayer);
			bAlive = 1;
		}
		oSprite.spriteSetOffset(u8Frame);
	}
};

#endif//__ENEMY_H__