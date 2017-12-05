//\===========================================================================================
//\ File: collision.h
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: 
//\===========================================================================================

#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "collisionMap.h"

#define COLLISION_X 1
#define COLLISION_Y 2


// Returns true if we have a collision tile at x,y
int pointCollision(int x, int y)
{
	
	int tid =  collisionMap[x];
	
	return ( tid == 1 || tid == 0);
}


// Test if there would be a collision given the bounding box and the proposed
// x and y offsets
int collisionTest(int x1, int y1, int x2, int y2, int xofs, int yofs)
{
	int result = 0;

	if (xofs > 0)
	{
		if (pointCollision(x2 + xofs, y1 ) || pointCollision(x2 + xofs, y2))
			result = COLLISION_X;
	}
	else if (xofs < 0)
	{
		if (pointCollision(x1 + xofs, y1 ) || pointCollision(x1 + xofs, y2 ))
			result = COLLISION_X;
	}

	if (yofs > 0)
	{
		if (pointCollision(x1, y2 + yofs) || pointCollision(x2, y2 + yofs))
			result = result | COLLISION_Y;
	}
	else if (yofs < 0)
	{
		if (pointCollision(x1, y1 + yofs) || pointCollision(x2, y1 + yofs))
			result = result | COLLISION_Y;
	}

	return result;
}

#endif //__COLLISION_H__