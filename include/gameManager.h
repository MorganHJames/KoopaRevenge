//\===========================================================================================
//\ File: gameManager.h
//\ Author: Morgan James
//\ Date Created: 12/12/2017
//\ Brief: A header for some variables and functions used by or that use multiple things.
//\===========================================================================================

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "gba.h"
#include "enemy.h"
#include "player.h"

class GameManager//A class that will contain functions that will use multiple different objects.
{
private:
public:

	void HurtPlayer(Player& a_rPlayer, Enemy& a_rEnemy1, Enemy& a_rEnemy2, Enemy& a_rEnemy3)//Checks to see if any of the enemies are touching the player.
	{
		Vector4 v4Player = { a_rPlayer.v2Position.fX, a_rPlayer.v2Position.fY, 16 , 32 };//A vector4 that represents the bounding box for the player.
		Vector4 v4Enemy1 = { a_rEnemy1.v2Position.fX, a_rEnemy1.v2Position.fY, 16 , 16 };//A vector4 that represents the bounding box for enemy1.
		Vector4 v4Enemy2 = { a_rEnemy2.v2Position.fX, a_rEnemy2.v2Position.fY, 16 , 16 };//A vector4 that represents the bounding box for enemy2.
		Vector4 v4Enemy3 = { a_rEnemy3.v2Position.fX, a_rEnemy3.v2Position.fY, 16 , 16 };//A vector4 that represents the bounding box for enemy3.
		//Hurt by player
		if (
			(v4Player.fX < v4Enemy1.fX + v4Enemy1.fW &&
				v4Player.fX + v4Player.fW > v4Enemy1.fX &&
				v4Player.fY < v4Enemy1.fY + v4Enemy1.fH &&
				v4Player.fH + v4Player.fY > v4Enemy1.fY && a_rEnemy1.bAlive == 1)//If the player and enemy1 are colliding and the enemy is alive.

			||//Or.

			(v4Player.fX < v4Enemy2.fX + v4Enemy2.fW &&
				v4Player.fX + v4Player.fW > v4Enemy2.fX &&
				v4Player.fY < v4Enemy2.fY + v4Enemy2.fH &&
				v4Player.fH + v4Player.fY > v4Enemy2.fY && a_rEnemy2.bAlive == 1)//If the player and enemy2 are colliding and the enemy is alive.

			||//Or.

			(v4Player.fX < v4Enemy3.fX + v4Enemy3.fW &&
				v4Player.fX + v4Player.fW > v4Enemy3.fX &&
				v4Player.fY < v4Enemy3.fY + v4Enemy3.fH &&
				v4Player.fH + v4Player.fY > v4Enemy3.fY && a_rEnemy3.bAlive == 1)//If the player and enemy3 are colliding and the enemy is alive.
			)
		{
			if (a_rPlayer.bInvulnerable == 0)//If the player is not invulnerable.
			{
				a_rPlayer.u8Lives--;//Decrease lives.
				a_rPlayer.u8FrameSkip = 16;//Sets the players frame skip to 16 so it starts blinking.
				a_rPlayer.bInvulnerable = 1;//Make the player invulnerable.
			}
		}
		else//If the player is touching any enemies.
		{
			a_rPlayer.u8FrameSkip = 8;//Set the frame skip to 8 so the animation plays normally.
			a_rPlayer.bInvulnerable = 0;//Sets the player to become vulnerable.
		}
	}
};

#endif//__GAME_MANAGER_H__