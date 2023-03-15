/******************************************************************************
* \file			GameState_Menu.cpp
* \brief		Main Menu Game state,to Create Main Menu and display on screen,
				also directs to other gamestates
* \author		Tan Jian Jie, 100% Code Contribution

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
static OptionsMenuManager& _omm = OptionsMenuManager::GetInstance();


 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/
void GameStateMenuLoad(void)
{
	
	_tm.TileManagerLoad("Resources/Menu.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_am.AudioManagerLoad();
	_omm.OptionsMenuManagerLoad();

}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/
void GameStateMenuInit(void)
{
	
	_em.EntityManagerInitialize();  // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);
	//_am.AudioManagerInitialize();
	

}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateMenuUpdate(void)
{
	if (!isOptionsEnabled)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate();     // Physics
		_cm.CollisionManagerUpdate();   // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();	
	}
	_omm.OptionsMenuManagerUpdate();
	_am.AudioManagerUpdate();
}
/**************************************************************************/
/*!
	The "Drawing" function of this state
	*/
	/**************************************************************************/
void GameStateMenuDraw(void)
{
	_bm.BackgroundManagerDraw();
	// Object's Draw functions called inside RenderManagerDraw();
	_rm.RenderManagerDraw();
	_um.UIManagerDraw();
	_omm.OptionsMenuManagerDraw();
}

/**************************************************************************/
/*!
	"Free" function of this state
	Destroy the Objects
	*/
	/**************************************************************************/
void GameStateMenuFree(void)
{
	
	
	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateMenuUnload(void)
{
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_am.AudioManagerUnload();
	_omm.OptionsMenuManagerUnload();
}
