/******************************************************************************
* \file			Wall_Yellow.h
* \brief		This file declares the Wall_Yellow class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef WALLYELLOW_H
#define WALLYELLOW_H

#include "Constants.h"

class Wall_Yellow : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/

	int test;

public:
	/*===================================*
				Constructors
	*====================================*/
	Wall_Yellow() = delete;
	Wall_Yellow(int);
	~Wall_Yellow();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif