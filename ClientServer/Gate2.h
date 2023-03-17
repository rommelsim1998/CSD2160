#pragma once

/******************************************************************************/
/*!
\file		Gate2.h
\brief		Header file for Gate2.cpp that works with with Lever1.cpp
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "GameObject.h"
#include "GateStateList.h"

class Gate2 : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	enum GATE_STATE state;
	enum GATE_INNER_STATE innerState;
	float counter;

public:
	/*===================================*
				Constructors
	*====================================*/
	Gate2() = delete;
	Gate2(int);
	~Gate2();
	GATE_STATE GetGateState();
	GATE_INNER_STATE GetInnerGateState();
	void SetState(GATE_STATE);
	void SetInnerState(GATE_INNER_STATE);
	void GateStateMachine();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

