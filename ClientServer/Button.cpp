/******************************************************************************/
/*!
\file		Button.cpp
\brief		This is supposed to act like a pressure plate where the gate(Gate3.cpp) will open
			when a box/player is standing on it and close when nothing is on the button.
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

using _em = EntityManager;
/**
 * @brief Default constructor for the Button game object
 *
 * @param id - game object id, type - is from the EntityList.h, IsActivated - set to false so no object is colliding with the button
 * @return void
 */

Button::Button(int id, int type) : GameObject(type, id), IsActivated{ false }, timer{0.0f}
{}
/**
 * @brief Destructor for the button game object
 *
 * @param void
 * @return void
 */
Button::~Button()
{}
/**
 * @brief Activates the gate by setting the state to going_up and the update function will handle calling the gate state machine function
 *
 * @param void
 * @return void
 */

void Button::ActivateGate()
{
	// call the function from Gate class to change the position of the gate as the player is colliding with the lever
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate3* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			IsActivated = true;
			theGate->SetState(STATE_GOING_UP);
		}
	}
}
/**
 * @brief DeActivates the gate by setting the state to going_down and the update function will handle calling the gate state machine function
 *
 * @param void
 * @return void
 */

void Button::DeActivateGate()
{
	if (IsActivated == true)
	{
		for (size_t i = 0; i < gate.size(); i++)
		{
			Gate3* theGate = gate[i];
			theGate->SetState(STATE_GOING_DOWN);
			theGate->SetInnerState(GATE_INNER_STATE_ON_ENTER);
			IsActivated = false;
		}
	}
}

/**
 * @brief Updates the IsActivated value depending on whether the gate is open or closed
 *
 * @param void
 * @return void
 */

void Button::UpdateGate()
{
	for (size_t i = 0; i < gate.size(); i++)
	{
		Gate3* theGate = gate[i];
		if (theGate->GetGateState() == STATE_NONE)
		{
			if (GetIsActivated() == false)
			{
				IsActivated = true;
			}
			else
			{
				IsActivated = false;
			}
		}
	}
}
/**
 * @brief Returns the value of IsActivated
 *
 * @param void
 * @return 1 - If gate is opened, 0 - if gate is closed
 */

bool Button::GetIsActivated()
{
	return IsActivated;
}
/**
 * @brief Initializes all the necessary data for the button game object
 *
 * @param void
 * @return void
 */

void Button::GameObjectInitialize()
{
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		GameObject* obj = it->second;
		/*if (GetType() != TYPE_BUTTON || GetType() != TYPE_BUTTON1)
			continue;*/
		if (GetType() == TYPE_BUTTON && obj->GetType() == TYPE_BUTTON_GATE)
		{
			gate.push_back(dynamic_cast<Gate3*>(obj));
		}
		else if(GetType() == TYPE_BUTTON1 && obj->GetType() == TYPE_BUTTON_GATE1)
		{
			gate.push_back(dynamic_cast<Gate3*>(obj));
		}
		else if (GetType() == TYPE_BUTTON2 && obj->GetType() == TYPE_BUTTON_GATE2)
		{
			gate.push_back(dynamic_cast<Gate3*>(obj));
		}
		else if (GetType() == TYPE_BUTTON3 && obj->GetType() == TYPE_BUTTON_GATE3)
		{
			gate.push_back(dynamic_cast<Gate3*>(obj));
		}
	}
	IsActivated = false;
	SetScale(50.0f); 
	AEVec2 initvel{ 0.0f, 0.0f };
	SetVelocity(initvel); 
}
/**
 * @brief Updates the button object with it's bounding box
 *
 * @param void
 * @return void
 */

void Button::GameObjectUpdate()
{
	AABB boundbox;
	boundbox.min.x = -0.1f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.1f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.1f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.1f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
}
/**
 * @brief Draws the button object at the appropriate position with the scaling included
 *		  When it is activated, button will move down.
 *
 * @param void
 * @return void
 */

void Button::GameObjectDraw()
{
	AEMtx33 mButtonScale;
	AEMtx33 mButtonTrans;
	AEVec2 Buttonpos = GetPosition();
	float Buttonscale = GetScale();
	if (IsActivated)
	{
		AEMtx33Trans(&mButtonTrans, Buttonpos.x, Buttonpos.y - 10.0f);
	}
	else
	{
		AEMtx33Trans(&mButtonTrans, Buttonpos.x, Buttonpos.y);
	}
	AEMtx33Scale(&mButtonScale, Buttonscale, Buttonscale);
	SetMScale(mButtonScale);
	SetMTrans(mButtonTrans);
}
