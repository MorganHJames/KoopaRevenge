//\===========================================================================================
//\ File: collision.h
//\ Author: Morgan James
//\ Date Created: 04/12/2017
//\ Brief: 
//\===========================================================================================

#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

/* finds which tile a screen coordinate maps to, taking scroll into account */
unsigned short tile_lookup(int x, int y, int xscroll, int yscroll,
	const unsigned short* tilemap, int tilemap_w, int tilemap_h)
{

	/* adjust for the scroll */
	x += xscroll;
	y += yscroll;

	/* convert from screen coordinates to tile coordinates */
	x >>= 3;
	y >>= 3;

	/* account for wraparound */
	while (x >= tilemap_w)
	{
		x -= tilemap_w;
	}
	while (y >= tilemap_h)
	{
		y -= tilemap_h;
	}
	while (x < 0)
	{
		x += tilemap_w;
	}
	while (y < 0)
	{
		y += tilemap_h;
	}

	/* lookup this tile from the map */
	int index = y * tilemap_w + x;

	/* return the tile */
	return tilemap[index];
}

#endif //__COLLISION_H__