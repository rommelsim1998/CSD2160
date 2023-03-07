/******************************************************************************/
/*!
\file		Lever1.cpp
\brief		This lever1.cpp activates the timer gate from Gate2.cpp. It works quite similar to lever.cpp
			the only difference is that when player collides/activates the lever, the gate will automatically
			open and close by itself within a set duration therefore the player isn't required to collide
			with the lever to close the gate.
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

using _em = EntityManager;
/**
 * @brief Constructor of the Lever1 object
 *
 * @param id - Lever1 object ID, timer - gate timer, IsActivated - gate is closed
 * @return void
 */

Lever1::Lever1(int id) : GameObject(TYPE_LEVER1, id), IsActivated{false}, timer{0.0f}
{}
/**
 * @brief Destructor of the Lever1 object
 *
 * @param void
 * @return void
 */

Lever1::~Lever1()
{}
/**
 * @brief Sets the corresponding gate state depending on its current gate state which will allow the gate to
 *		  move up or down.
 *
 * @param void
 * @return void
 */

void Lever1::ActivateGate()
{
	// call the function from Gate class to change the position of the gate as the player is colliding with the lever
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate2* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = true;
			theGate->SetState(STATE_GOING_UP);

		}
		else if (theGate->GetGateState() == STATE_TRIGGERED)
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

void Lever1::UpdateGate()
{
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate2* theGate = gate[i];
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

bool Lever1::GetIsActivated()
{
	return IsActivated;
}
/**
 * @brief Initializes the Lever with the corresponding Gate from Gate2.cpp. Sets the scale and initial velocity to 0.
 *
 * @param void
 * @return void
 */

void Lever1::GameObjectInitialize()
{
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		GameObject* obj = it->second;
		if (obj->GetType() == TYPE_LEVER_GATE1)
		{
			gate.push_back(dynamic_cast<Gate2*>(obj));
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

void Lever1::GameObjectUpdate()
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

void Lever1::GameObjectDraw() 
{
	AEMtx33 mLever1Scale;
	float Lever1scale = GetScale();
	if (IsActivated)
	{
		AEMtx33Scale(&mLever1Scale, Lever1scale, Lever1scale); // flipped lever
	}
	else
	{
		AEMtx33Scale(&mLever1Scale, -Lever1scale, Lever1scale);
	}
	SetMScale(mLever1Scale);

	AEVec2 Lever1pos = GetPosition();
	AEMtx33 mLever1Trans;
	AEMtx33Trans(&mLever1Trans, Lever1pos.x, Lever1pos.y);
	SetMTrans(mLever1Trans);
}
