/******************************************************************************/
/*!
\file		Gate4.cpp
\brief		This works the same way as Gate3.cpp just that the button that activates
			it is the Button1 game object from Button1.cpp

\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

const float			GRAVITY = 5.0f;
const float		GATE_IDLE_TIME = 5.0f;
using _cm = CollisionManager;
/**
 * @brief Constructor of a Gate4 GameObject.
 *
 * @param id - id of the object
 * @param state - state of the gate
 * @param innerState - innerstate of the gate
 * @counter - time for gate to remain open
 * @return void
 */

Gate4::Gate4(int id) : GameObject(TYPE_BUTTON_GATE, id), state{ STATE_NONE }, innerState{ GATE_INNER_STATE_ON_ENTER }, counter{ GATE_IDLE_TIME }
{}
/**
 * @brief Destructor of a Gate4 GameObject.
 *
 * @param void
 * @return void
 */

Gate4::~Gate4()
{}

/**
 * @brief Gate State Machine for this timer gate. The order will be STATE_GOING_UP -> STATE_GOING_DOWN
 *
 * @param void
 * @return void
 */
void Gate4::GateStateMachine()
{
	if (state == STATE_GOING_UP)
	{
		switch (innerState)
		{
		case GATE_INNER_STATE_ON_ENTER:
			AEVec2 EnterVel = GetVelocity();
			EnterVel.y = GRAVITY;
			SetVelocity(EnterVel);
			innerState = GATE_INNER_STATE_ON_UPDATE;
			break;
		
		case GATE_INNER_STATE_ON_UPDATE:
			counter -= g_dt;
			if (counter < 0)
			{
				innerState = GATE_INNER_STATE_ON_EXIT;
			}
			break;

		case GATE_INNER_STATE_ON_EXIT:
			AEVec2 ExitVel = GetVelocity();
			ExitVel.y = 0.0f;
			SetVelocity(ExitVel);
			innerState = GATE_INNER_STATE_ON_ENTER;
			state = STATE_GOING_DOWN;
			break;
		}
	}
	else if (state == STATE_GOING_DOWN)
	{
		switch (innerState)
		{
		case GATE_INNER_STATE_ON_ENTER:
			counter = 1;
			AEVec2 DEnterVel = GetVelocity();
			DEnterVel.y = -GRAVITY;
			SetVelocity(DEnterVel);
			innerState = GATE_INNER_STATE_ON_UPDATE;
			break;

		case GATE_INNER_STATE_ON_UPDATE:
			counter -= g_dt;
			if (counter < 0)
			{
				innerState = GATE_INNER_STATE_ON_EXIT;
			}
			break;
		case GATE_INNER_STATE_ON_EXIT:
			counter = GATE_IDLE_TIME;
			AEVec2 DExitVel = GetVelocity();
			DExitVel.y = 0.0f;
			SetVelocity(DExitVel);
			state = STATE_NONE;
			innerState = GATE_INNER_STATE_ON_ENTER;
			break;
		}
	}
}
/**
 * @brief Returns which innerstate the gate is currently in
 *
 * @param void
 * @return GATE_INNER_STATE
 */

GATE_INNER_STATE Gate4::GetInnerGateState()
{
	return innerState;
}
/**
 * @brief Set the innerstate of the gate with the value that is passed
 *
 * @param GATE_INNER_STATE
 * @return void
 */

void Gate4::SetInnerState(GATE_INNER_STATE in)
{
	innerState = in;
}
/**
 * @brief Set state of the gate with the value that is passed
 *
 * @param GATE_STATE
 * @return void
 */

void Gate4::SetState(GATE_STATE something)
{
	state = something;
}
/**
 * @brief Return the current state of the gate
 *
 * @param void
 * @return GATE_STATE
 */

GATE_STATE Gate4::GetGateState()
{
	return state;
}
/**
 * @brief Initializes the gate's initial velocity, state, gravity
 *
 * @param void
 * @return void
 */

void Gate4::GameObjectInitialize()
{
	SetScale(50.0f); 
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
	SetState(STATE_NONE);
	SetHasGravity(false);
}
/**
 * @brief update the game object's bounding box and makes the gate moving according to it's state
 * @param void
 * @return void
 */

void Gate4::GameObjectUpdate()
{
	AABB boundbox;
	boundbox.min.x = -0.5f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.5f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.5f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.5f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
	GateStateMachine();
}
/**
 * @brief Drawing the gate4 game object.
 *
 * @param void
 * @return void
 */

void Gate4::GameObjectDraw()
{
	AEMtx33 mGate4Scale;
	float Gate4scale = GetScale();

	AEMtx33Scale(&mGate4Scale, Gate4scale, Gate4scale);

	SetMScale(mGate4Scale);

	AEVec2 Gate4pos = GetPosition();
	AEMtx33 mGate4Trans;
	AEMtx33Trans(&mGate4Trans, Gate4pos.x, Gate4pos.y);
	SetMTrans(mGate4Trans);
}
