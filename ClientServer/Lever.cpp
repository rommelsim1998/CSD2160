/******************************************************************************/
/*!
\file		Lever.cpp
\brief		This lever works together with the gate from Gate.cpp. When the player collides with the lever
			the lever will flip and the state of the gate will be set. It will remain flipped till the player once again
			collides with the lever and the appropriate gate state will be set as well.

\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "Constants.h"

using _em = EntityManager;
/**
 * @brief Constructor of the Lever object, timer - gate timer, IsActivated - gate is closed
 *
 * @param id - Lever object ID
 * @return void
 */

Lever::Lever(int id) : GameObject(TYPE_LEVER, id), IsActivated{false}, timer{0.0f}
{}
/**
 * @brief Destructor of the Lever object
 *
 * @param void
 * @return void
 */

Lever::~Lever()
{}
/**
 * @brief Sets the corresponding gate state depending on its current gate state which will allow the gate to
 *		  move up or down.
 *
 * @param void
 * @return void
 */

void Lever::ActivateGate()
{
	// call the function from Gate class to change the position of the gate as the player is colliding with the lever
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = true;
			theGate->SetState(STATE_GOING_UP);

		}
		else if(theGate->GetGateState() == STATE_TRIGGERED)
		{
			IsActivated = true;
			theGate->SetState(STATE_GOING_DOWN);
		}
	}
}
/**
 * @brief Updates the IsActivated status of the gate
 *
 * @param void
 * @return void
 */

void Lever::UpdateGate()
{
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = false;
		}
	}
}
/**
 * @brief Returns the value of IsActivated
 *
 * @param void
 * @return bool 1 - represents gate is activated and 0 - gate is not activated
 */

bool Lever::GetIsActivated()
{
	return IsActivated;
}
/**
 * @brief Initializes the Lever with the corresponding Gate from Gate.cpp. Sets the scale and initial velocity to 0.
 *
 * @param void
 * @return void
 */

void Lever::GameObjectInitialize()
{
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		GameObject* obj = it->second;
		if (obj->GetType() == TYPE_LEVER_GATE)
		{
			gate.push_back(dynamic_cast<Gate*>(obj));
		}
	}
	IsActivated = false;
	SetScale(50.0f);
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
}
/**
 * @brief Updates the lever's bounding box which the player will interact with
 *
 * @param void
 * @return void
 */

void Lever::GameObjectUpdate()
{
	UpdateGate();

	AABB boundbox;
	boundbox.min.x = -0.1f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.1f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.1f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.1f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
}
/**
 * @brief Draws the lever and flips it when the player activates the lever.
 *
 * @param void
 * @return void
 */

void Lever::GameObjectDraw() 
{
	AEMtx33 mLeverScale;
	float Leverscale = GetScale();
	if (IsActivated)
	{
		AEMtx33Scale(&mLeverScale, Leverscale, Leverscale); // flipped lever
	}
	else
	{
		AEMtx33Scale(&mLeverScale, -Leverscale, Leverscale);
	}
	SetMScale(mLeverScale);

	AEVec2 Leverpos = GetPosition();
	AEMtx33 mLeverTrans;
	AEMtx33Trans(&mLeverTrans, Leverpos.x, Leverpos.y);
	SetMTrans(mLeverTrans);
}
