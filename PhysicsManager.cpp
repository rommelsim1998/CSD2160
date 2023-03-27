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

void PredictPosition(GameObject* obj, float delta_time, AEVec2 serverInput)
{
	//	save copy of current object position
	AEVec2 tempPosition = obj->GetPosition();
	
	AEVec2 newvel = obj->GetVelocity();;
	//	predict obj position
	if (obj->GetDirection() >= pi)	//	left
		newvel.x = -200.f * delta_time;

	else if (obj->GetDirection() <= 0.0f)	//	right
		newvel.x = 200.f * delta_time;
	
	obj->SetVelocity(newvel);

	//	update current object based on prediction
	static AEVec2 newPos{};
	AEVec2Add(&newPos, &tempPosition, &newvel);
	
	if ((newPos.x < serverInput.x || newPos.x > serverInput.x))	//	check if prediction verses server input
		obj->SetPosition(serverInput);
	else
		obj->SetPosition(newPos);
}



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
	static int x1{}, y1{}, x2{}, y2{};
	static int rec_x1{}, rec_y1{};
	static int rec_x2{}, rec_y2{};
	static GameObject* go1{}, * go2{};

	ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);
	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		if (it->first == 8) go1 = it->second;
		else if (it->first == 7) go2 = it->second;
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

		// move player 1 
		if (_id == 1)
		{
			if (go1)
			{
				// Calculate Player 1 physics internally
				static AEVec2 newPos1{};
				auto oldPos1 = go1->GetPosition();
				auto vel1 = go1->GetVelocity();
				AEVec2Add(&newPos1, &oldPos1, &vel1);
				if (!(newPos1.x >= 1000 && newPos1.y >= 1000 && newPos1.x < 0 && newPos1.y < 0))
					go1->SetPosition(newPos1);

				x1 = newPos1.x;
				y1 = newPos1.y;
			}

			// Client Send Player 1 data over to server for Player 2 to read
			//ClientHandle.Send(x1, y1, rec_x2, rec_y2);

			// Update Player 2 physics from server 
			//ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);
			if (go2)
			{
				AEVec2 go2PosFromServer = { static_cast<f32>(rec_x2), static_cast<f32>(rec_y2) };
				//go2->SetPosition(go2PosFromServer);
				PredictPosition(go2, g_dt, go2PosFromServer);
			}
		}
		else if (_id == 2)
		{
			if (go2)
			{
				// Calulcate Player 2 physics internally
				static AEVec2 newPos2{};
				auto oldPos2 = go2->GetPosition();
				auto vel2 = go2->GetVelocity();
				AEVec2Add(&newPos2, &oldPos2, &vel2);
				if (!(newPos2.x >= 1000 && newPos2.y >= 1000 && newPos2.x < 0 && newPos2.y < 0))
					go2->SetPosition(newPos2);

				x2 = newPos2.x;
				y2 = newPos2.y;
			}

			// Client send Player 2 data over to server for Player 1 to read
			//ClientHandle.Send(rec_x1, rec_y1, x2, y2);

			// Update Players 1 physics from server
			//ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);

			if (go1)
			{
				AEVec2 go1PosFromServer = { static_cast<f32>(rec_x1), static_cast<f32>(rec_y1) };
				//go1->SetPosition(go1PosFromServer);
				PredictPosition(go2, g_dt, go1PosFromServer);
			}
		}
		/*
		// player 1
		if (go1)
		{
			static AEVec2 newPos1{};
			auto oldPos1 = go1->GetPosition();
			auto vel1 = go1->GetVelocity();
			AEVec2Add(&newPos1, &oldPos1, &vel1);
			x1 = newPos1.x; y1 = newPos1.y;
			AEVec2 newpos_1 = { rec_x1, rec_y1 };
			if (rec_x1 >= 1000 && rec_y1 >= 1000 && rec_x1 < 0 && rec_y1 < 0)
			{
				go1->SetPosition(oldPos1);
			}
			else
			{
				go1->SetPosition(newPos1);
			}

			ClientHandle.Send(x1, y1, rec_x2, rec_y2);

			
		}

		// player 2
		else if (it->first == 7 && _id == 2)
		{
			static AEVec2 newPos2{};
			auto oldPos2 = it->second->GetPosition();
			auto vel2 = it->second->GetVelocity();
			AEVec2Add(&newPos2, &oldPos2, &vel2);
			x2 = newPos2.x; y2 = newPos2.y;

			AEVec2 newpos_2 = { rec_x2, rec_y2 };
			if (rec_x2 >= 1000 && rec_y2 >= 1000 && rec_x2 < 0 && rec_y2 < 0)
			{
				it->second->SetPosition(oldPos2);
			}
			else
			{
				it->second->SetPosition(newPos2);
			}

			ClientHandle.Send(rec_x1, rec_y1, x2, y2);
			ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);
		}
		*/

		
		

		// engine proof updated AABB 

		/*AABB first, second;*/

		/*first.min.x = -0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.min.y = -0.5f * it->second->GetScale() + it->second->GetPosition().y;
		first.max.x = 0.5f * it->second->GetScale() + it->second->GetPosition().x;
		first.max.y = 0.5f * it->second->GetScale() + it->second->GetPosition().y;
		it->second->SetBoundingBox(first);*/
	}



	
	if(_id == 1)
		ClientHandle.Send(x1, y1, rec_x2, rec_y2);
	else if(_id == 2)
		ClientHandle.Send(rec_x1, rec_y1, x2, y2);
}
