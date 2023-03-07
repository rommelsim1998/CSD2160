/******************************************************************************
* \file			ColorObj.h
* \brief		This file declares the ColorObj class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef COLOROBJ_H
#define COLOROBJ_H

#include "Constants.h"

class ColorObj : public GameObject
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
	ColorObj() = delete;
	ColorObj(int);
	~ColorObj();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif