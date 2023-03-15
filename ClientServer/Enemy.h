#ifndef ENEMY_H
#define ENEMY_H

/******************************************************************************
* \file			Enemy.h
* \brief        This file contains the class declaration of the Enemy class
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The Enemy object is an object entity in the game that represents
*				the knights of King Mono.
*				It has the it's own simple AI state system.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

class Enemy : public GameObject {
private:
	/*===================================*
			Private - Data Members
	*====================================*/

	int horizontalDetectRange;		// Range of Horizontal Detection.
	float idleCounter;				// Counter for idle
	float moveCounter;				// Counter for movement
	ENEMY_STATE state;				// Current state
	ENEMY_STATE previousState;		// Previous state
	ENEMY_INNER_STATE innerState;

	// Detection box is from front of the enemy.
	AABB detectionBox;

public:

	/*===================================*
				Constructors
	*====================================*/
	Enemy() = delete;
	Enemy(int);
	~Enemy();

	/*===================================*
				Accessors
	*====================================*/
	ENEMY_STATE GetState() const;
	ENEMY_INNER_STATE GetInnerState() const;
	AABB GetDetectionBox() const;

	/*===================================*
				Mutators
	*====================================*/
	void SetState(ENEMY_STATE const);
	void SetPreviousState(ENEMY_STATE const);
	void SetInnerState(ENEMY_INNER_STATE const);
	void SetDetectionBox(AABB const);
	void SetMoveCounter(float const);

	void DecreaseIdleTime(float const);
	void DecreaseMoveTime(float const);

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;

private:
	void ChangeState();
};

#endif