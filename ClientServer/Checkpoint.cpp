/******************************************************************************
* \file			Checkpoint.cpp
* \brief		This file handles the initializing of checkpoint object, updates in
				which the checkpoint does when player interacts with, and drawing 
				the checkpoint object.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

#define pi 3.14159265358979323846f
#define half_pi pi/2.0f
#define three_pi_half 3.0f*pi/2.0f

using _em = EntityManager;
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();

/***************************************************************************/
/*!
\brief
	Checkpoint constructor that constructs the checkpoint objects by inheriting
	from GameObject.

\param id
	The id value tagged to the checkpoint object.
*/
/**************************************************************************/
Checkpoint::Checkpoint(int id) : GameObject(TYPE_CHCKPT, id), test{ 68 }
{
}

/***************************************************************************/
/*!
\brief
	Checkpoint destructor that destroys the checkpoint object.
*/
/**************************************************************************/
Checkpoint::~Checkpoint()
{
}

/***************************************************************************/
/*!
\brief
	A function that initializes the checkpoint object during each game state.
*/
/**************************************************************************/
void Checkpoint::GameObjectInitialize()
{
	SetScale(50.0f);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
}

/***************************************************************************/
/*!
\brief
	A function that handles updates on the checkpoint object during each game state.
*/
/**************************************************************************/
void Checkpoint::GameObjectUpdate()
{
	SetHasGravity(false);
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
	A function that draws the checkpoint object during each game state.
*/
/**************************************************************************/
void Checkpoint::GameObjectDraw()
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