/******************************************************************************
* \file          Cave5.cpp
* \brief         This file is the main file for Cave 5
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "Cave5.h"
#include "EntityList.h"
#include "GameObject.h"
#include <iostream>

#define pi 3.14159265358979323846f
#define half_pi pi/2.0f
#define three_pi_half 3.0f*pi/2.0f

Cave5::Cave5(int id)
	: GameObject(TYPE_CAVE5, id), test{ 11 }
{
}

Cave5::~Cave5()
{
}

void Cave5::GameObjectInitialize()
{
	SetScale(100.0f);
}

void Cave5::GameObjectUpdate()
{
	//ChangeState();
	AEVec2 distance, velocity, position;
	velocity = GetVelocity();
	position = GetPosition();
	AEVec2Scale(&distance, &velocity, (float)AEFrameRateControllerGetFrameTime());
	AEVec2Add(&position, &position, &distance);
	SetPosition(position);

	// Setting of bounding box for Cave Object
	AABB boundbox;
	boundbox.min.x = -0.1f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.1f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.2f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.2f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);

}

void Cave5::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale;
	theScale = GetScale();

	// If current direction is left make scale left.
	AEMtx33Scale(&mScale, theScale, theScale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMTrans(mTrans);
	return;
}