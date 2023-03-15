/******************************************************************************
* \file          Cave7.h
* \brief         This file is the Declaration Game Object Cave6
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#pragma once

#include "GameObject.h"

class Cave7 : public GameObject
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
	Cave7() = delete;
	Cave7(int);
	~Cave7();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};