/******************************************************************************/
/*!
\file		Gate2.cpp
\brief		Gate2 refers to the timer gate where the time it takes to open the gate and remain open
			is equivalent to the GATE_IDLE_TIME. When the player collides with the lever1 object, it will open and remain open
			for the duration of the GATE_IDLE_TIME. Upon reaching the specified duration, the gate will start to close and
			the lever1 object will revert back to normal.
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

const float			GRAVITY = 5.0f;
const float		GATE_IDLE_TIME = 3.0f;
using _em = EntityManager;
using _cm = CollisionManager;
/**
 * @brief Constructor of a Gate2 GameObject.
 *
 * @param id - id of the object
 * @param state - state of the gate
 * @param innerState - innerstate of the gate
 * @counter - time for gate to remain open
 * @return void
 */

Gate2::Gate2(int id) : GameObject(TYPE_LEVER_GATE1, id), state{ STATE_NONE }, innerState{ GATE_INNER_STATE_ON_ENTER }, counter{ GATE_IDLE_TIME }
{}
/**
 * @brief Destructor of a Gate2 GameObject.
 *
 * @param void
 * @return void
 */

Gate2::~Gate2()
{}


/**
 * @brief Gate State Machine for this timer gate. The order will be STATE_GOING_UP -> STATE_GOING_DOWN
 *
 * @param void
 * @return void
 */

void Gate2::GateStateMachine()
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
			counter = 3.0f;
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

GATE_INNER_STATE Gate2::GetInnerGateState()
{
	return innerState;
}
/**
 * @brief Set the innerstate of the gate with the value that is passed
 *
 * @param GATE_INNER_STATE
 * @return void
 */

void Gate2::SetInnerState(GATE_INNER_STATE in)
{
	innerState = in;
}
/**
 * @brief Set state of the gate with the value that is passed
 *
 * @param GATE_STATE
 * @return void
 */
void Gate2::SetState(GATE_STATE something)
{
	state = something;
}
/**
 * @brief Return the current state of the gate
 *
 * @param void
 * @return GATE_STATE
 */
GATE_STATE Gate2::GetGateState()
{
	return state;
}
/**
 * @brief Initializes the gate's initial velocity, state, gravity and whether it is collidable
 *
 * @param void
 * @return void
 */
void Gate2::GameObjectInitialize()
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
void Gate2::GameObjectUpdate()
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

void Gate2::GameObjectDraw()
{
	AEMtx33 mGate2Scale;
	float Gate2scale = GetScale();

	AEMtx33Scale(&mGate2Scale, Gate2scale, Gate2scale);

	SetMScale(mGate2Scale);

	AEVec2 Gate2pos = GetPosition();
	AEMtx33 mGate2Trans;
	AEMtx33Trans(&mGate2Trans, Gate2pos.x, Gate2pos.y);
	SetMTrans(mGate2Trans);
}
