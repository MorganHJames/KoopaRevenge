//\===========================================================================================
//\ File: main.cpp
//\ Author: Morgan James
//\ Date Created: 13/11/2017
//\ Brief: Contains the start point for the game.
//\===========================================================================================

#include "Intellisense.h"
#include "gba.h"
#include <string.h>

#include "sprite.h"

#include "koopa.h"//Sprite include.


int main()
{
	REGISTRY_DISPLAYCONTROL = DISPLAYCONTROL_BACKGROUNDMODE_0 | ENABLE_OBJECTS | DISPLAYCONTROL_VIDEOMODE_0 | MAPPINGMODE_1D;//Set the mode to 0 with background 0.

	//setup_background();//setup the background 0.

	//setup_sprite_image();//Setup the sprite image data.

	//sprite_clear();//clear all the sprites on screen now 

	//struct Koopa koopa;//Create the Koopa.
	//koopa_init(&koopa);//Initilize the Koopa.

	//int xscroll = 0;//Set initial scroll to 0.

	memcpy(PALETTE_SPRITE_MEMORY, koopaPal, koopaPalLen);
	memcpy(&TILEBLOCK_MEMORY[4][0], koopaTiles, koopaTilesLen);

	Sprite myDude;

	myDude.position.x = integerToFixed(120);
	myDude.position.y = integerToFixed(128);

	myDude.Attribute = &MEMORY_OBJECT_ATTRIBUTE_MEMORY[0];

	objectAttributeMemoryInitialize(MEMORY_OBJECT_ATTRIBUTE_MEMORY, 128);

	myDude.Attribute->attribute0 = setAttribute0(myDude.position.y, 0, 0, 0, ATTRIBUTE0_COLOR_4BPP, ATTRIBUTE0_SQUARE);
	myDude.Attribute->attribute1 = setAttribute1(myDude.position.x, 0, ATTRIBUTE1_SIZE_2);
	myDude.Attribute->attribute2 = setAttribute2(0, 0, 0);

	setObjectPosition(myDude.Attribute, fixedToUnsignedInteger(myDude.position.x), fixedToUnsignedInteger(myDude.position.y));
	

	while(1)//Loop forever.
	{
		pollKeys();

		myDude.position.x = fixedAddition(myDude.position.x, integerToFixed(getAxis(HORIZONTAL)));
		myDude.position.y = fixedSubtraction(myDude.position.y, integerToFixed(getAxis(VERTICAL)));

		setObjectPosition(myDude.Attribute, fixedToUnsignedInteger(myDude.position.x), fixedToUnsignedInteger(myDude.position.y));

		verticalSync();




	}

	return 0;
}