/******************************************************************************
* \file			Box.h
* \brief		This file declares the Box class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef BOX_H
#define BOX_H

#include "Constants.h"

class Box : public GameObject
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
	Box() = delete;
	Box(int);
	~Box();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif