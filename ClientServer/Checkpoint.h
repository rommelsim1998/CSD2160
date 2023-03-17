/******************************************************************************
* \file			Checkpoint.h
* \brief		This file declares the Checkpoint class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "GameObject.h"

class Checkpoint : public GameObject
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
	Checkpoint() = delete;
	Checkpoint(int);
	~Checkpoint();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif