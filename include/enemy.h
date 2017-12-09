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


/* a struct for the koopa's logic and behavior */
class Enemy
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

	int runAnimationDelay;

	void enemyInitialization()
	{
		sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[65];
		sprite->Attribute->attribute0 = setAttribute0(0, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		sprite->Attribute->attribute1 = setAttribute1(0, 0, ATTRIBUTE1_SIZE_1);
		sprite->Attribute->attribute2 = setAttribute2(64, 0, 2);

		position.x = 5;
		position.y = 5;

		falling = 0;
		runDistance = 100;
		move = 0;

		xvel = 0;
		yvel = 0;
		flip = 0;
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

	void enemyAI(Player a_player)
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

		//Up collision
		if (collisionMap[TL] > 0 || collisionMap[TR] > 0)
		{
			yvel = 0;
		
		}
		
		//Running right
		if (a_player.position.x - runDistance > position.x)
		{
			//Right collision
			if (collisionMap[ITR] > 0 || collisionMap[IBR] > 0 )
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
		if (a_player.position.x + runDistance <  position.x)
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

	/* update the koopa */
	void enemyUpdate(Player a_player)
	{	
		//sprite flip didn't work for the enemy for some unannounced reason.
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
	}



};

#endif//__ENEMY_H__