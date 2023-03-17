/******************************************************************************/
/*!
\file		Button1.cpp
\brief		This button/pressure plate activates the Gate4 game object from Gate4.cpp. When player/box
			is standing/colliding with the button1 object, the gate will remain open
			and only close when nothing is colliding with the button
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

using _em = EntityManager;
/**
 * @brief Default constructor for the Button1 game object
 *
 * @param id - game object id, type - is from the EntityList.h, IsActivated - set to false so no object is colliding with the button
 * @return void
 */

Button1::Button1(int id) : GameObject(TYPE_BUTTON1, id), IsActivated{ false }, timer{0.0f}
{}
/**
 * @brief Destructor for the Button1 game object
 *
 * @param void
 * @return void
 */

Button1::~Button1()
{}
/**
 * @brief Activates the gate by setting the state to going_up and the update function will handle calling the gate state machine function
 *
 * @param void
 * @return void
 */

void Button1::ActivateGate()
{
	// call the function from Gate class to change the position of the gate as the player is colliding with the lever
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate4* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = true;
			theGate->SetState(STATE_GOING_UP);
			theGate->GateStateMachine();
		}
	}
}
/**
 * @brief DeActivates the gate by setting the state to going_down and the update function will handle calling the gate state machine function
 *
 * @param void
 * @return void
 */

void Button1::DeActivateGate()
{
	// call the function from Gate class to change the position of the gate as the player is colliding with the lever
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate4* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = false;
			theGate->SetState(STATE_GOING_DOWN);
			theGate->GateStateMachine();
		}
	}
}
/**
 * @brief Updates the IsActivated value depending on whether the gate is open or closed
 *
 * @param void
 * @return void
 */

void Button1::UpdateGate()
{
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate4* theGate = gate[i];
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
 * @return 1 - If gate is opened, 0 - if gate is closed
 */

bool Button1::GetIsActivated()
{
	return IsActivated;
}
/**
 * @brief Initializes all the necessary data for the Button1 game object
 *
 * @param void
 * @return void
 */

void Button1::GameObjectInitialize()
{
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		GameObject* obj = it->second;
		if (obj->GetType() == TYPE_BUTTON_GATE1)
		{
			gate.push_back(dynamic_cast<Gate4*>(obj));
		}
	}
	IsActivated = false;
	SetScale(50.0f); 
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
}
/**
 * @brief Updates the Button1 object with it's bounding box
 *
 * @param void
 * @return void
 */

void Button1::GameObjectUpdate()
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
 * @brief Draws the button object at the appropriate position with the scaling included
 *		  When it is activated, button will flip.
 *
 * @param void
 * @return void
 */

void Button1::GameObjectDraw()
{
	AEMtx33 mButton1Scale;
	float Button1scale = GetScale();
	if (IsActivated)
	{
		AEMtx33Scale(&mButton1Scale, Button1scale, Button1scale); // flipped lever
	}
	else
	{
		AEMtx33Scale(&mButton1Scale, -Button1scale, Button1scale);
	}
	SetMScale(mButton1Scale);

	AEVec2 Button1pos = GetPosition();
	AEMtx33 mButton1Trans;
	AEMtx33Trans(&mButton1Trans, Button1pos.x, Button1pos.y);
	SetMTrans(mButton1Trans);
}
