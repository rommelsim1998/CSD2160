/******************************************************************************
* \file          GameState_Level3.cpp
* \brief         This file is the main file for Game state of level 3
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

// Create manager instances. (Make them static)
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static UIManager& _um = UIManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();
static PauseMenuManager& _pmm = PauseMenuManager::GetInstance();


 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/
void GameStateLevel3Load(void)
{
	
	_tm.TileManagerLoad("Resources/Level 3.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_bm.BackgroundManagerLoad();
	_um.UIManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();
}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/
void GameStateLevel3Init(void)
{
	
	_em.EntityManagerInitialize();  // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);

}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateLevel3Update(void)
{
	if (!isPaused)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate();     // Physics
		_cm.CollisionManagerUpdate();   // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();
	}
	_pmm.PauseMenuManagerUpdate();
	_am.AudioManagerUpdate();
}
/**************************************************************************/
/*!
	The "Drawing" function of this state
	*/
	/**************************************************************************/
void GameStateLevel3Draw(void)
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
void GameStateLevel3Free(void)
{
	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateLevel3Unload(void)
{
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_pmm.PauseMenuManagerUnload();
	_am.AudioManagerUnload();
}
