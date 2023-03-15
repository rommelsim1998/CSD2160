/******************************************************************************
* \file			Wall_Red.cpp
* \brief		This file handles the initializing of wall_red object, updates in
				which the wall_red does when player interacts with, and drawing the
				wall_red object.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

#define pi 3.14159265358979323846f
#define half_pi pi/2.0f
#define three_pi_half 3.0f*pi/2.0f

/***************************************************************************/
/*!
\brief
	Wall constructor that constructs the wall objects by inheriting
	from GameObject. Initializing the color to yellow;

\param id
	The id value tagged to the wall object.
*/
/**************************************************************************/
Wall_Yellow::Wall_Yellow(int id)
	: GameObject(TYPE_WALL_YELLOW, id), test{ 8 }
{
	SetColor(Color::COLOR_YELLOW);
}

/***************************************************************************/
/*!
\brief
	Wall destructor that destroys the wall object.
*/
/**************************************************************************/
Wall_Yellow::~Wall_Yellow()
{
}

/***************************************************************************/
/*!
\brief
	A function that initializes the wall object during each game state.
*/
/**************************************************************************/
void Wall_Yellow::GameObjectInitialize()
{
	SetHasGravity(false);
	SetScale(55.0f);
}

/***************************************************************************/
/*!
\brief
	A function that handles updates on the wall object during each game state.
*/
/**************************************************************************/
void Wall_Yellow::GameObjectUpdate()
{
	//ChangeState();
	AEVec2 distance, velocity, position;
	velocity = GetVelocity();
	position = GetPosition();
	AEVec2Scale(&distance, &velocity, (float)AEFrameRateControllerGetFrameTime());
	AEVec2Add(&position, &position, &distance);
	SetColor(Color::COLOR_YELLOW);
	SetPosition(position);

	// Setting of bounding box for Wall_Yellow Object
	AABB boundbox;
	boundbox.min.x = -0.5f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.5f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.5f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.5f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);

}

/***************************************************************************/
/*!
\brief
	A function that draws the wall object during each game state.
*/
/**************************************************************************/
void Wall_Yellow::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale = GetScale();

	// If current direction is left make scale left.
	AEMtx33Scale(&mScale, theScale, theScale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMTrans(mTrans);
	return;
}