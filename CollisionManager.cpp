/******************************************************************************
* \file			CollisionManager.cpp
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

#include "Constants.h"
#include <iostream>
#include <cstdlib>
#include "ColorObj.h"
#include "Checkpoint.h"
#include <fstream>
#include <string>
#include <sstream>
#include "AudioManager.h"
#include <fmod.hpp>
#include <stdio.h>
const float			GRAVITY = 1.0f;


using _em = EntityManager;

TileManager& _tm = TileManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();

bool CollisionManager::ObjectBottomBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2)
{
	AABB standbox1, standbox2;
	standbox1.min.x = (f32)(-0.25 * scale1 + pos1.x);
	standbox1.max.x = standbox1.min.x;
	standbox1.min.y = (f32)(pos1.y - (0.5 * scale1));
	standbox1.max.y = standbox1.min.y;

	standbox2.min.x = (f32)(0.25 * scale1 + pos1.x);
	standbox2.max.x = standbox2.min.x;
	standbox2.min.y = (f32)(pos1.y - (0.5 * scale1));
	standbox2.max.y = standbox2.min.y;

	bool result = CollisionIntersection_RectRect(standbox1, vel1, aabb2, vel2);
	bool result2 = CollisionIntersection_RectRect(standbox2, vel1, aabb2, vel2);

	if (result || result2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionManager::ObjectLeftBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2)
{
	AABB leftside;

	leftside.min.x = (f32)(pos1.x - (0.5 * scale1));
	leftside.max.x = leftside.min.x;
	leftside.min.y = (f32)(-0.25 * scale1 + pos1.y);
	leftside.max.y = (f32)(0.25 * scale1 + pos1.y);

	bool result3 = CollisionIntersection_RectRect(leftside, vel1, aabb2, vel2);

	if (result3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionManager::ObjectRightBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2)
{
	AABB rightside;

	rightside.min.x = (f32)(pos1.x + (0.5 * scale1));
	rightside.max.x = rightside.min.x;
	rightside.min.y = (f32)(-0.25 * scale1 + pos1.y);
	rightside.max.y = (f32)(0.25 * scale1 + pos1.y);

	bool result4 = CollisionIntersection_RectRect(rightside, vel1, aabb2, vel2);

	if (result4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionManager::ObjectTopBinaryCollision(const AEVec2& pos1, float scale1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2)
{
	AABB standbox1, standbox2;
	standbox1.min.x = (f32)(-0.25 * scale1 + pos1.x);
	standbox1.max.x = standbox1.min.x;
	standbox1.min.y = (f32)(pos1.y + (0.5 * scale1));
	standbox1.max.y = standbox1.min.y;

	standbox2.min.x = (f32)(0.25 * scale1 + pos1.x);
	standbox2.max.x = standbox2.min.x;
	standbox2.min.y = (f32)(pos1.y + (0.5 * scale1));
	standbox2.max.y = standbox2.min.y;

	bool result = CollisionIntersection_RectRect(standbox1, vel1, aabb2, vel2);
	bool result2 = CollisionIntersection_RectRect(standbox2, vel1, aabb2, vel2);

	if (result || result2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*===================================*
		Collision Man Update
*====================================*/
void CollisionManager::CollisionManagerUpdate()
{
	// Collision Implementations (Response) here.
	/*===================================*
				AABB Collision
	*====================================*/
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		GameObject* obj1 = it->second;
		//Check if it is active

		/*===================================*
				Player Object Check
		*====================================*/
		if (it->second->GetType() == TYPE_PLAYER)
		{
			Player* player = dynamic_cast<Player*>(it->second);
			for (auto it2 = list.begin(); it2 != list.end(); ++it2)
			{
				// Skip checks if it's the same ID
				if (it->second->GetID() == it2->second->GetID())
					continue;
				GameObject* obj2 = it2->second;
				/*===================================*
						Player - Box Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_BOX)
				{
					Box* objectBox = dynamic_cast<Box*>(it2->second);
					AABB box1 = it->second->GetBoundingBox();
					AABB box2 = it2->second->GetBoundingBox();

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();
					/*===================================*
							Player Stand on Box
					*====================================*/
					if ((it->second->GetColor() != it2->second->GetColor()) && ObjectBottomBinaryCollision(it->second->GetPosition(), it->second->GetScale(), vel1, box2, vel2))
					{
						bool standing = true;
						player->SetisStanding(standing);

						AEVec2 vel = it->second->GetVelocity();
						vel.y = 0.0f;
						it->second->SetVelocity(vel);
						AEVec2 boxPos = it2->second->GetPosition();
						float boxScale = it->second->GetScale();

						// Then get that hot spot's y value. And shift object by that hotspot's
						// tile location and + tile_widthscale/2 and + object_scale/2
						AEVec2 playerPos = it->second->GetPosition();
						playerPos.y = (boxPos.y) + (boxScale * 0.38f)+(it->second->GetScale() * 0.5f);
						it->second->SetPosition(playerPos);
					}
					/*===================================*
					  Player Pushing and Pulling Box Left
					*====================================*/
					else if ((it->second->GetColor() != it2->second->GetColor()) && ObjectLeftBinaryCollision(it->second->GetPosition(), it->second->GetScale(), vel1, box2, vel2))
					{
						player->SetPull(true);

						if (player->GetCollisionFlag() & COLLISION_RIGHT)
						{
							player->SetPull(false);
						}
						if ((AEInputCheckCurr(AEVK_LEFT) || (AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_RIGHT))) && player->GetPull())
						{
							bool jump = false;
							player->SetisStanding(jump);

							AEVec2 vel = player->GetVelocity();

							vel.y = 0.0f;
							objectBox->SetVelocity(vel);
							AEVec2 boxPos = it2->second->GetPosition();
							float boxScale = it->second->GetScale();

							AEVec2 playerPos = it->second->GetPosition();
							AEVec2Add(&boxPos, &boxPos, &vel);
							objectBox->SetPosition(boxPos);

							float playerScale = player->GetScale();
							playerPos.x = boxPos.x + (boxScale * 0.22f) + (playerScale * 0.5f);
							player->SetPosition(playerPos);
						}
					}
					/*===================================*
					 Player Pushing and Pulling Box Right
					*====================================*/
					else if ((it->second->GetColor() != it2->second->GetColor()) && ObjectRightBinaryCollision(it->second->GetPosition(), it->second->GetScale(), vel1, box2, vel2))
					{
						player->SetPull(true);

						if (player->GetCollisionFlag() & COLLISION_LEFT)
						{
							player->SetPull(false);
						}
						if ((AEInputCheckCurr(AEVK_RIGHT) || (AEInputCheckCurr(AEVK_LSHIFT) && AEInputCheckCurr(AEVK_LEFT))) && player->GetPull())
						{
							bool jump = false;
							player->SetisStanding(jump);

							AEVec2 vel = player->GetVelocity();

							vel.y = 0.0f;
							objectBox->SetVelocity(vel);
							AEVec2 boxPos = it2->second->GetPosition();
							float boxScale = it->second->GetScale();

							AEVec2 playerPos = it->second->GetPosition();
							AEVec2Add(&boxPos, &boxPos, &vel);
							objectBox->SetPosition(boxPos);

							float playerScale = player->GetScale();
							playerPos.x = boxPos.x - (boxScale * 0.22f) - (playerScale * 0.5f);
							player->SetPosition(playerPos);
						}
					}

					/*===================================*
								Player Snap
					*====================================*/
					bool Colide = CollisionIntersection_RectRect(box1, vel1, box2, vel2);
					if ((it->second->GetColor() != it2->second->GetColor()) && (Colide == true))
					{
						AEVec2 playerPos = player->GetPosition();
						AEVec2 boxPos = objectBox->GetPosition();
						float playerScale = player->GetScale();
						float boxScale = objectBox->GetScale();
						// Check if box collided against wall to the right.
						// Don't allow push right
						// Only allow pull left
						// Player must be pushed back against box.

						if (objectBox->GetCollisionFlag() & COLLISION_RIGHT)
						{
							playerPos.x = boxPos.x - (boxScale * 0.22f) - (playerScale * 0.5f);
							player->SetPosition(playerPos);
						}
						if (objectBox->GetCollisionFlag() & COLLISION_LEFT)
						{
							playerPos.x = boxPos.x + (boxScale * 0.22f) + (playerScale * 0.5f);
							player->SetPosition(playerPos);
						}
					}
				}
				/*===================================*
					Blue Wall - Player Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_BLUE)
				{
					Wall_Blue* bluewall = dynamic_cast<Wall_Blue*>(it2->second);
					AABB aabbplayer = player->GetBoundingBox();
					AABB aabbwall = bluewall->GetBoundingBox();
					AEVec2 vel1 = player->GetVelocity();
					AEVec2 vel2 = bluewall->GetVelocity();
					AEVec2 playerPos = player->GetPosition();
					AEVec2 wallPos = bluewall->GetPosition();
					float wallScale = bluewall->GetScale();
					float playerScale = player->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resulttop = ObjectTopBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					if (resultright && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultleft && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultbtm && (it->second->GetColor() != it2->second->GetColor()))
					{
						bool standing = true;
						player->SetisStanding(standing);
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resulttop && (it->second->GetColor() != it2->second->GetColor()))
					{
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}

				}
				/*===================================*
					Green Wall - Player Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_GREEN)
				{
					Wall_Green* greenwall = dynamic_cast<Wall_Green*>(it2->second);
					AABB aabbplayer = player->GetBoundingBox();
					AABB aabbwall = greenwall->GetBoundingBox();
					AEVec2 vel1 = player->GetVelocity();
					AEVec2 vel2 = greenwall->GetVelocity();
					AEVec2 playerPos = player->GetPosition();
					AEVec2 wallPos = greenwall->GetPosition();
					float wallScale = greenwall->GetScale();
					float playerScale = player->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resulttop = ObjectTopBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					if (resultright && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultleft && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}	
					else if (resultbtm && (it->second->GetColor() != it2->second->GetColor()))
					{
						bool standing = true;
						player->SetisStanding(standing);
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resulttop && (it->second->GetColor() != it2->second->GetColor()))
					{
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
				}
				/*===================================*
					Red Wall - Player Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_RED)
				{
					Wall_Red* redwall = dynamic_cast<Wall_Red*>(it2->second);
					AABB aabbplayer = player->GetBoundingBox();
					AABB aabbwall = redwall->GetBoundingBox();
					AEVec2 vel1 = player->GetVelocity();
					AEVec2 vel2 = redwall->GetVelocity();
					AEVec2 playerPos = player->GetPosition();
					AEVec2 wallPos = redwall->GetPosition();
					float wallScale = redwall->GetScale();
					float playerScale = player->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resulttop = ObjectTopBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					if (resultright && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultleft && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultbtm && (it->second->GetColor() != it2->second->GetColor()))
					{
						bool standing = true;
						player->SetisStanding(standing);
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resulttop && (it->second->GetColor() != it2->second->GetColor()))
					{
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
				}
				/*===================================*
					Yellow Wall - Player Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_YELLOW)
				{
					Wall_Yellow* yellowwall = dynamic_cast<Wall_Yellow*>(it2->second);
					AABB aabbplayer = player->GetBoundingBox();
					AABB aabbwall = yellowwall->GetBoundingBox();
					AEVec2 vel1 = player->GetVelocity();
					AEVec2 vel2 = yellowwall->GetVelocity();
					AEVec2 playerPos = player->GetPosition();
					AEVec2 wallPos = yellowwall->GetPosition();
					float wallScale = yellowwall->GetScale();
					float playerScale = player->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					bool resulttop = ObjectTopBinaryCollision(player->GetPosition(), player->GetScale(), vel1, aabbwall, vel2);
					if (resultright && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultleft && (it->second->GetColor() != it2->second->GetColor()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
					else if (resultbtm && (it->second->GetColor() != it2->second->GetColor()))
					{
						bool standing = true;
						player->SetisStanding(standing);
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}	
					else if (resulttop && (it->second->GetColor() != it2->second->GetColor()))
					{
						vel1.y = 0.0f;
						player->SetVelocity(vel1);
						playerPos.y = (wallPos.y) - (wallScale * 0.5f) - (playerScale * 0.5f);
						player->SetPosition(playerPos);
					}
				}
				/*==============================================================*
						Player - Lever Collision  | for TriggerGate(Gate)
				*===============================================================*/

				else if (it2->second->GetType() == TYPE_LEVER)
				{
					Lever* lever = dynamic_cast<Lever*>(it2->second);
					AABB playerlever = it->second->GetBoundingBox(); // player
					AABB lever1 = it2->second->GetBoundingBox();// lever

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();

					if (CollisionIntersection_RectRect(playerlever, vel1, lever1, vel2))
					{
						lever->ActivateGate();

					}
				}
				/*==============================================================*
						Player - Lever Collision  | for TimerGate(Gate2)
				*===============================================================*/

				else if (it2->second->GetType() == TYPE_LEVER1)
				{
					Lever1* lever = dynamic_cast<Lever1*>(it2->second);
					AABB playerlever = it->second->GetBoundingBox(); // player
					AABB timerlever = it2->second->GetBoundingBox();// lever

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();

					if (CollisionIntersection_RectRect(playerlever, vel1, timerlever, vel2))
					{
						lever->ActivateGate();
					}
				}
				/*==============================================================*
						Player - Button Collision
				*===============================================================*/

				else if (it2->second->GetType() == TYPE_BUTTON || it2->second->GetType() == TYPE_BUTTON1 ||
						it2->second->GetType() == TYPE_BUTTON2 || it2->second->GetType() == TYPE_BUTTON3)
				{
					Button* btn = dynamic_cast<Button*>(it2->second);
					AABB playerbtn = it->second->GetBoundingBox(); // player
					AABB btncol = it2->second->GetBoundingBox();// lever

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();

					if (CollisionIntersection_RectRect(playerbtn, vel1, btncol, vel2))
					{
						btn->AddObject(it->second);
					}
					else
					{
						btn->RemoveObj(it->second);
					}

					if (btn->GetObjects().size() && btn->GetIsActivated() == false)
						btn->ActivateGate();
					else if((btn->GetObjects().size() == 0) && (btn->GetIsActivated() == true))
					{
							btn->DeActivateGate();
					}
				}
				/*===============================================================*
						Player - Gate3/4 Collision | aka pressure gate
				*================================================================*/
				if (it2->second->GetType() == TYPE_BUTTON_GATE || it2->second->GetType() == TYPE_BUTTON_GATE1 ||
					it2->second->GetType() == TYPE_BUTTON_GATE2 || it2->second->GetType() == TYPE_BUTTON_GATE3)
				{
					Gate3* gate = dynamic_cast<Gate3*>(obj2);
					if (gate->GetIsCollidable())
					{
						AEVec2 playerPos, playerVel, gatePos, gateVel;
						AABB gateBoundingBox;
						float playerScale, gateScale;
						playerScale = player->GetScale();
						gateScale = gate->GetScale();
						playerPos = player->GetPosition();
						playerVel = player->GetVelocity();
						gatePos = gate->GetPosition();
						gateVel = gate->GetVelocity();
						gateBoundingBox = gate->GetBoundingBox();

						if (ObjectRightBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x - (gateScale * 0.5f) - (playerScale * 0.5));
						}
						else if (ObjectLeftBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x + (gateScale * 0.5f) + (playerScale * 0.5));
						}
						player->SetPosition(playerPos);
					}
				}
				/*===============================================================*
						Player - Gate2 Collision | aka timer gate
				*================================================================*/

				if (it2->second->GetType() == TYPE_LEVER_GATE1)
				{
					Gate2* gate = dynamic_cast<Gate2*>(obj2);
					if (gate->GetIsCollidable())
					{
						AEVec2 playerPos, playerVel, gatePos, gateVel;
						AABB gateBoundingBox;
						float playerScale, gateScale;
						playerScale = player->GetScale();
						gateScale = gate->GetScale();
						playerPos = player->GetPosition();
						playerVel = player->GetVelocity();
						gatePos = gate->GetPosition();
						gateVel = gate->GetVelocity();
						gateBoundingBox = gate->GetBoundingBox();

						if (ObjectRightBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x - (gateScale * 0.5f) - (playerScale * 0.5));
						}
						else if (ObjectLeftBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x + (gateScale * 0.5f) + (playerScale * 0.5));
						}
						player->SetPosition(playerPos);
					}
				}

				else if (it2->second->GetType() == TYPE_SPIKE)
				{
					AABB box1 = it->second->GetBoundingBox();
					AABB box2 = it2->second->GetBoundingBox();

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();
					bool Colide = CollisionIntersection_RectRect(box1, vel1, box2, vel2);
					if (Colide == true)
					{
						next = GS_RESTART;
					}
				}
				/*===================================*
						Player - Door Collision - Main Menu
				*====================================*/
				// set bounding box for cave
				AABB box1 = it->second->GetBoundingBox();
				AABB box2 = it2->second->GetBoundingBox();

				AEVec2 vel1 = it->second->GetVelocity();
				AEVec2 vel2 = it2->second->GetVelocity();

				bool Colide = CollisionIntersection_RectRect(box1, vel1, box2, vel2);
				// if current game state is main menu
				if (current == GS_MAINMENU)
				{
					// for entering cave1
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_LS;
					}
					if (it2->second->GetType() == TYPE_CAVE2 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_CREDITS;
					}
					if (it2->second->GetType() == TYPE_CAVE3 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_QUIT;
						//current = GS_QUIT;
					}
					if (it2->second->GetType() == TYPE_CAVE4 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						isOptionsEnabled = true;
						//current = GS_QUIT;
					}

				}
				if (current == GS_LS)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_MAINMENU;
					}
					if (it2->second->GetType() == TYPE_CAVE2 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_LEVEL1;
					}
					if (it2->second->GetType() == TYPE_CAVE3 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_LEVEL3;
					}
					if (it2->second->GetType() == TYPE_CAVE4 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_LEVEL5;
					}
					if (it2->second->GetType() == TYPE_CAVE5 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_LEVEL7;
					}
					if (it2->second->GetType() == TYPE_CAVE6 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_EXTRA;
					}
				}
				// if gamestate is testlevel set the door to do this 
				if (current == GS_TESTLEVEL)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_QUIT;
					}
				}

				if (current == GS_LEVEL1)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if(levelfile.is_open())
						{
							while(!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 1)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LEVEL2;
					}
				}

				if (current == GS_LEVEL2)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 2)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LS;
					}
				}

				if (current == GS_LEVEL3)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 3)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LEVEL4;
					}
				}
				if (current == GS_LEVEL4)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 4)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LS;
					}
				}
				if (current == GS_LEVEL5)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 5)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LEVEL6;
					}
				}
				if (current == GS_LEVEL6)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 6)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LS;
					}
				}
				if (current == GS_LEVEL7)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 7)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LEVEL8;
					}
				}
				if (current == GS_LEVEL8)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						std::fstream levelfile;
						std::string line;
						int count = 0;
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if (levelfile.get() == '1')
								{
									++count;
								}
							}
							levelfile.close();
						}
						levelfile.open("Resources/levels.txt");
						if (levelfile.is_open())
						{
							while (!levelfile.eof())
							{
								if ((levelfile.get() == ' ') && count < 8)
								{
									levelfile.seekp((levelfile.tellp() - static_cast<std::streampos>(1)));
									levelfile.put('1');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(',');
									levelfile.seekp(levelfile.tellp());
									levelfile.put(' ');
									levelfile.seekp(levelfile.tellp());
								}
							}
							levelfile.close();
						}
						next = GS_LS;
					}
				}
				if (current == GS_EXTRA)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_END;
					}
				}
				if (current == GS_END)
				{
					if (it2->second->GetType() == TYPE_CAVE1 && AEInputCheckTriggered(AEVK_UP) && (Colide == true))
					{
						next = GS_MAINMENU; // To credits then main menu
					}
				}

				/*===================================*
						Player - Enemy Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_ENEMY)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(obj2);
					/*===================================*
							Enemy Detect Player
					*====================================*/
					if (enemy->GetState() == ENEMY_STATE::STATE_ENEMY_DEATH)
						continue;
					if ((enemy->GetState() != ENEMY_STATE::STATE_CHASE_PLAYER) ||
						((enemy->GetState() == ENEMY_STATE::STATE_CHASE_PLAYER) &&
							(enemy->GetInnerState() == ENEMY_INNER_STATE::INNER_STATE_ON_EXIT)))
					{
						if (CollisionIntersection_RectRect(obj1->GetBoundingBox(), obj1->GetVelocity(),
							enemy->GetDetectionBox(), enemy->GetVelocity()))
						{
							if (enemy->GetState() == ENEMY_STATE::STATE_MOVE_LEFT)
								enemy->SetPreviousState(ENEMY_STATE::STATE_MOVE_LEFT);
							else if (enemy->GetState() == ENEMY_STATE::STATE_MOVE_RIGHT)
								enemy->SetPreviousState(ENEMY_STATE::STATE_MOVE_RIGHT);
							// If player is detected, change state to chase player.
							enemy->SetState(ENEMY_STATE::STATE_CHASE_PLAYER);
							enemy->SetInnerState(ENEMY_INNER_STATE::INNER_STATE_ON_ENTER);
						}
					}
					else if (enemy->GetState() == ENEMY_STATE::STATE_CHASE_PLAYER)
					{
						// If the player is not detected by enemy.
						if (!CollisionIntersection_RectRect(obj1->GetBoundingBox(), obj1->GetVelocity(),
							enemy->GetDetectionBox(), enemy->GetVelocity()))
						{

							//load audio manager and play sound
							//_am.AudioManagerLoad();
							_am.playeffect("Resources/enemyfoundu.wav",_am.sound, _am.soundeffect, _am.bgm_paused, &_am.test);
							// Exit out of the Chase Player State.
							enemy->SetInnerState(ENEMY_INNER_STATE::INNER_STATE_ON_EXIT);
						}
					}

					// Check last for enemy hitting player.
					if (CollisionIntersection_CircCirc(obj1->GetPosition(), obj1->GetScale(),
						enemy->GetPosition(), enemy->GetScale() * 0.35f) )
					{
						// Player gets hit.
						// Change gamestate to restart.
						next = GS_RESTART;
					}
				}

				/*===================================*
						Player - Spike Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_SPIKE)
				{
					Spikes* spikes = dynamic_cast<Spikes*>(obj2);
					if (CollisionIntersection_RectRect(obj1->GetBoundingBox(), obj1->GetVelocity(),
						spikes->GetBoundingBox(), spikes->GetVelocity()))
					{
						next = GS_RESTART;
					}
				}

				/*===================================*
						Player - Gate Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_LEVER_GATE)
				{
					Gate* gate = dynamic_cast<Gate*>(obj2);
					if (gate->GetIsCollidable())
					{
						AEVec2 playerPos;
						AEVec2 playerVel;
						AEVec2 gatePos;
						AEVec2 gateVel;
						AABB gateBoundingBox;
						float playerScale;
						float gateScale;
						playerScale = player->GetScale();
						gateScale = gate->GetScale();
						playerPos = player->GetPosition();
						playerVel = player->GetVelocity();
						gatePos = gate->GetPosition();
						gateVel = gate->GetVelocity();
						gateBoundingBox = gate->GetBoundingBox();

						if (ObjectRightBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x - (gateScale * 0.5f) - (playerScale * 0.5));
						}
						else if (ObjectLeftBinaryCollision(playerPos, playerScale, playerVel, gateBoundingBox, gateVel))
						{
							playerPos.x = (f32)(gatePos.x + (gateScale * 0.5f) + (playerScale * 0.5));
						}
						player->SetPosition(playerPos);
					}
				}

				/*===================================*
						Player - ColorObj Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_COLOROBJ)
				{
					ColorObj* colorobj = dynamic_cast<ColorObj*>(obj2);
					
					if (CollisionIntersection_RectRect(obj1->GetBoundingBox(), obj1->GetVelocity(),
						colorobj->GetBoundingBox(), colorobj->GetVelocity()))
					{
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_COLOROBJ_RED)
						{
							colorobj->SetFlag(false);

							std::fstream colorfile;

							colorfile.open("Resources/color.txt");
							if (colorfile.is_open())
							{
								while (!colorfile.eof())
								{
									if (colorfile.get() == 'a')
									{
										colorfile.seekp((colorfile.tellp() - static_cast<std::streampos>(1)));
										colorfile.put('A');
										colorfile.seekp(colorfile.tellp());
									}
								}
								colorfile.close();
							}
						}
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_COLOROBJ_BLUE)
						{
							colorobj->SetFlag(false);

							std::fstream colorfile;

							colorfile.open("Resources/color.txt");
							if (colorfile.is_open())
							{
								while (!colorfile.eof())
								{
									if (colorfile.get() == 'b')
									{
										colorfile.seekp((colorfile.tellp() - static_cast<std::streampos>(1)));
										colorfile.put('B');
										colorfile.seekp(colorfile.tellp());
									}
								}
								colorfile.close();
							}
						}
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_COLOROBJ_GREEN)
						{
							colorobj->SetFlag(false);

							std::fstream colorfile;

							colorfile.open("Resources/color.txt");
							if (colorfile.is_open())
							{
								while (!colorfile.eof())
								{
									if (colorfile.get() == 'c')
									{
										colorfile.seekp((colorfile.tellp() - static_cast<std::streampos>(1)));
										colorfile.put('C');
										colorfile.seekp(colorfile.tellp());
									}
								}
								colorfile.close();
							}
						}
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_COLOROBJ_YELLOW)
						{
							colorobj->SetFlag(false);

							std::fstream colorfile;

							colorfile.open("Resources/color.txt");
							if (colorfile.is_open())
							{
								while (!colorfile.eof())
								{
									if (colorfile.get() == 'd')
									{
										colorfile.seekp((colorfile.tellp() - static_cast<std::streampos>(1)));
										colorfile.put('D');
										colorfile.seekp(colorfile.tellp());
									}
								}
								colorfile.close();
							}
						}
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_CHECKPOINT)
						{
							colorobj->SetFlag(false);
							AEVec2 resPos = colorobj->GetPosition();
							player->SetRestartPos(resPos);
						}
					}
				}
				/*===================================*
					Player - ImageBox Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_IMAGEBOX1 || it2->second->GetType() == TYPE_IMAGEBOX2 || it2->second->GetType() == TYPE_IMAGEBOX3 ||
					it2->second->GetType() == TYPE_IMAGEBOX4 || it2->second->GetType() == TYPE_IMAGEBOX5 || it2->second->GetType() == TYPE_IMAGEBOX6)
				{
					ImageBox* imgBox1 = dynamic_cast<ImageBox*>(it2->second);
					if (imgBox1->GetShowOnNearEffect())
					{
						// When Detected
						if (CollisionIntersection_RectRect(player->GetBoundingBox(), player->GetVelocity(),
							imgBox1->GetDetectionBox(), imgBox1->GetVelocity()))
						{
							imgBox1->SetFlag(true);
						}
						// When Not Detected.
						else if (!CollisionIntersection_RectRect(player->GetBoundingBox(), player->GetVelocity(),
							imgBox1->GetDetectionBox(), imgBox1->GetVelocity()))
						{
							imgBox1->SetFlag(false);
						}
					}
				}

				/*===================================*
						Player - ColorObj Collision
				*====================================*/
				if (it2->second->GetType() == TYPE_CHCKPT)
				{
					Checkpoint* checkpoint = dynamic_cast<Checkpoint*>(obj2);

					if (CollisionIntersection_RectRect(obj1->GetBoundingBox(), obj1->GetVelocity(),
						checkpoint->GetBoundingBox(), checkpoint->GetVelocity()))
					{
						if (_tm.GetTileTypeAt(obj1->GetPosition().x, obj1->GetPosition().y) == TileType::TILE_CHECKPOINT)
						{
							checkpoint->SetFlag(false);
							AEVec2 resPos = checkpoint->GetPosition();
							player->SetRestartPos(resPos);
						}
					}
				}
			}
		}
		
		/*===================================*
				Enemy Object Check
		*====================================*/
		if (obj1->GetType() == TYPE_ENEMY)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(obj1);
			for (auto it2 = list.begin(); it2 != list.end(); it2++)
			{
				GameObject* obj2 = it2->second;
				/*===================================*
						Enemy - Box Collision
				*====================================*/
				if ((obj2->GetType() == TYPE_BOX) && (obj2->GetIsCollidable() == true))
				{
					Box* box = dynamic_cast<Box*>(obj2);
					AEVec2 enemyPos;
					AEVec2 enemyVel;
					AEVec2 boxPos;
					AEVec2 boxVel;
					AABB boxBoundingBox;
					float enemyScale;
					float boxScale;
					enemyScale = enemy->GetScale();
					boxScale = box->GetScale();
					enemyPos = enemy->GetPosition();
					enemyVel = enemy->GetVelocity();
					boxPos = box->GetPosition();
					boxVel = box->GetVelocity();
					boxBoundingBox = box->GetBoundingBox();
					boxVel.x = 0.0f;
					boxVel.y = 0.0f;
					//// Right check
					if (ObjectRightBinaryCollision(enemyPos, enemyScale, enemyVel, boxBoundingBox, boxVel))
					{
						enemyPos.x = boxPos.x - (boxScale * 0.5f) - (enemyScale * 0.5f);
						enemyVel.x = 0.0f;
						enemy->SetDetectionBox(enemy->GetBoundingBox());
					}
					if (ObjectLeftBinaryCollision(enemyPos, enemyScale, enemyVel, boxBoundingBox, boxVel))
					{
						enemyPos.x = boxPos.x + (boxScale * 0.5f) + (enemyScale * 0.5f);
						enemyVel.x = 0.0f;
						enemy->SetDetectionBox(enemy->GetBoundingBox());
					}

					bool Colide = CollisionIntersection_RectRect(enemy->GetBoundingBox(), enemyVel, boxBoundingBox, boxVel);
					if ((it->second->GetColor() != it2->second->GetColor()) && (Colide == true))
					{
						if (enemy->GetCollisionFlag() & COLLISION_RIGHT)
						{
							enemyPos.x = boxPos.x - (boxScale * 0.22f) - (enemyScale * 0.5f);
							//enemy->SetPosition(enemyPos);
						}
						else if (enemy->GetCollisionFlag() & COLLISION_LEFT)
						{
							enemyPos.x = boxPos.x + (boxScale * 0.22f) + (enemyScale * 0.5f);
							//enemy->SetPosition(enemyPos);
						}
					}
					enemy->SetPosition(enemyPos);
					enemy->SetVelocity(enemyVel);
				}
				/*===================================*
						Enemy - Gate Collision
				*====================================*/
				if ((obj2->GetType() == TYPE_LEVER_GATE))
				{
					Gate* gate = dynamic_cast<Gate*>(obj2);
					AEVec2 enemyPos;
					AEVec2 enemyVel;
					AEVec2 gatePos;
					AEVec2 gateVel;
					AABB gateBoundingBox;
					float enemyScale;
					float gateScale;
					enemyScale = enemy->GetScale();
					gateScale = gate->GetScale();
					enemyPos = enemy->GetPosition();
					enemyVel = enemy->GetVelocity();
					gatePos = gate->GetPosition();
					gateVel = gate->GetVelocity();
					gateBoundingBox = gate->GetBoundingBox();
					gateVel.x = 0.0f;
					gateVel.y = 0.0f;
					if (ObjectRightBinaryCollision(enemyPos, enemyScale, enemyVel, gateBoundingBox, gateVel))
					{
						enemyPos.x = gatePos.x - (gateScale * 0.5f) - (enemyScale * 0.5f);
						enemyVel.x = 0.0f;
						enemy->SetDetectionBox(enemy->GetBoundingBox());
					}
					else if(ObjectLeftBinaryCollision(enemyPos, enemyScale, enemyVel, gateBoundingBox, gateVel))
					{
						enemyPos.x = gatePos.x + (gateScale * 0.5f) + (enemyScale * 0.5f);
						enemyVel.x = 0.0f;
						enemy->SetDetectionBox(enemy->GetBoundingBox());
					}
					enemy->SetPosition(enemyPos);
					enemy->SetVelocity(enemyVel);
				}
				/*===================================*
						Enemy - Spike Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_SPIKE)
				{
					// Enemy should die if hit spike.
					Spikes* spike = dynamic_cast<Spikes*>(it2->second);
					if ((enemy->GetState() != ENEMY_STATE::STATE_ENEMY_DEATH) && CollisionIntersection_RectRect(enemy->GetBoundingBox(), enemy->GetVelocity(),
						spike->GetBoundingBox(), spike->GetVelocity()))
					{
						enemy->SetState(ENEMY_STATE::STATE_ENEMY_DEATH);
						enemy->SetInnerState(ENEMY_INNER_STATE::INNER_STATE_ON_ENTER);
					}
				}
				/*===================================*
					Blue Wall - Enemy Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_BLUE)
				{
					Wall_Blue* bluewall = dynamic_cast<Wall_Blue*>(it2->second);
					AABB aabbEnemy = enemy->GetBoundingBox();
					AABB aabbwall = bluewall->GetBoundingBox();
					AEVec2 vel1 = enemy->GetVelocity();
					AEVec2 vel2 = bluewall->GetVelocity();
					AEVec2 enemyPos = enemy->GetPosition();
					AEVec2 wallPos = bluewall->GetPosition();
					float wallScale = bluewall->GetScale();
					float enemyScale = enemy->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					if (resultright && (bluewall->GetIsCollidable()))
					{
						enemyPos.x = wallPos.x - (wallScale * 0.5f) - (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
					else if (resultleft && (bluewall->GetIsCollidable()))
					{
						enemyPos.x = wallPos.x + (wallScale * 0.5f) + (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
					else if (resultbtm && (bluewall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						enemy->SetVelocity(vel1);
						enemyPos.y = (wallPos.y) + (wallScale * 0.45f) + (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
				}
				/*===================================*
					Green Wall - Enemy Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_GREEN)
				{
					Wall_Green* greenwall = dynamic_cast<Wall_Green*>(it2->second);
					AABB aabbEnemy = enemy->GetBoundingBox();
					AABB aabbwall = greenwall->GetBoundingBox();
					AEVec2 vel1 = enemy->GetVelocity();
					AEVec2 vel2 = greenwall->GetVelocity();
					AEVec2 enemyPos = enemy->GetPosition();
					AEVec2 wallPos = greenwall->GetPosition();
					float wallScale = greenwall->GetScale();
					float enemyScale = enemy->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (greenwall->GetIsCollidable()))
					{
						enemyPos.x = wallPos.x - (wallScale * 0.5f) - (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
					else if (resultleft && (greenwall->GetIsCollidable()))
					{
						enemyPos.x = wallPos.x + (wallScale * 0.5f) + (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
					else if (resultbtm && (greenwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						enemy->SetVelocity(vel1);
						enemyPos.y = (wallPos.y) + (wallScale * 0.45f) + (enemyScale * 0.5f);
						enemy->SetPosition(enemyPos);
					}
				}
				/*===================================*
					Red Wall - Enemy Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_RED)
				{
					Wall_Red* redwall = dynamic_cast<Wall_Red*>(it2->second);
					AABB aabbplayer = enemy->GetBoundingBox();
					AABB aabbwall = redwall->GetBoundingBox();
					AEVec2 vel1 = enemy->GetVelocity();
					AEVec2 vel2 = redwall->GetVelocity();
					AEVec2 playerPos = enemy->GetPosition();
					AEVec2 wallPos = redwall->GetPosition();
					float wallScale = redwall->GetScale();
					float playerScale = enemy->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (redwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
					else if (resultleft && (redwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
					else if (resultbtm && (redwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						enemy->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.45f) + (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
				}
				/*===================================*
					Yellow Wall - Enemy Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_YELLOW)
				{
					Wall_Yellow* yellowwall = dynamic_cast<Wall_Yellow*>(it2->second);
					AABB aabbplayer = enemy->GetBoundingBox();
					AABB aabbwall = yellowwall->GetBoundingBox();
					AEVec2 vel1 = enemy->GetVelocity();
					AEVec2 vel2 = yellowwall->GetVelocity();
					AEVec2 playerPos = enemy->GetPosition();
					AEVec2 wallPos = yellowwall->GetPosition();
					float wallScale = yellowwall->GetScale();
					float playerScale = enemy->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(enemy->GetPosition(), enemy->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (yellowwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
					else if (resultleft && (yellowwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
					else if (resultbtm && (yellowwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						enemy->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.45f) + (playerScale * 0.5f);
						enemy->SetPosition(playerPos);
					}
				}

			}
		}

		if (obj1->GetType() == TYPE_BOX)
		{
			Box* box = dynamic_cast<Box*>(obj1);
			for (auto it2 = list.begin(); it2 != list.end(); it2++)
			{
				GameObject* obj2 = it2->second;

				/*===================================*
					Blue Wall - Box Collision
				*====================================*/
				if (obj2->GetType() == TYPE_WALL_BLUE)
				{
					Wall_Blue* bluewall = dynamic_cast<Wall_Blue*>(it2->second);
					AABB aabbplayer = box->GetBoundingBox();
					AABB aabbwall = bluewall->GetBoundingBox();
					AEVec2 vel1 = box->GetVelocity();
					AEVec2 vel2 = bluewall->GetVelocity();
					AEVec2 playerPos = box->GetPosition();
					AEVec2 wallPos = bluewall->GetPosition();
					float wallScale = bluewall->GetScale();
					float playerScale = box->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (bluewall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultleft && (bluewall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultbtm && (bluewall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						box->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
				}
				/*===================================*
					Green Wall - Box Collision
				*====================================*/
				else if (obj2->GetType() == TYPE_WALL_GREEN)
				{
					Wall_Green* greenwall = dynamic_cast<Wall_Green*>(it2->second);
					AABB aabbplayer = box->GetBoundingBox();
					AABB aabbwall = greenwall->GetBoundingBox();
					AEVec2 vel1 = box->GetVelocity();
					AEVec2 vel2 = greenwall->GetVelocity();
					AEVec2 playerPos = box->GetPosition();
					AEVec2 wallPos = greenwall->GetPosition();
					float wallScale = greenwall->GetScale();
					float playerScale = box->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (greenwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultleft && (greenwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultbtm && (greenwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						box->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
				}
				/*===================================*
					Red Wall - Box Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_RED)
				{
					Wall_Red* redwall = dynamic_cast<Wall_Red*>(it2->second);
					AABB aabbplayer = box->GetBoundingBox();
					AABB aabbwall = redwall->GetBoundingBox();
					AEVec2 vel1 = box->GetVelocity();
					AEVec2 vel2 = redwall->GetVelocity();
					AEVec2 playerPos = box->GetPosition();
					AEVec2 wallPos = redwall->GetPosition();
					float wallScale = redwall->GetScale();
					float playerScale = box->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (redwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultleft && (redwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultbtm && (redwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						box->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
				}
				/*===================================*
					Yellow Wall - Box Collision
				*====================================*/
				else if (it2->second->GetType() == TYPE_WALL_YELLOW)
				{
					Wall_Yellow* yellowwall = dynamic_cast<Wall_Yellow*>(it2->second);
					AABB aabbplayer = box->GetBoundingBox();
					AABB aabbwall = yellowwall->GetBoundingBox();
					AEVec2 vel1 = box->GetVelocity();
					AEVec2 vel2 = yellowwall->GetVelocity();
					AEVec2 playerPos = box->GetPosition();
					AEVec2 wallPos = yellowwall->GetPosition();
					float wallScale = yellowwall->GetScale();
					float playerScale = box->GetScale();

					bool resultbtm = ObjectBottomBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultright = ObjectRightBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					bool resultleft = ObjectLeftBinaryCollision(box->GetPosition(), box->GetScale(), vel1, aabbwall, vel2);
					//bool result = CollisionIntersection_RectRect(aabbplayer, vel1, aabbwall, vel2);
					if (resultright && (yellowwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x - (wallScale * 0.5f) - (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultleft && (yellowwall->GetIsCollidable()))
					{
						playerPos.x = wallPos.x + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
					else if (resultbtm && (yellowwall->GetIsCollidable()))
					{
						vel1.y = 0.0f;
						box->SetVelocity(vel1);
						playerPos.y = (wallPos.y) + (wallScale * 0.5f) + (playerScale * 0.5f);
						box->SetPosition(playerPos);
					}
				}

				/*===================================*
					Button - Box Collision
				*====================================*/
				else if ((it2->second->GetType() == TYPE_BUTTON || it2->second->GetType() == TYPE_BUTTON1
					|| it2->second->GetType() == TYPE_BUTTON2
					|| it2->second->GetType() == TYPE_BUTTON3))
				{
					Button* btn = dynamic_cast<Button*>(it2->second);
					AABB boxAABB = it->second->GetBoundingBox(); // player
					AABB btncol = it2->second->GetBoundingBox();// lever

					AEVec2 vel1 = it->second->GetVelocity();
					AEVec2 vel2 = it2->second->GetVelocity();

					if (CollisionIntersection_RectRect(boxAABB, vel1, btncol, vel2) && (it->second->GetIsCollidable() == true))
					{
						//btn->ActivateGate();
						btn->AddObject(it->second);
					}
					else
					{
						// When no collision detected, we make container empty by remove.
						btn->RemoveObj(it->second);
						//btn->DeActivateGate();
					}

					if (btn->GetObjects().size() && btn->GetIsActivated() == false)
						btn->ActivateGate();
					else if ((btn->GetObjects().size() == 0) && (btn->GetIsActivated() == true))
					{
						btn->DeActivateGate();
					}
				}
			}
		}
	}

	/*===================================*
				Binary Collsiion
	*====================================*/
	for (auto it = list.begin(); it != list.end(); it++)
	{
		GameObject* obj = it->second;
		if (obj->GetFlag() == 0)		// Flip back to == for it to work.
			continue;
		if (obj->GetType() == TYPE_LEVER_GATE || obj->GetType() == TYPE_LEVER_GATE1
			|| obj->GetType() == TYPE_BUTTON_GATE
			|| obj->GetType() == TYPE_BUTTON_GATE1
			|| obj->GetType() == TYPE_BUTTON_GATE2
			|| obj->GetType() == TYPE_BUTTON_GATE3)
			continue;

		//AEVec2 hotSpotPos;
		int result = CheckInstanceBinaryMapCollision(static_cast<float>(obj->GetPosition().x),
			static_cast<float>(obj->GetPosition().y),
			obj->GetScale(), obj->GetScale());
		obj->SetCollisionFlag(result);
		if (result)
		{
			// Position Stuff
			AEVec2 pos = obj->GetPosition();
			float xPos = pos.x;
			float yPos = pos.y;

			// Velocity Stuff
			AEVec2 vel = obj->GetVelocity();
			// Tile Pos
			//AEVec2 tilePos = _tm.GetTilePosAt(xPos, yPos);

			if ((result & COLLISION_BOTTOM))
			{
				vel.y = 0.0f;
				AEVec2 bPos = _tm.GetTilePosAt(xPos, (yPos - (obj->GetScale() * 0.5f)));
				pos.y = (bPos.y * TILE_HEIGHT) + (TILE_HEIGHT) + (obj->GetScale() * 0.5f);
			}
			if (result & COLLISION_TOP)
			{
				//SnapBack(yPos);
				vel.y = 0.0f;
				AEVec2 tPos = _tm.GetTilePosAt(xPos, (yPos + (obj->GetScale() * 0.5f)));
				pos.y = (tPos.y * TILE_HEIGHT) - (obj->GetScale() * 0.5f); // Might need to remove TILE_HEIGHT
			}
			if (result & COLLISION_LEFT)
			{
				vel.x = 0.0f;
				AEVec2 lPos = _tm.GetTilePosAt((xPos - (obj->GetScale() * 0.5f)), yPos);
				pos.x = (lPos.x * TILE_WIDTH) + (TILE_WIDTH)+(obj->GetScale() * 0.5f);
			}
			if (result & COLLISION_RIGHT)	// Consider &
			{
				AEVec2 rPos = _tm.GetTilePosAt((xPos + (obj->GetScale() * 0.5f)), yPos);
				pos.x = (rPos.x * TILE_WIDTH) - (obj->GetScale() * 0.5f);	// Find out why this one don't need tile width.
				vel.x = 0.0f;
			}
			obj->SetPosition(pos);
			obj->SetVelocity(vel);
		}
	}
}

// ======== NEW COLLISION ALGORITHMS BELOW ==========

bool CollisionManager::CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
														const AABB& aabb2, const AEVec2& vel2)
{
	if (aabb1.min.x > aabb2.max.x || aabb1.min.y > aabb2.max.y ||
		aabb1.max.x < aabb2.min.x || aabb1.max.y < aabb2.min.y)
	{
		float tFirst = 0.0f;
		float tLast = g_dt;

		AEVec2 relV = { (vel2.x - vel1.x), (vel2.y - vel1.y) };
		AEVec2Scale(&relV, &relV, g_dt);

		if (relV.x < 0)
		{
			if (aabb1.min.x > aabb2.max.x)
				return false;

			if (aabb1.max.x < aabb2.min.x)
				tFirst = max((aabb1.max.x - aabb2.min.x) / relV.x, tFirst);

			if (aabb1.min.x < aabb2.max.x)
				tLast = min((aabb1.min.x - aabb2.max.x) / relV.x, tLast);
		}

		else
		{
			if (aabb1.min.x > aabb2.max.x)
				tFirst = max((aabb1.min.x - aabb2.max.x) / relV.x, tFirst);

			if (aabb1.max.x > aabb2.min.x)
				tLast = min((aabb1.max.x - aabb2.min.x) / relV.x, tLast);

			if (aabb1.max.x < aabb2.min.x)
				return false;
		}

		if (relV.y < 0)
		{
			if (aabb1.min.y > aabb2.max.y)
				return false;

			if (aabb1.max.y < aabb2.min.y)
				tFirst = max((aabb1.max.y - aabb2.min.y) / relV.y, tFirst);

			if (aabb1.min.y < aabb2.max.y)
				tLast = min((aabb1.min.y - aabb2.max.y) / relV.y, tLast);
		}

		else
		{
			if (aabb1.min.y > aabb2.max.y)
				tFirst = max((aabb1.min.y - aabb2.max.y) / relV.y, tFirst);

			if (aabb1.max.y > aabb2.min.y)
				tLast = min((aabb1.max.y - aabb2.min.y) / relV.y, tLast);

			if (aabb1.max.y < aabb2.min.y)
				return false;
		}

		if (tFirst > tLast)
			return false;
	}

	return true;
}

bool CollisionManager::CollisionIntersection_CircCirc(const AEVec2& pos1, const float scale1,
	const AEVec2& pos2, const float scale2)
{
	// Calculate Distance between objects.
	// Get both scale's and compare.
	// If distance lesser than scale total, collided.
	// Else distance greater than scale total, not collided.

	f32 distance;
	distance = AEVec2Distance(const_cast<AEVec2*>(&pos1), const_cast<AEVec2*>(&pos2));
	
	float colDistance = (scale1 * 0.5f) + (scale2 * 0.5f);
	if (static_cast<float>(distance) < colDistance)
	{
		return true;
	}
	else
		return false;
}

int CollisionManager::CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
	//At the end of this function, "Flag" will be used to determine which sides
	//of the object instance are colliding. 2 hot spots will be placed on each side.

	int flag = 0;

	// 2 Hotspots right side
	float rx1 = static_cast<float>(floor(PosX + scaleX / 2));
	float ry1 = static_cast<float>(floor(PosY + scaleY / 4));
	float ry2 = static_cast<float>(floor(PosY - scaleY / 4));

	// 2 Hotspots left side
	float lx1 = static_cast<float>(floor(PosX - scaleX / 2));
	float ly1 = static_cast<float>(floor(PosY + scaleY / 4));
	float ly2 = static_cast<float>(floor(PosY - scaleY / 4));

	// 2 Hotspots top side
	float ty1 = static_cast<float>(floor(PosY + scaleY / 2));
	float tx1 = static_cast<float>(floor(PosX + scaleX / 4));
	float tx2 = static_cast<float>(floor(PosX - scaleX / 4));

	// 2 Hotspots bottom side
	float by1 = static_cast<float>(floor(PosY - scaleY / 2));
	float bx1 = static_cast<float>(floor(PosX + scaleX / 4));
	float bx2 = static_cast<float>(floor(PosX - scaleX / 4));


	// Check collision for right side.
	if (1 == _tm.GetColMapValue(rx1, ry1) ||
		1 == _tm.GetColMapValue(rx1, ry2))
	{
		flag += COLLISION_RIGHT;
	}

	// Check collision for left side.
	if (1 == _tm.GetColMapValue(lx1, ly1) ||
		1 == _tm.GetColMapValue(lx1, ly2))
	{
		flag += COLLISION_LEFT;
	}

	// Check collision for top side.
	if (1 == _tm.GetColMapValue(tx1, ty1) ||
		1 == _tm.GetColMapValue(tx2, ty1))
	{
		flag += COLLISION_TOP;
	}

	// Check collision for bottom side.
	if (1 == _tm.GetColMapValue(bx1, by1) ||
		1 == _tm.GetColMapValue(bx2, by1))
	{
		flag += COLLISION_BOTTOM;
	}

	// Return the combined collision data.
	return flag;
}


