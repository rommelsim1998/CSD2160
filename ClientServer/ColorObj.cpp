/******************************************************************************
* \file			ColorObj.cpp
* \brief		This file handles the initializing of colorobj object, updates in
				which the colorobj does when player interacts with, and drawing the
				colorobj object. (ColorObj are items that when collected, it 
				unlocks the color for the player to be able to use).
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
	ColorObj constructor that constructs the colorobj objects by inheriting
	from GameObject.

\param id
	The id value tagged to the colorobj object.
*/
/**************************************************************************/
ColorObj::ColorObj(int id) : GameObject(TYPE_COLOROBJ, id), test{ 68 }
{

}

/***************************************************************************/
/*!
\brief
	ColorObj destructor that destroys the colorobj object.
*/
/**************************************************************************/
ColorObj::~ColorObj()
{

}

/***************************************************************************/
/*!
\brief
	A function that initializes the colorobj object during each game state.
*/
/**************************************************************************/
void ColorObj::GameObjectInitialize()
{
	SetScale(50.0f);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
}

/***************************************************************************/
/*!
\brief
	A function that handles updates on the colorobj object during each game 
	state.
*/
/**************************************************************************/
void ColorObj::GameObjectUpdate()
{
	SetHasGravity(false);

	// Check if the color has been unlocked, which then prevents the object from appearing in game.
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (it->second->GetType() == TYPE_COLOROBJ)
		{
			std::ifstream colorfile;
			std::string line;
			colorfile.open("Resources/color.txt");
			if (colorfile.is_open())
			{
				while (getline(colorfile, line))
				{
					size_t found;
					if (((found = line.find("A")) != std::string::npos) && (current == GS_LEVEL1))
					{
						SetFlag(false);
					}
					if (((found = line.find("B")) != std::string::npos) && (current == GS_LEVEL2))
					{
						SetFlag(false);
					}
					if (((found = line.find("C")) != std::string::npos) && (current == GS_LEVEL4))
					{
						SetFlag(false);
					}
					if (((found = line.find("D")) != std::string::npos) && (current == GS_LEVEL6))
					{
						SetFlag(false);
					}
				}
				colorfile.close();
			}
		}
	}

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
	A function that draws the colorobj object during each game state.
*/
/**************************************************************************/
void ColorObj::GameObjectDraw()
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