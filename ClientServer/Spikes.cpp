/******************************************************************************
* \file			Spikes.cpp
* \brief		This file contains the definition of the Spike object class.
*				it acts as the hazard that affects both player and enemy.
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Spikes.h"
#include "EntityList.h"
#include "GameObject.h"
#include "Main.h"
#include "TileManager.h"
#include "CollisionManager.h"
#include "EntityManager.h"
#include <iostream>

using _em = EntityManager;
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();

/***************************************************************************/
/*!
	\brief
		The overloaded constructor for the spike object.
*/
/**************************************************************************/
Spikes::Spikes(int id) : GameObject(TYPE_SPIKE, id), test{ 8 }
{
	// Empty By Design
}

/***************************************************************************/
/*!
	\brief
		The deconstructor for the spike object
*/
/**************************************************************************/
Spikes::~Spikes()
{
	// Empty By Design
}

/***************************************************************************/
/*!
	\brief
		The Initialize function of the object that initializes the spikes.
*/
/**************************************************************************/
void Spikes::GameObjectInitialize()
{
	SetScale(60.0f);
	SetHasGravity(false);
}

/***************************************************************************/
/*!
	\brief
		The Update function of the object which updates the Spikes.
		For now it only updates the bounding box of the object
*/
/**************************************************************************/
void Spikes::GameObjectUpdate()
{
	// Setting of bounding box for Box Object
	AABB boundbox;
	boundbox.min.x = -0.25f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.25f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.5f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.15f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
}

/***************************************************************************/
/*!
	\brief
		The Draw function of the object which handles preparing the object
		for drawing by the Rendering Manager
*/
/**************************************************************************/
void Spikes::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale = GetScale();

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