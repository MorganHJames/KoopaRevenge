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
#include "map.h"
#include "background.h"

/* a struct for the koopa's logic and behavior */
struct Player {
	/* the actual sprite attribute info */
	Sprite* sprite;

	/* the x and y postion */
	Vector2 position;

	/* the koopa's y velocity in 1/256 pixels/second */
	int yvel;

	/* the koopa's y acceleration in 1/256 pixels/second^2 */
	int gravity;

	/* which frame of the animation he is on */
	int frame;

	/* the number of frames to wait before flipping */
	int animation_delay;

	/* the animation counter counts how many frames until we flip */
	int counter;

	/* whether the koopa is moving right now or not */
	int move;

	/* the number of pixels away from the edge of the screen the koopa stays */
	int border;
	/* if the koopa is currently falling */
    int falling;
};			


void loadBackground()
{
	dma_word_cpy(PALETTE_BACKGROUND_MEMORY, background_palette, background_paletteLen);
	u16* tileMemoryLocation = tileBlockAddress(0);
	dma_word_cpy(tileMemoryLocation, background_data, background_dataLen);
	u16* tileMapMemoryLocation = tileMapBlockAddress(16);
	dma_word_cpy(tileMapMemoryLocation, map, map_dataLen);

	setBackgroundControlRegister(0, 0, 0, 0, 1, 16, 0, BACKGROUND_REGISTRY_SIZE_32x32);

}

void playerInitialization(Player* a_player)
{
	a_player->position.x = 120;
	a_player->position.y = 113;
	a_player->yvel = 0;
	a_player->gravity = 50;
	a_player->border = 40;
	a_player->frame = 0;
	a_player->move = 0;
	a_player->counter = 0;
	a_player->falling = 0;
	a_player->animation_delay = 8;
}

/* move the Player left or right returns if it is at edge of the screen */
int playerMoveLeft(Player* a_player)
{
	/* face left */
	spriteSetHorizontalFlip(a_player->sprite, 1);
	a_player->move = 1;

	/* if we are at the left end, just scroll the screen */
	if (a_player->position.x < a_player->border)
	{
		return 1;
	}
	else
	{
		/* else move left */
		a_player->position.x--;
		return 0;
	}
}
int playerMoveRight(Player* a_player)
{
	/* face right */
	spriteSetHorizontalFlip(a_player->sprite, 0);
	a_player->move = 1;

	/* if we are at the right end, just scroll the screen */
	if (a_player->position.x > (240 - 16 - a_player->border))
	{
		return 1;
	}
	else
	{
		/* else move right */
		a_player->position.x++;
		return 0;
	}
}

void playerStop(Player* a_player)
{
	a_player->move = 0;
	a_player->frame = 0;
	a_player->counter = 7;
	spriteSetOffset(a_player->sprite, a_player->frame);
}

/* update the koopa */
void playerUpdate(Player* a_player)
{
	if (a_player->move)
	{
		a_player->counter++;
		if (a_player->counter >= a_player->animation_delay)
		{
			a_player->frame = a_player->frame + 16;
			if (a_player->frame > 16)
			{
				a_player->frame = 0;
			}
			spriteSetOffset(a_player->sprite, a_player->frame);
			a_player->counter = 0;
		}
	}

	spriteSetPosition(a_player->sprite, a_player->position.x, a_player->position.y);
}

/* setup the sprite image and palette */
void playerSetupSpriteImage()
{
	/* load the palette from the image into palette memory*/

	dma_word_cpy(PALETTE_SPRITE_MEMORY, koopaPal, koopaPalLen);

	/* load the image into char block 0 */
	dma_word_cpy(&TILEBLOCK_MEMORY[4][0], &koopaTiles[0], koopaTilesLen);

}


#endif//__PLAYER_H__