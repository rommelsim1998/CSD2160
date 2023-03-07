#pragma once

/******************************************************************************/
/*!
\file		Lever1.h
\brief		Header file for Lever1.cpp [Lever that activates the Timer Gate from Gate2.cpp]
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <vector>
#include "GameObject.h"
#include "Gate2.h"

class Lever1 : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	// vector to store pointer address of Gates/Door
	std::vector<Gate2*> gate;
	bool IsActivated;
	float timer;


public:
	/*===================================*
				Constructors
	*====================================*/
	Lever1() = delete;
	Lever1(int);
	~Lever1();

	void ActivateGate();
	void UpdateGate();
	bool GetIsActivated();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};
