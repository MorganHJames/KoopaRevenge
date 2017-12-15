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

	int xvel;
	int walkSpeed;
	int runSpeed;
	int runDistance;
	int move;
	int falling;
	int yvel;
	int jumpHeight;
	int gravity;
	int counter;
	int frame;
	int flip;
	int animationDelay;
	int walkAnimationDelay;
	int alive;
	int runAnimationDelay;


	void enemyInitialization(SpriteManager& a_spriteManager, Player a_player, int objMem)
	{
		oSprite.Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[a_spriteManager.objectAttributeMemoryFree()];
		oSprite.Attribute->u16Attribute0 = SetAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		oSprite.Attribute->u16Attribute1 = SetAttribute1(0, 0, ATTRIBUTE1_SIZE_1);
		
		spawnEnemy(a_player);
		falling = 0;
		runDistance = 100;
		move = 0;
		xvel = 0;
		yvel = 0;
		flip = 0;
		alive = 1;
		gravity = 1;
		frame = 64;
		jumpHeight = 11;
		counter = 0;
		walkSpeed = 1;
		runSpeed = 2;
		animationDelay = 8;
		walkAnimationDelay = 8;
		runAnimationDelay = 4;
	}

	void spawnEnemy(Player a_player)
	{

		int pallete = 0;
		v2Position.fY = 0;//Sets the enemy's y to be 0 so its at the top of the screen and wont spawn in any terrain.

		int side = QuasiRandomRange(0, 1000);//Picks a side for the player to spawn on.

		if (side > 500)//Left side chosen.
		{
			side = QuasiRandomRange(-1000, -300);
		}
		else//Right side chosen.
		{
			side = QuasiRandomRange(300, 1000);
		}
		if (side % 2 == 0)
		{
			pallete = 2;
		}
		else
		{
			pallete = 3;
		}


		oSprite.Attribute->u16Attribute2 = SetAttribute2(64, 1, pallete);
		v2Position.fX = side;
	}

	void enemyMoveLeft()
	{
		/* face left */
		flip = 1;
		//move = 1;
		v2Position.fX -= xvel;
	}

	void enemyMoveRight()
	{
		/* face right */
		flip = 0;
		//move = 1;
		v2Position.fX += xvel;
	}

	void enemyJump()
	{
		if (!falling)
		{
			move = 0;
			frame = 80;
			yvel = -jumpHeight;
			falling = 1;
		}
	}

	void enemyStop()
	{
		move = 0;
		frame = 64;
		counter = 7;
		xvel = 0;
		oSprite.spriteSetOffset(frame);
	}

	void gotHit(Player& a_player)
	{
		Vector4 playerFeet = { a_player.position.fX, a_player.position.fY + 32, 16 , 8 };
		Vector4 enemyHead = { v2Position.fX, v2Position.fY, 16 , 8 };
		//Hurt by player
		if (playerFeet.x < enemyHead.x + enemyHead.w &&
			playerFeet.x + playerFeet.w > enemyHead.x &&
			playerFeet.y < enemyHead.y + enemyHead.h &&
			playerFeet.h + playerFeet.y > enemyHead.y  && (a_player.yvel != 0))
		{

			alive = 0;
			// collision detected!
			a_player.playerBounce();
			move = 0;
			a_player.score++;
			frame = 84;
			falling = 1;
			yvel = -jumpHeight;
			

		}
	}
	void enemyAI(Player& a_player)
	{
		s32 pX = ((v2Position.fX + xvel) >> 3) + (a_player.iXScroll >> 3);
		s32 pY = ((v2Position.fY + yvel) >> 3) + (a_player.iYScroll >> 3);

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

		s32 BL = pX + pY + (collisionMapWidth << 1);
		s32 BR = pX + pY + (collisionMapWidth << 1) + 2;

		s32 ITL = pX + pY;
		s32 IBL = pX + pY + collisionMapWidth;

		s32 ITR = pX + pY + 2;
		s32 IBR = pX + pY + collisionMapWidth + 2;

		if (alive)
		{
			gotHit(a_player);
		}

		if (alive)
		{
			gotHit(a_player);
			//Down collision
			if (collisionMap[BL] > 0 || collisionMap[BR] > 0)
			{
				yvel = 0;
				falling = 0;
				move = 1;
				//position.fY--;
			}
			else
			{
				/* he is falling now */
				falling = 1;
			}

			////Up collision
			if (collisionMap[TL] > 0 || collisionMap[TR] > 0)
			{
				yvel = 0;

			}

			//Running right
			if (a_player.position.fX - runDistance > v2Position.fX)
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0)
				{
					--v2Position.fX;
					enemyJump();

				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					enemyMoveRight();

				}
			}
			//Walk right
			else if (a_player.position.fX > v2Position.fX)
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0)
				{
					--v2Position.fX;
					enemyJump();
				}
				else
				{
					xvel = walkSpeed;
					animationDelay = runAnimationDelay;
					enemyMoveRight();

				}
			}
			//Stop
			else if (a_player.position.fX == v2Position.fX)
			{
				enemyStop();
			}

			//Running left
			if (FixedToInteger(a_player.position.fX) + runDistance < FixedToInteger(v2Position.fX))
			{
				//left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0)
				{
					++v2Position.fX;
					enemyJump();
				}
				else
				{
					xvel = runSpeed;
					animationDelay = runAnimationDelay;
					enemyMoveLeft();

				}
			}
			//Walk left
			else if (a_player.position.fX < v2Position.fX)
			{
				//left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0)
				{
					++v2Position.fX;
					enemyJump();
				}
				else
				{
					xvel = walkSpeed;
					animationDelay = runAnimationDelay;
					enemyMoveLeft();

				}
			}
			//Stop
			else if (a_player.position.fX == v2Position.fX)
			{
				enemyStop();
			}

		}


	}

	void hurtPlayer(Player& a_player, Enemy2& a_enemy2, Enemy3& a_enemy3 )
	{
		Vector4 player = { a_player.position.fX, a_player.position.fY, 16 , 32 };
		Vector4 enemy = { this->v2Position.fX, this->v2Position.fY, 16 , 16 };
		Vector4 enemy2 = { a_enemy2.position.fX, a_enemy2.position.fY, 16 , 16 };
		Vector4 enemy3 = { a_enemy3.position.fX, a_enemy3.position.fY, 16 , 16 };
		//Hurt by player
		if (
			(player.x < enemy.x + enemy.w &&
			player.x + player.w > enemy.x &&
			player.y < enemy.y + enemy.h &&
			player.h + player.y > enemy.y && alive == 1 )
			
			||

			(player.x < enemy2.x + enemy2.w &&
			player.x + player.w > enemy2.x &&
			player.y < enemy2.y + enemy2.h &&
			player.h + player.y > enemy2.y && a_enemy2.alive == 1 )
			
			||

			(player.x < enemy3.x + enemy3.w &&
			player.x + player.w > enemy3.x &&
			player.y < enemy3.y + enemy3.h &&
			player.h + player.y > enemy3.y && a_enemy3.alive == 1)
			
			)
		{
			
			if (a_player.invulnerable == 0)
			{
				a_player.lives--;
				a_player.frameSkip = 16;
				a_player.invulnerable = 1;
				
			}
			
			
		}
		else
		{
			a_player.frameSkip = 8;
			a_player.invulnerable = 0;
		}
	}
		
	/* update the koopa */
	void enemyUpdate(Player& a_player, Enemy2& a_enemy2, Enemy3& a_enemy3)
	{
		//sprite flip didn't work for the enemy for some unannounced reason.
		oSprite.Attribute->u16Attribute1 = SetAttribute1(v2Position.fX, flip, ATTRIBUTE1_SIZE_1);
		
		enemyAI(a_player);
		hurtPlayer(a_player, a_enemy2, a_enemy3);
		if (move)
		{
			counter++;
			if (counter >= animationDelay)
			{
				frame += 4;

				if (frame > 76)
				{
					frame = 68;
				}
				counter = 0;
			}
		}

		/* update y position and speed if falling */
		if (falling)
		{
			v2Position.fY += yvel;
			yvel += gravity;
		}


		if (a_player.screenLeft)
		{
			v2Position.fX += a_player.xvel;
		}
		if (a_player.screenRight)
		{
			v2Position.fX -= a_player.xvel;
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
			spawnEnemy(a_player);
			alive = 1;
		}
		oSprite.spriteSetOffset(frame);
	}



};

#endif//__ENEMY_H__