#ifndef CS230_MAIN_H_
#define CS230_MAIN_H_

/******************************************************************************
* \file			Main.h
* \brief		This file contains the main which is where the actual game loop
*				occurs.
*				state
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

//------------------------------------
// Globals

extern float	g_dt;
extern double	g_appTime;
extern bool		full_screen_me;
extern bool		isPaused;
extern bool     isOptionsEnabled;

// ---------------------------------------------------------------------------
#include "GameStateList.h"
#include "GameObject.h"
#include"GameStateManager.h"
#include "Test_Level.h"
#include "GameState_Level1.h"
#include "GameState_Level2.h"
#include "GameState_Level3.h"
#include "GameState_Level4.h"
#include "GameState_Level5.h"
#include "GameState_Level6.h"
#include "GameState_Level7.h"
#include "GameState_Level8.h"
#include "GameState_Connect.h"
#include "GameState_LS.h"
#include "GameState_End.h"
#include "GameState_SplashScreen.h"
#include "GameState_Credits.h"
#include "GameState_Extra.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "AudioManager.h"

#include "GameState_Menu.h"

extern s8		font;

#endif