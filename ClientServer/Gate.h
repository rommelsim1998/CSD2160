#pragma once
/******************************************************************************/
/*!
\file		Gate.h
\brief		Header file for Gate.cpp that works with Lever.cpp
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "GameObject.h"
#include "GateStateList.h"

class Gate : public GameObject
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
	Gate() = delete;
	Gate(int);
	~Gate();
	GATE_STATE GetGateState();
	GATE_INNER_STATE GetInnerGateState();
	void SetState(GATE_STATE);
	void SetInnerState(GATE_INNER_STATE);
	void GateStateMachine();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

