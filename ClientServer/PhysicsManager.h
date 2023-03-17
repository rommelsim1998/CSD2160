/******************************************************************************/
/*!
\file		PhysicsManager.h
\brief		Where the physics for each game object is updated
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "GameObject.h"
#include "Player.h"

class PhysicsManager
{
private:

public:
	/*===================================*
				Constructors
	*====================================*/
	PhysicsManager() = default;
	~PhysicsManager() = default;

	void PhysicsManagerUpdate();

	// Other collision and collision response.

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static PhysicsManager& GetInstance()
	{
		static PhysicsManager _instance;
		return _instance;
	}

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager(PhysicsManager&&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
	PhysicsManager& operator=(PhysicsManager&&) = delete;
};


#endif