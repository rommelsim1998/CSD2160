/******************************************************************************
* \file          GameState_Level1.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

/******************************************************************************
						CLIENT
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

const std::string ip = "192.168.128.173";
const short unsigned port = 54000;

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

static int clientID;
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
	ClientHandle.Init(ip, port);
	
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
	static GameObject* go1 = _em.GetEntityList()[7];
	static GameObject* go2 = _em.GetEntityList()[8];

	int x1 = static_cast<int>(go1->GetPosition().x);
	int y1 = static_cast<int>(go1->GetPosition().y);
	int x2 = static_cast<int>(go2->GetPosition().x);
	int y2 = static_cast<int>(go2->GetPosition().y);
	ClientHandle.Send(x1, y1, x2, y2);

	int rec_x1, rec_y1;
	int rec_x2, rec_y2;
	ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);
	std::cout << "[Client]: " << rec_x1 << ", " << rec_y1 << ", " <<
		rec_y1 << ", " << rec_y2 << "\n";


	//if its in pause state
	if (!isPaused)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate();     // Physics
		_cm.CollisionManagerUpdate();   // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();
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
