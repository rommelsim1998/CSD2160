/******************************************************************************
* \file			CollisionManager.h
* \brief		This file handles all the collision checks for all the game
*				state
* \author		Sebastian Yew Kai Jie, 57.85% Code Contribution
*				Kyle Vincent Velasco Gatchalian, 30.81% Code Contribution
*				Tan Jian Jie, 4.68% Code Contribution
*				Ng Yuwen Felicia, 6.66% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef CS230_COLLISION_H_
#define CS230_COLLISION_H_

#include "AEEngine.h"
#include "GameObject.h"

class CollisionManager {
public:
	/*===================================*
				Constructors
	*====================================*/
	CollisionManager() = default;
	~CollisionManager() = default;


	/*===================================*
				Member Functions
	*====================================*/
	void CollisionManagerUpdate();

	bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
		const AABB& aabb2, const AEVec2& vel2);
	bool CollisionIntersection_CircCirc(const AEVec2& pos1, const float scale1,
		const AEVec2& pos2, const float scale2);
	int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY);

	bool ObjectBottomBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2);

	bool ObjectLeftBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2);

	bool ObjectRightBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2);

	bool ObjectTopBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2);
	//void SnapBack(float& Coordinate);

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static CollisionManager& GetInstance()
	{
		static CollisionManager _instance;
		return _instance;
	}
	//static EntityManager& GetInstance();

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	CollisionManager& operator=(CollisionManager&&) = delete;
};

#endif // CS230_COLLISION_H_
