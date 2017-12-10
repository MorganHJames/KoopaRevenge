//\===========================================================================================
//\ File: enemy3.h
//\ Author: Morgan James
//\ Date Created: 08/12/2017
//\ Brief:
//\===========================================================================================

#ifndef __ENEMY3_H__
#define __ENEMY3_H__

#include "sprite.h"
#include "gba_graphics.h"
#include "mario.h"
#include "gba_vector2.h"
#include "gba_input.h"
#include "backgroundFunctions.h"
#include "particleFunctions.h"
#include "particles.h"
#include "gba_vector4.h"


/* a struct for the koopa's logic and behavior */
class Enemy3
{
private:
public:

	/* the actual sprite attribute info */
	Sprite* sprite;

	/* the x and y postion */
	Vector2 position;

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
	u32 time;

	void enemyInitialization(Player a_player, int objMem)
	{
		sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[objMem];
		sprite->Attribute->attribute0 = setAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		sprite->Attribute->attribute1 = setAttribute1(0, 0, ATTRIBUTE1_SIZE_1);


		spawnEnemy(a_player);

		falling = 0;
		runDistance = 100;
		move = 0;
		time = 0;
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
		position.y = 0;//Sets the enemy's y to be 0 so its at the top of the screen and wont spawn in any terrain.

		int side = quasiRandomRange(0, 1000);//Picks a side for the player to spawn on.

		if (side > 500)//Left side chosen.
		{
			side = quasiRandomRange(-1000, -300);
		}
		else//Right side chosen.
		{
			side = quasiRandomRange(300, 1000);
		}
		if (side % 2 == 0)
		{
			pallete = 2;
		}
		else
		{
			pallete = 3;
		}


		sprite->Attribute->attribute2 = setAttribute2(64, 0, pallete);
		position.x = side;
	}

	void enemyMoveLeft()
	{
		/* face left */
		flip = 1;
		//move = 1;
		position.x -= xvel;
	}

	void enemyMoveRight()
	{
		/* face right */
		flip = 0;
		//move = 1;
		position.x += xvel;
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
		sprite->spriteSetOffset(frame);
	}

	void gotHit(Player& a_player)
	{
		Vector4 playerFeet = { a_player.position.x, a_player.position.y + 32, 16 , 8 };
		Vector4 enemyHead = { position.x, position.y, 16 , 8 };
		//Hurt by player
		if (playerFeet.x < enemyHead.x + enemyHead.w &&
			playerFeet.x + playerFeet.w > enemyHead.x &&
			playerFeet.y < enemyHead.y + enemyHead.h &&
			playerFeet.h + playerFeet.y > enemyHead.y  && a_player.yvel > 0)
		{
			alive = 0;
			// collision detected!
			a_player.playerBounce();
			move = 0;

			frame = 84;
			falling = 1;
			yvel = -jumpHeight;

		}
	}

	void hurtPlayer(Player& a_player)
	{
		Vector4 player = { a_player.position.x, a_player.position.y, 16 , 32 };
		Vector4 enemy = { position.x, position.y, 16 , 16 };
		//Hurt by player
		if (player.x < enemy.x + enemy.w &&
			player.x + player.w > enemy.x &&
			player.y < enemy.y + enemy.h &&
			player.h + player.y > enemy.y)
		{
			a_player.frameSkip = 16;
			a_player.invulnerable = 1;

			u32 time = TIMER_3_DATA;
		}
	}


	void enemyAI(Player& a_player)
	{
		s32 pX = ((position.x + xvel) >> 3) + (a_player.iXScroll >> 3);
		s32 pY = ((position.y + yvel) >> 3) + (a_player.iYScroll >> 3);

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
			hurtPlayer(a_player);
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
				//position.y--;
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
			if (a_player.position.x - runDistance > position.x)
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0)
				{
					--position.x;
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
			else if (a_player.position.x > position.x)
			{
				//Right collision
				if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0)
				{
					--position.x;
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
			else if (a_player.position.x == position.x)
			{
				enemyStop();
			}

			//Running left
			if (a_player.position.x + runDistance < position.x)
			{
				//left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0)
				{
					++position.x;
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
			else if (a_player.position.x < position.x)
			{
				//left collision
				if (collisionMap[ITL] > 0 || collisionMap[IBL] > 0)
				{
					++position.x;
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
			else if (a_player.position.x == position.x)
			{
				enemyStop();
			}

		}


	}

	/* update the koopa */
	void enemyUpdate(Player& a_player)
	{
		if (TIMER_3_DATA < (time + (TIMER_SECONED >> 8)))
		{
			a_player.frameSkip = 8;
			a_player.invulnerable = 0;
		}

		////sprite flip didn't work for the enemy for some unannounced reason.
		sprite->Attribute->attribute1 = setAttribute1(position.x, flip, ATTRIBUTE1_SIZE_1);
		sprite->spriteSetOffset(frame);
		enemyAI(a_player);
		

		
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
			position.y += yvel;
			yvel += gravity;
		}


		if (a_player.screenLeft)
		{
			position.x += a_player.xvel;
		}
		if (a_player.screenRight)
		{
			position.x -= a_player.xvel;
		}


		if (position.x > 0 && position.x < 240)
		{
			sprite->spriteSetPosition(position.x, position.y);

		}
		else
		{
			sprite->spriteSetPosition(0, 160);
		}
		if (position.y > 160)
		{
			spawnEnemy(a_player);
			alive = 1;
		}
	}



};

#endif//__ENEMY3_H__