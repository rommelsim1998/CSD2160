/******************************************************************************
* \file			GameState_LS.cpp
* \brief		This file loads up the level select state of the game by 
*				calling all the required Manager for necessary loading,
*				initializing, updating, drawing, freeing, and unloading.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

// Create manager instances
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
	This function loads the level select state by calling the necessary
	managers that requires loading for this game state. It also checks if
	a levels.txt exist, else create one. Not only that, it checks if user
	meet the requirements in the levels.txt, which if does, changes the 
	level select map to a different one.
*/
/**************************************************************************/
void GameStateLSLoad(void)
{
	std::ifstream levelfile;
	levelfile.open("Resources/levels.txt");
	if (levelfile.peek() == std::ifstream::traits_type::eof())
	{
		levelfile.close();
		std::ofstream levelfile2;
		levelfile2.open("Resources/levels.txt");
		levelfile2 << " ";
		levelfile2.close();
	}
	else
	{
		levelfile.close();
	}

	std::ifstream levelfile3;
	std::string line;
	levelfile3.open("Resources/levels.txt");
	if (levelfile3.is_open())
	{
		int count = 0;
		std::stringstream str;
		while (getline(levelfile3, line))
		{
			str << line;
		}

		std::string charac;
		while (std::getline(str, charac, ','))
		{
			++count;
		}

		if (count < 9)
		{
			_tm.TileManagerLoad("Resources/LS.txt");
		}
		else
		{
			_tm.TileManagerLoad("Resources/LS2.txt");
		}
		levelfile3.close();
	}

	_em.EntityManagerLoad();        
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_am.AudioManagerLoad();
}

/***************************************************************************/
/*!
\brief
	This function initializes the level select state by calling the necessary
	managers that requires initializing for this game state.
*/
/**************************************************************************/
void GameStateLSInit(void)
{
	_em.EntityManagerInitialize();  
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);
	
}

/***************************************************************************/
/*!
\brief
	This function updates the level select state by calling the necessary
	managers that requires updating for this game state.
*/
/**************************************************************************/
void GameStateLSUpdate(void)
{
	_em.EntityManagerUpdate();     
	_pm.PhysicsManagerUpdate();     
	_cm.CollisionManagerUpdate();   
	_bm.BackgroundManagerUpdate();
	_um.UIManagerUpdate();
	_am.AudioManagerUpdate();
}

/***************************************************************************/
/*!
\brief
	This function draws the level select state by calling the necessary
	managers that requires drawing for this game state.
*/
/**************************************************************************/
void GameStateLSDraw(void)
{
	_bm.BackgroundManagerDraw();
	_rm.RenderManagerDraw();
	_um.UIManagerDraw();
}

/***************************************************************************/
/*!
\brief
	This function frees the level select state by calling the necessary
	managers that requires freeing for this game state.
*/
/**************************************************************************/
void GameStateLSFree(void)
{

}

/***************************************************************************/
/*!
\brief
	This function unloads the level select state by calling the necessary
	managers that requires unloading for this game state.
*/
/**************************************************************************/
void GameStateLSUnload(void)
{
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_am.AudioManagerUnload();
}
