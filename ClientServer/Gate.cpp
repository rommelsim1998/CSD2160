/******************************************************************************/
/*!
\file		Gate.cpp
\brief		This is supposed to act like a trigger gate such that when the player
			activates the gate by colliding with the lever from lever.cpp
			it will remain open till the player collides once again with the lever and deactivates it.

\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

const float			GRAVITY = 5.0f;
const float		GATE_IDLE_TIME = 1.0f;
using _cm = CollisionManager;
using _em = EntityManager;

/**
 * @brief Constructor of a Gate GameObject.
 *
 * @param id - id of the object
 * @param state - state of the gate
 * @param innerState - innerstate of the gate
 * @counter - time for gate to remain open
 * @return void
 */

Gate::Gate(int id) : GameObject(TYPE_LEVER_GATE, id), state{ STATE_NONE }, innerState{ GATE_INNER_STATE_ON_ENTER }, counter{ GATE_IDLE_TIME }
{}
/**
 * @brief Destructor of a Gate GameObject.
 *
 * @param void
 * @return void
 */

Gate::~Gate()
{}

/**
 * @brief Gate state machine that makes the gate move and sets the appropriate state at the end STATE_TRIGGERED
 *		  or STATE_NONE at the end of each state depending on the situation
 *
 * @param void
 * @return void
 */

void Gate::GateStateMachine()
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
				counter = 3.0f;
			}
			break;

		case GATE_INNER_STATE_ON_EXIT:
			AEVec2 ExitVel = GetVelocity();
			ExitVel.y = 0.0f;
			SetVelocity(ExitVel);
			if (counter < 0)
			{
				innerState = GATE_INNER_STATE_ON_ENTER;
				state = STATE_TRIGGERED;
			}
			counter -= g_dt;
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

GATE_INNER_STATE Gate::GetInnerGateState()
{
	return innerState;
}
/**
 * @brief Set the innerstate of the gate with the value that is passed
 *
 * @param GATE_INNER_STATE
 * @return void
 */

void Gate::SetInnerState(GATE_INNER_STATE in)
{
	innerState = in;
}
/**
 * @brief Set state of the gate with the value that is passed
 *
 * @param GATE_STATE
 * @return void
 */

void Gate::SetState(GATE_STATE something)
{
	state = something;
}
/**
 * @brief Return the current state of the gate
 *
 * @param void
 * @return GATE_STATE
 */

GATE_STATE Gate::GetGateState()
{
	return state;
}
/**
 * @brief Initializes the gate's initial velocity, state, gravity and whether it is collidable. restart positione.
 *
 * @param void
 * @return void
 */

void Gate::GameObjectInitialize()
{
	SetScale(50.0f); 
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
	SetState(STATE_NONE);
	SetHasGravity(false);
	SetIsCollidable(true);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
	SetInnerState(GATE_INNER_STATE_ON_ENTER);
	counter = GATE_IDLE_TIME;
}
/**
 * @brief update the game object's bounding box and makes the gate moving according to it's state
 * @param void
 * @return void
 */

void Gate::GameObjectUpdate()
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
 * @brief Drawing the gate game object.
 *
 * @param void
 * @return void
 */

void Gate::GameObjectDraw()
{
	AEMtx33 mGateScale;
	float Gatescale = GetScale();

	AEMtx33Scale(&mGateScale, Gatescale, Gatescale);

	SetMScale(mGateScale);

	AEVec2 Gatepos = GetPosition();
	AEMtx33 mGateTrans;
	AEMtx33Trans(&mGateTrans, Gatepos.x, Gatepos.y);
	SetMTrans(mGateTrans);
}
