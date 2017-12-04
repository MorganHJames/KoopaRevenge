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

/* a struct for the koopa's logic and behavior */
class Player {
private:
public:
	/* the actual sprite attribute info */
	Sprite* sprite;

	/* the x and y postion */
	Vector2 position;

	s32 iXScroll;
	fixed iXSrollBackground2Offset;
	fixed iXSrollBackground3Offset;

	int walkSpeed;

	int runSpeed;

	int walkAnimationDelay;

	int runAnimationDelay;

	int xvel;

	/* the koopa's y velocity in 1/256 pixels/second */
	int yvel;

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

	void playerInitialization()
	{
		/* setup the sprite image and palette */
		/* load the palette from the image into palette memory*/
		directMemoryAccessWordCopy(PALETTE_SPRITE_MEMORY, koopaPal, koopaPalLen);

		/* load the image into char block 0 */
		directMemoryAccessWordCopy(&TILEBLOCK_MEMORY[4][0], &koopaTiles[0], koopaTilesLen);

		position.x = 120;
		position.y = 113;
		xvel = 1;
		yvel = 0;
		walkSpeed = 1;
		runSpeed = 2;
		iXScroll = 0;
		iXSrollBackground2Offset = fixedDivide(integerToFixed(75), integerToFixed(100));
		iXSrollBackground3Offset = fixedDivide(integerToFixed(5), integerToFixed(10));
		walkAnimationDelay = 8;
		runAnimationDelay = 4;
		gravity = 50;
		border = 40;
		frame = 0;
		move = 0;
		counter = 0;
		falling = 0;
		animationDelay = 8;
		sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[0];
		sprite->Attribute->attribute0 = setAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_TALL);
		sprite->Attribute->attribute1 = setAttribute1(120, 0, ATTRIBUTE1_SIZE_2);
		sprite->Attribute->attribute2 = setAttribute2(0, 0, 0);
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
		frame = 0;
		counter = 7;
		sprite->spriteSetOffset(frame);
	}

	/* update the koopa */
	void playerUpdate()
	{
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
		
		sprite->spriteSetPosition(position.x, position.y);

		REGISTRY_BACKGROUND_OFF_SET[0].s16X = iXScroll;
	    REGISTRY_BACKGROUND_OFF_SET[1].s16X = fixedToInteger(fixedMultiply(integerToFixed(iXScroll), iXSrollBackground2Offset));
		REGISTRY_BACKGROUND_OFF_SET[2].s16X = fixedToInteger(fixedMultiply(integerToFixed(iXScroll), iXSrollBackground3Offset));
	
		switch (getAxis(HORIZONTAL))
		{
			// Moving Right
		case 1:
		{
			if (keyDown(B))
			{
				xvel = runSpeed;
				animationDelay = runAnimationDelay;
				if (playerMoveRight())
				{
					iXScroll += xvel;
				}
			}
			else if (playerMoveRight())
			{
				xvel = walkSpeed;
				iXScroll += xvel;
				animationDelay = walkAnimationDelay;
			}
			else
			{
				xvel = walkSpeed;
				animationDelay = walkAnimationDelay;
			}
			break;
		}
		// Moving left
		case -1:
		{
			if (keyDown(B))
			{
				xvel = runSpeed;
				animationDelay = runAnimationDelay;
				if (playerMoveLeft())
				{
					iXScroll -= xvel;
				}
			}
			else if (playerMoveLeft())
			{
				xvel = walkSpeed;
				iXScroll -= xvel;
				animationDelay = walkAnimationDelay;
			}
			else
			{
				xvel = walkSpeed;
				animationDelay = walkAnimationDelay;
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

};			

#endif//__PLAYER_H__