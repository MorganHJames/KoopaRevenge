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

class GameManager
{
private:
public:

	void HurtPlayer(Player& a_rPlayer, Enemy& a_rEnemy1, Enemy& a_rEnemy2, Enemy& a_rEnemy3)
	{
		Vector4 v4Player = { a_rPlayer.position.fX, a_rPlayer.position.fY, 16 , 32 };
		Vector4 v4Enemy1 = { a_rEnemy1.v2Position.fX, a_rEnemy1.v2Position.fY, 16 , 16 };
		Vector4 v4Enemy2 = { a_rEnemy2.v2Position.fX, a_rEnemy2.v2Position.fY, 16 , 16 };
		Vector4 v4Enemy3 = { a_rEnemy3.v2Position.fX, a_rEnemy3.v2Position.fY, 16 , 16 };
		//Hurt by player
		if (
			(v4Player.fX < v4Enemy1.fX + v4Enemy1.fW &&
				v4Player.fX + v4Player.fW > v4Enemy1.fX &&
				v4Player.fY < v4Enemy1.fY + v4Enemy1.fH &&
				v4Player.fH + v4Player.fY > v4Enemy1.fY && a_rEnemy1.bAlive == 1)

			||

			(v4Player.fX < v4Enemy2.fX + v4Enemy2.fW &&
				v4Player.fX + v4Player.fW > v4Enemy2.fX &&
				v4Player.fY < v4Enemy2.fY + v4Enemy2.fH &&
				v4Player.fH + v4Player.fY > v4Enemy2.fY && a_rEnemy2.bAlive == 1)

			||

			(v4Player.fX < v4Enemy3.fX + v4Enemy3.fW &&
				v4Player.fX + v4Player.fW > v4Enemy3.fX &&
				v4Player.fY < v4Enemy3.fY + v4Enemy3.fH &&
				v4Player.fH + v4Player.fY > v4Enemy3.fY && a_rEnemy3.bAlive == 1)
			)
		{
			if (a_rPlayer.invulnerable == 0)
			{
				a_rPlayer.lives--;
				a_rPlayer.frameSkip = 16;
				a_rPlayer.invulnerable = 1;
			}
		}
		else
		{
			a_rPlayer.frameSkip = 8;
			a_rPlayer.invulnerable = 0;
		}
	}

};

#endif//__GAME_MANAGER_H__