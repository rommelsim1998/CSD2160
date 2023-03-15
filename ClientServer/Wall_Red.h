/******************************************************************************
* \file			Wall_Red.h
* \brief		This file declares the Wall_Red class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef WALLRED_H
#define WALLRED_H

#include "Constants.h"

class Wall_Red : public GameObject
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
	Wall_Red() = delete;
	Wall_Red(int);
	~Wall_Red();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif