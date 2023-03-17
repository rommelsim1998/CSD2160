/******************************************************************************
* \file			Wall_Green.h
* \brief		This file declares the Wall_Green class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef WALLGREEN_H
#define WALLGREEN_H

#include "Constants.h"

class Wall_Green : public GameObject
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
	Wall_Green() = delete;
	Wall_Green(int);
	~Wall_Green();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif