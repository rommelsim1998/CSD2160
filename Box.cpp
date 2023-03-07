/******************************************************************************
* \file			Box.cpp
* \brief		This file handles the initializing of box object, updates in
				which the box does when player interacts with, and drawing the 
				box object.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

using _em = EntityManager;
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();

/***************************************************************************/
/*!
\brief
	Box constructor that constructs the box objects by inheriting
	from GameObject.

\param id
	The id value tagged to the box object.
*/
/**************************************************************************/
Box::Box(int id) : GameObject(TYPE_BOX, id), test{ 7 }
{

}

/***************************************************************************/
/*!
\brief
	Box destructor that destroys the box object.
*/
/**************************************************************************/
Box::~Box() 
{

}

/***************************************************************************/
/*!
\brief
	A function that initializes the box object during each game state.
*/
/**************************************************************************/
void Box::GameObjectInitialize()
{
	SetScale(50.0f);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
}

/***************************************************************************/
/*!
\brief
	A function that handles updates on the box object during each game state.
*/
/**************************************************************************/
void Box::GameObjectUpdate()
{
	AEVec2 boxvel;
	AEVec2Set(&boxvel, 0.0f, -97.0f * g_dt);
	SetVelocity(boxvel);

	SetHasGravity(true);

	// Setting of bounding box for Box Object
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
	A function that draws the box object during each game state.
*/
/**************************************************************************/
void Box::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale;
	theScale = GetScale();

	// If current direction is left make scale left.
	if (half_pi < GetDirection() &&
		three_pi_half > GetDirection())
	{
		AEMtx33Scale(&mScale, -theScale, theScale);
	}
	else
		AEMtx33Scale(&mScale, theScale, theScale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMTrans(mTrans);
}