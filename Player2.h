#pragma once
/******************************************************************************
* \file			Player2.h
* \brief		This file declares the Player2 class
* \author		

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef PLAYER2_H
#define PLAYER2_H

#include "Constants.h"

class Player2 : public GameObject {
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	int test;
	float playerSpeed = 200.0f;
	bool isStanding = false;
	bool pull = false;
	Color startingColor = Color::COLOR_YELLOW;
	int playerid = -1;

public:
	/*===================================*
				Constructors
	*====================================*/
	Player2() = delete;
	Player2(int);
	~Player2();

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
