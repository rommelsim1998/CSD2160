/******************************************************************************
* \file          GameState_Level1.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#pragma once
//#include "Constants.h"
#include <WS2tcpip.h>
#include <winsock.h>
#include "GameState_Connect.h"
#include "ConnectionManager.h"
#include "Main.h"
#include <iostream>
#include "NetworkingSystem/System.h"
// Create manager instances. (Make them static)
static UIManager& _um = UIManager::GetInstance();
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();
static PauseMenuManager& _pmm = PauseMenuManager::GetInstance();
static Server& ServerHandle = Server::getInstance();
static Client& ClientHandle = Client::getInstance();
 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/
void GameStateLevel1Load(void)
{
	

}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/
void GameStateLevel1Init(void)
{
	_tm.TileManagerLoad("Resources/Level 1.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();
	_em.EntityManagerInitialize();  // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);

}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateLevel1Update(void)
{
	//if its in pause state
	if (!isPaused)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate();     // Physics
		_cm.CollisionManagerUpdate();   // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();
		ClientHandle.Update();
		ServerHandle.Update();
		static float x, y;
		//erverHandle.Update();

		//struct pos {
		//	float x, y;
		//};
		//pos tmp{ 100,100 };
		//ServerHandle.Send(&tmp, sizeof(pos));

		//ClientHandle.Read(x, y);
		//std::cout << "(" << x << ", " << y << ")\n";		// client should read back 100,100


		static float send_x = 100, send_y = 100;
		ServerHandle.Send(send_x, send_y);

		static float recieve_x, recieve_y;
		ClientHandle.Read(recieve_x, recieve_y);

		std::cout << "Recieving: (" << recieve_x << ", " << recieve_x << ")\n";		// client should read back 100,100
	}



	_am.AudioManagerUpdate();
	_pmm.PauseMenuManagerUpdate();
}
/**************************************************************************/
/*!
	The "Drawing" function of this state
	*/
	/**************************************************************************/
void GameStateLevel1Draw(void)
{
	// Object's Draw functions called inside RenderManagerDraw();
	_bm.BackgroundManagerDraw();
	_rm.RenderManagerDraw();
	_um.UIManagerDraw();
	_pmm.PauseMenuManagerDraw();
}

/**************************************************************************/
/*!
	"Free" function of this state
	Destroy the Objects
	*/
	/**************************************************************************/
void GameStateLevel1Free(void)
{
	
	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateLevel1Unload(void)
{
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_pmm.PauseMenuManagerUnload();
	_am.AudioManagerUnload();
}
