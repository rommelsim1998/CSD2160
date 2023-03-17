/******************************************************************************
* \file			GameState_Extra.cpp
* \brief		This file loads up the last level state of the game by
*				calling all the required Manager for necessary loading,
*				initializing, updating, drawing, freeing, and unloading.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

// Create manager instances. 
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static UIManager& _um = UIManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();
static PauseMenuManager& _pmm = PauseMenuManager::GetInstance();

/***************************************************************************/
/*!
\brief
	This function loads the last level state by calling the necessary
	managers that requires loading for this game state.
*/
/**************************************************************************/
void GameStateExtraLoad(void)
{

	_tm.TileManagerLoad("Resources/ExtraLevel.txt");
	_em.EntityManagerLoad();        
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();
}

/***************************************************************************/
/*!
\brief
	This function initializes the last level state by calling the necessary
	managers that requires initializing for this game state.
*/
/**************************************************************************/
void GameStateExtraInit(void)
{

	_em.EntityManagerInitialize(); 
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);
	
}

/***************************************************************************/
/*!
\brief
	This function updates the last level state by calling the necessary
	managers that requires updating for this game state.
*/
/**************************************************************************/
void GameStateExtraUpdate(void)
{
	if (!isPaused)
	{
		_em.EntityManagerUpdate();
		_pm.PhysicsManagerUpdate();   
		_cm.CollisionManagerUpdate(); 
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();

	}
	_am.AudioManagerUpdate();
	_pmm.PauseMenuManagerUpdate();
}

/***************************************************************************/
/*!
\brief
	This function draws the last level state by calling the necessary
	managers that requires drawing for this game state.
*/
/**************************************************************************/
void GameStateExtraDraw(void)
{
	_bm.BackgroundManagerDraw();
	_rm.RenderManagerDraw();
	_um.UIManagerDraw();
	_pmm.PauseMenuManagerDraw();
}

/***************************************************************************/
/*!
\brief
	This function frees the last level state by calling the necessary
	managers that requires freeing for this game state.
*/
/**************************************************************************/
void GameStateExtraFree(void)
{
	
}

/***************************************************************************/
/*!
\brief
	This function unloads the last level state by calling the necessary
	managers that requires unloading for this game state.
*/
/**************************************************************************/
void GameStateExtraUnload(void)
{
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_pmm.PauseMenuManagerUnload();
	_am.AudioManagerUnload();
}
