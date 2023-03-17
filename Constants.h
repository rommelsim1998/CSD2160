#ifndef CONSTANTS_H
#define CONSTANTS_H

/******************************************************************************
* \file			Constants.h
* \brief		This file contains the includes necessary so it is all easier
*				to track.
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

// ==== LIBRARIES ====

#include <iostream>       // std::cout
#include <string>         // std::string
#include <fstream>
#include <sstream>
#include <fmod.hpp>
#include <map>
#include <vector>
#include <AEEngine.h>


//#include <WS2tcpip.h>	// socket programming

// ==== ENUMS ====

#include "ColorList.h"
#include "EnemyStateList.h"
#include "EntityList.h"
#include "GameStateList.h"
#include "Tiletype.h"
#include "GateStateList.h"

// ==== OBJECTS ====

#include "RenderData.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Box.h"
#include "Button.h"
#include "Tile.h"
#include "ImageBox.h"
#include "ColorObj.h"
#include "Checkpoint.h"
#include "Cave1.h"
#include "Cave2.h"
#include "Cave3.h"
#include "Cave4.h"
#include "Cave5.h"
#include "Cave6.h"
#include "Cave7.h"
#include "Wall_Blue.h"
#include "Wall_Green.h"
#include "Wall_Red.h"
#include "Wall_Yellow.h"
#include "Lever.h"
#include "Lever1.h"
#include "Gate.h"
#include "Gate2.h"
#include "Gate3.h"
#include "Lever1.h"
#include "Button.h"
#include "Spikes.h"
#include "Gate.h"
#include "Gate2.h"
#include "Gate3.h"
#include "Gate4.h"
#include "Button1.h"

// ==== MANAGERS ====

#include "TileManager.h"
#include "EntityManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "BackgroundManager.h"
#include "UIManager.h"
#include "PauseMenuManager.h"
#include "AudioManager.h"
#include "OptionsMenuManager.h"


// ==== OTHERS ====

#include "Main.h"
#include "GameStateManager.h"

// ==== VALUES ====

// Math
#define pi 3.14159265358979323846f
#define half_pi pi/2.0f
#define three_pi_half 3.0f*pi/2.0f

// Player
#define PLAYER_JUMP 4.9f

// Enemy
//#define IDLE_COUNT 4.0f
#define IDLE_COUNT 2.0f
#define ENEMY_SPEED 3.0f
#define ENEMY_CHASE_SPEED 5.0f
#define ENEMY_MOVE_MIN 1.2f
#define ENEMY_MOVE_MAX 1.5f

// Colour
#define COLOR_CHANGE_COUNT 0.45f
#define COLOR_POWER_SPEED 60.0f
#define RESET_BACKGROUND_SIZE 1.0f

// PauseUI
#define PAUSE_BACKGROUND_TINT_SCALE 3000.0f
#define BUTTON_WIDTH 40.0f
#define BUTTON_HEIGHT 10.0f
#define BUTTON_SCALE 5.0f
#define PAUSE_UI_LOGO_SCALE 200.0f
#define PAUSE_UI_LOGO_OFFSET_Y 250.0f
#define PAUSE_UI_LOGO_OFFSET_X 90.0f
#define INSTRUCTIONS_IMAGE_SCALE 450.0f
#define INSTRUCTIONS_IMAGE_OFFSET_X 400.0f
#define VOLIMG_SCALE 450.0f

#endif
