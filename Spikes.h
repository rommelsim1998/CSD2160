#ifndef SPIKES_H
#define SPIKES_H
/******************************************************************************
* \file			Spikes.h
* \brief		This file contains the declaration of the Spike object class.
*				it acts as the hazard that affects both player and enemy.
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "GameObject.h"

class Spikes : public GameObject
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
	Spikes() = delete;
	Spikes(int);
	~Spikes();

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif