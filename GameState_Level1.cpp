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
// #include "Constants.h"
#include <WS2tcpip.h>
#include <winsock.h>
#include "GameState_Connect.h"
#include "ConnectionManager.h"
#include "Main.h"
#include <iostream>
#include "NetworkingSystem/System.h"

const std::string ip = "192.168.26.56";

const short unsigned port = 54000;

// Create manager instances. (Make them static)
static UIManager &_um = UIManager::GetInstance();
static EntityManager &_em = EntityManager::GetInstance();
static RenderManager &_rm = RenderManager::GetInstance();
static PhysicsManager &_pm = PhysicsManager::GetInstance();
static TileManager &_tm = TileManager::GetInstance();
static CollisionManager &_cm = CollisionManager::GetInstance();
static BackgroundManager &_bm = BackgroundManager::GetInstance();
static AudioManager &_am = AudioManager::GetInstance();
static PauseMenuManager &_pmm = PauseMenuManager::GetInstance();
static Server &ServerHandle = Server::getInstance();
static Client &ClientHandle = Client::getInstance();

/**************************************************************************/
/*!
	"Load" function of this state
	*/
/**************************************************************************/

void GameStateLevel1Load(void)
{

	_tm.TileManagerLoad("Resources/Level 1.txt");
	_em.EntityManagerLoad(); // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();
}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
/**************************************************************************/
void GameStateLevel1Init(void)
{
	ClientHandle.Init(ip, port);

	// assign when id is NULL.

	_em.EntityManagerInitialize(); // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);
	static int tmp{};
	if (_id == 0)
	{
		while (1)
		{
			char tmp[69] = "hello\n";
			ClientHandle.Send(tmp, 69);
			_id = ClientHandle.GetClientId();
			if (_id > 0)
				break;
		}
		/*while (!(tmp == 1 || tmp == 2))
		{
			tmp = ClientHandle.GetClientId();
			_id = tmp;
			break;
		}*/
	}

	static bool is2PlayersConnected = false;
	while (1)
	{
		is2PlayersConnected = ClientHandle.WaitFor2Players();
		if (is2PlayersConnected == true)
		{
			std::cout << "My ID is " << _id << "Connected players is 2. Moving to game state update!\n";
			return;
		}
	}
}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
/**************************************************************************/
static AEVec2 g1_pos, g2_pos;
void GameStateLevel1Update(void)
{
	// if its in pause state
	if (!isPaused)
	{
	

		_em.EntityManagerUpdate();	  // Logic
		_pm.PhysicsManagerUpdate();	  // Physics
		_cm.CollisionManagerUpdate(); // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();
	}

	/*
	static GameObject *go1 = _em.GetEntityList()[8];
	static GameObject *go2 = _em.GetEntityList()[7];

	int x1 = static_cast<int>(go1->GetPosition().x);
	int y1 = static_cast<int>(go1->GetPosition().y);
	int x2 = static_cast<int>(go2->GetPosition().x);
	int y2 = static_cast<int>(go2->GetPosition().y);
	*/
	/*

	// ClientHandle.Send(x1, y1, x2, y2);

	int rec_x1, rec_y1;
	int rec_x2{}, rec_y2{};

	ClientHandle.Read(rec_x1, rec_y1, rec_x2, rec_y2);

	g1_pos = {float(rec_x1), float(rec_y1)};
	g2_pos = {float(rec_x2), float(rec_y2)};
	if (_id == 1)
	{
		go2->SetPosition(g2_pos);
	}
	else if (_id == 2)
	{
		go1->SetPosition(g1_pos);
	}
	*/

	_am.AudioManagerUpdate();
	_pmm.PauseMenuManagerUpdate();

	//ClientHandle.Send(x1, y1, x2, y2);
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
