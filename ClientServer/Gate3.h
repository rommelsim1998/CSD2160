#pragma once

/******************************************************************************/
/*!
\file		Gate3.h
\brief		Header file for Gate3.cpp.This Gate works with Button object from Button.cpp
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "GameObject.h"
#include "GateStateList.h"

class Gate3 : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	enum GATE_STATE state;
	enum GATE_INNER_STATE innerState;
	float counter;
	float chargeCounter;

public:
	/*===================================*
				Constructors
	*====================================*/
	Gate3() = delete;
	Gate3(int,int);
	~Gate3();
	GATE_STATE GetGateState();
	GATE_INNER_STATE GetInnerGateState();
	void SetState(GATE_STATE);
	void SetInnerState(GATE_INNER_STATE);
	void GateStateMachine();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

