#pragma once

/******************************************************************************/
/*!
\file		Lever.h
\brief		Header file for Lever.cpp [Lever that activates the Trigger Gate from Gate.cpp]
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <vector>
#include "GameObject.h"
#include "Gate.h"

class Lever : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	// vector to store pointer address of Gates/Door
	std::vector<Gate*> gate;
	bool IsActivated;
	float timer;


public:
	/*===================================*
				Constructors
	*====================================*/
	Lever() = delete;
	Lever(int);
	~Lever();

	void ActivateGate();
	void UpdateGate();
	bool GetIsActivated();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};
