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

//#include "Constants.h"


#include <WS2tcpip.h>
#include <winsock.h>
#include "GameState_Connect.h"
#include "GameState_Level1.h"
#include "Main.h"
#include <iostream>
#include "NetworkingSystem/System.h"
#define GRAVITY -10.0f;

int _id;
using _em = EntityManager;
static Server& ServerHandle = Server::getInstance();
static Client& ClientHandle = Client::getInstance();


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
		if(!(it->first == 7 || it->first == 8))
			it->second->SetPosition(newpos);		// dont set pos for go1 and go2

		else
		{
			static int x1{}, y1{}, x2{}, y2{};
			// player 1
			if (it->first == 7)
			{
				x1 = it->second->GetPosition().x;
				y1 = it->second->GetPosition().y;
			}
			// player 2
			else if (it->first == 8)
			{
				x2 = it->second->GetPosition().x;
				y2 = it->second->GetPosition().y;
			}
			if (it->first == 7 || it->first == 8)
			{
				if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0 &&
					x1 <= 1000 && y1 <= 1000 && x2 <= 1000 && y2 <= 1000)
					ClientHandle.Send(x1, y1, x2, y2);
			}


			static int rec_x1{}, rec_y1{};
			static int rec_x2{}, rec_y2{};
			ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);

			// player 1
			if (_id == 1)
			{
				if (it->first == 7)
				{
					AEVec2 updatedPos_go1 = { (float)rec_x1, (float)rec_y1 };

					//it->second->SetVelocity(updatedPos_go1);
					//it->second->SetPosition(updatedPos_go1);
				}
			}

			// player 2
			if (_id == 2)
			{
				if (it->first == 8)
				{
					AEVec2 updatedPos_go2 = { (float)rec_x2, (float)rec_y2 };
					//it->second->SetVelocity(updatedPos_go2);
					//it->second->SetPosition(updatedPos_go2);
				}

			}
		}
		
		

		// engine proof updated AABB 

		/*AABB first, second;*/

		/*first.min.x = -0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.min.y = -0.5f * it->second->GetScale() + it->second->GetPosition().y;
		first.max.x = 0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.max.y = 0.5f * it->second->GetScale() + it->second->GetPosition().y;
		it->second->SetBoundingBox(first);*/
	}

}
