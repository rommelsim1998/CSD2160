/******************************************************************************
* \file			Player.h
* \brief		This file declares the Player class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Constants.h"

class Player : public GameObject{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	int test;
	float playerSpeed = 200.0f;
	bool isStanding = false;
	bool pull = false;
	Color startingColor = Color::COLOR_GREY;
	int playerid = -1;

public:
	/*===================================*
				Constructors
	*====================================*/
	Player() = delete;
	Player(int);
	~Player();

	/*===================================*
					Accessors
	*====================================*/
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
	void SetisStanding(bool);
	bool GetPull() const;
	void SetPull(bool);
};

#endif