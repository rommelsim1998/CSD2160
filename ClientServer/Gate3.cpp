/******************************************************************************/
/*!
\file		Gate3.cpp
\brief		This is where the gate that responds to Button.cpp is created. The
			gate will move up when a player/box is standing on the button [STATE_PRESSED]
			and close when nothing is standing on it. [STATE_NONE]
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
 * @brief Constructor of a Gate3 GameObject.
 *
 * @param id - id of the object
 * @param state - state of the gate
 * @param innerState - innerstate of the gate
 * @counter - time for gate to remain open
 * @chargeCounter - counter to close gate
 * @return void
 */
Gate3::Gate3(int id, int type) : GameObject(type, id), state{ STATE_NONE }, innerState{ GATE_INNER_STATE_ON_ENTER }, counter{ GATE_IDLE_TIME }, chargeCounter{0.0f}
{}
/**
 * @brief Destructor of a Gate3 GameObject.
 *
 * @param void
 * @return void
 */

Gate3::~Gate3()
{}
/**
 * @brief Gate State Machine for this timer gate. The order will be STATE_GOING_UP -> STATE_GOING_DOWN
 *
 * @param void
 * @return void
 */

void Gate3::GateStateMachine()
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
			counter = 1.0f;
			SetIsCollidable(false);
			break;

		case GATE_INNER_STATE_ON_UPDATE:
			counter -= g_dt;
			chargeCounter += g_dt;
			if (counter < 0)
			{
				innerState = GATE_INNER_STATE_ON_EXIT;
				chargeCounter = 1.0f;
				counter = 1.0f;
			}
			break;

		case GATE_INNER_STATE_ON_EXIT:
			AEVec2 ExitVel = GetVelocity();
			ExitVel.y = 0.0f;
			SetVelocity(ExitVel);
			counter -= g_dt;
			if (counter < 0)
			{
				innerState = GATE_INNER_STATE_ON_ENTER;
				state = STATE_PRESSED;
			}
			break;
		}
	}
	else if (state == STATE_GOING_DOWN)
	{
		switch (innerState)
		{
		case GATE_INNER_STATE_ON_ENTER:
			AEVec2 DEnterVel = GetVelocity();
			DEnterVel.y = -GRAVITY;
			SetVelocity(DEnterVel);
			innerState = GATE_INNER_STATE_ON_UPDATE;
			SetIsCollidable(true);
			break;

		case GATE_INNER_STATE_ON_UPDATE:
			chargeCounter = chargeCounter - g_dt;
			if (chargeCounter < 0.0f)
			{
				innerState = GATE_INNER_STATE_ON_EXIT;
			}
			break;
		case GATE_INNER_STATE_ON_EXIT:
			AEVec2 DExitVel = GetVelocity();
			DExitVel.y = 0.0f;
			SetVelocity(DExitVel);
			AEVec2 resPos = GetRestartPos();
			SetPosition(resPos);
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

GATE_INNER_STATE Gate3::GetInnerGateState()
{
	return innerState;
}
/**
 * @brief Set the innerstate of the gate with the value that is passed
 *
 * @param GATE_INNER_STATE
 * @return void
 */

void Gate3::SetInnerState(GATE_INNER_STATE in)
{
	innerState = in;
}
/**
 * @brief Set state of the gate with the value that is passed
 *
 * @param GATE_STATE
 * @return void
 */

void Gate3::SetState(GATE_STATE something)
{
	state = something;
}
/**
 * @brief Return the current state of the gate
 *
 * @param void
 * @return GATE_STATE
 */
GATE_STATE Gate3::GetGateState()
{
	return state;
}
/**
 * @brief Initializes the gate's initial velocity, state, innerState, counter, resetposition, gravity and whether it is collidable
 *
 * @param void
 * @return void
 */
void Gate3::GameObjectInitialize()
{
	SetScale(50.0f); 
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
	SetState(STATE_NONE);
	SetInnerState(GATE_INNER_STATE_ON_ENTER);
	counter = 0.0f;
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
	SetHasGravity(false);
	SetIsCollidable(true);

}
/**
 * @brief update the game object's bounding box and makes the gate moving according to it's state
 * @param void
 * @return void
 */
void Gate3::GameObjectUpdate()
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
 * @brief Drawing the Gate3 game object.
 *
 * @param void
 * @return void
 */
void Gate3::GameObjectDraw()
{
	AEMtx33 mGate3Scale;
	float Gate3scale = GetScale();

	AEMtx33Scale(&mGate3Scale, Gate3scale, Gate3scale);

	SetMScale(mGate3Scale);

	AEVec2 Gate3pos = GetPosition();
	AEMtx33 mGate3Trans;
	AEMtx33Trans(&mGate3Trans, Gate3pos.x, Gate3pos.y);
	SetMTrans(mGate3Trans);
}
