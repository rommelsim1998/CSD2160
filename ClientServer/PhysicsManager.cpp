/******************************************************************************/
/*!
\file		PhysicsManager.cpp
\brief		Where the physics for each game object is updated
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

#define GRAVITY -10.0f;

using _em = EntityManager;

/*===================================*
		Physics Man Update
*====================================*/
/**
 * @brief Updates the final position of the objects before collision response occurs while taking into account gravity
 *
 * @return void
 */

void PhysicsManager::PhysicsManagerUpdate()
{
	float Gravity = -10.0f;
	AEVec2 oldpos;
	AEVec2 newpos;
	AEVec2 vel;


	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{

		/*===================================*
						Gravity
		*====================================*/
		if (it->second->GetHasGravity())
		{
			//AEVec2 vel;
			vel = it->second->GetVelocity();
			vel.y = (Gravity * g_dt) + vel.y;
			it->second->SetVelocity(vel);
		}

		/*===================================*
					Resultant Physics
		*====================================*/
		oldpos = it->second->GetPosition();
		vel = it->second->GetVelocity();
		AEVec2Add(&newpos, &oldpos, &vel);
		it->second->SetPosition(newpos);

		// engine proof updated AABB 

		/*AABB first, second;*/

		/*first.min.x = -0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.min.y = -0.5f * it->second->GetScale() + it->second->GetPosition().y;
		first.max.x = 0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.max.y = 0.5f * it->second->GetScale() + it->second->GetPosition().y;
		it->second->SetBoundingBox(first);*/
	}

}
