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


	void enemyInitialization()
	{
		sprite->Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[65];
		sprite->Attribute->attribute0 = setAttribute0(113, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
		sprite->Attribute->attribute1 = setAttribute1(120, 0, ATTRIBUTE1_SIZE_1);
		sprite->Attribute->attribute2 = setAttribute2(64, 0, 2);

		position.x = 5;
		position.y = 5;
	}


	/* update the koopa */
	void enemyUpdate()
	{


		sprite->spriteSetPosition(position.x, position.y);
	}



};

#endif//__ENEMY_H__