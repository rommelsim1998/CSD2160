/******************************************************************************
* \file			Wall_Blue.h
* \brief		This file declares the Wall_Blue class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef WALLBLUE_H
#define WALLBLUE_H

#include "Constants.h"

class Wall_Blue : public GameObject
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
	Wall_Blue() = delete;
	Wall_Blue(int);
	~Wall_Blue();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif