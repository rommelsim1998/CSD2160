/******************************************************************************
* \file			Player.cpp
* \brief		This file handles the initializing of player object, updates in 
				which the user can do, and drawing the player object.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "ConnectionManager.h"
#include "Constants.h"

using _em = EntityManager;
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();

/***************************************************************************/
/*!
\brief
	Player constructor that constructs the player objects by inheriting 
	from GameObject. It also checks if a color.txt file is available, else
	create one. It also set the starting background color for all game states.

\param id
	The id value tagged to the player object.
*/
/**************************************************************************/
Player::Player(int id) : GameObject{TYPE_PLAYER, id}, test{ 6 }
{
	//Checks if a color.txt file is available, else create one.
	std::ifstream colorfile;
	colorfile.open("Resources/color.txt");
	if (colorfile.peek() == std::ifstream::traits_type::eof())
	{
		colorfile.close();
		std::ofstream colorfile2;
		colorfile2.open("Resources/color.txt");
		colorfile2 << "a" << "\n" << "b" << "\n" << "c" << "\n" << "d";
		colorfile2.close();
	}
	else
	{
		colorfile.close();
	}

	//Set starting background color of levels
	if (current == GS_LEVEL1 || current == GS_MAINMENU || current == GS_LEVEL2 || current == GS_TESTLEVEL || 
		current == GS_LEVEL4 || current == GS_LEVEL7 || current == GS_LEVEL8) //King Story
	{
		startingColor = Color::COLOR_GREY;
	}
	else if (current == GS_LEVEL6 || current == GS_LEVEL3)
	{
		startingColor = Color::COLOR_BLUE;
	}
	else if (current == GS_LEVEL5 || current == GS_EXTRA)
	{
		startingColor = Color::COLOR_GREEN;
	}
	else if (current == GS_END)
	{
		startingColor = Color::COLOR_YELLOW;
	}
}

/***************************************************************************/
/*!
\brief
	Player destructor that destroys the player object.
*/
/**************************************************************************/
Player::~Player() 
{

}

/***************************************************************************/
/*!
\brief
	A function that initializes the player object during each game state.
*/
/**************************************************************************/
void Player::GameObjectInitialize()
{
	if (GetType() == NULL)
	{
		// Nullptr
	}
	SetScale(70.0f);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
	SetColor(startingColor);
	_bm.SetBackgroundColor(startingColor);

	const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
	for (auto it = list.begin(); it != list.end(); it++)
	{
		if (it->second->GetColor() != Color::COLOR_BLACK)
		{
			if (it->second->GetColor() == GetColor())
			{
				it->second->SetIsCollidable(false);
			}
			else
			{
				it->second->SetIsCollidable(true);
			}
		}
	}
}

/***************************************************************************/
/*!
\brief
	A function that handles updates on user input on the player object 
	during each game state.
*/
/**************************************************************************/
void Player::GameObjectUpdate() 
{
	// Trigger game fullscreen
	/*
	if (AEInputCheckTriggered(AEVK_O))
	{
		full_screen_me = !full_screen_me;
		AEToogleFullScreen(full_screen_me);
	}
	*/

	// Enable or disable Player gravity based on tile
	if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y) == TileType::TILE_EMPTY)
	{
		SetHasGravity(true);

		if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y - GetScale() * 0.5f) == TileType::TILE_LADDER)
		{
			SetHasGravity(false);
		}
		else
		{
			SetHasGravity(true);
		}
	}

	if (Connectionmanager::isMultiplayer == true)
	{
		// Movement left and right of Player
		if (AEInputCheckCurr(AEVK_LEFT))
		{
			SetDirection(pi);
			AEVec2 newvel = GetVelocity();
			newvel.x = -playerSpeed * g_dt;
			SetVelocity(newvel);
		}
		else if (AEInputCheckCurr(AEVK_RIGHT))
		{
			SetDirection(0.0f);
			AEVec2 newvel = GetVelocity();
			newvel.x = playerSpeed * g_dt;
			SetVelocity(newvel);
		}
		else
		{
			AEVec2 newvel = GetVelocity();
			newvel.x = 0.0f;
			if (GetCollisionFlag() == COLLISION_BOTTOM)
			{
				newvel.y = 0.0f;
			}
			SetVelocity(newvel);
		}

	}
	else
	{
		// Movement left and right of Player
		if (AEInputCheckCurr(AEVK_A))
		{
			SetDirection(pi);
			AEVec2 newvel = GetVelocity();
			newvel.x = -playerSpeed * g_dt;
			SetVelocity(newvel);
		}
		else if (AEInputCheckCurr(AEVK_D))
		{
			SetDirection(0.0f);
			AEVec2 newvel = GetVelocity();
			newvel.x = playerSpeed * g_dt;
			SetVelocity(newvel);
		}
		else
		{
			AEVec2 newvel = GetVelocity();
			newvel.x = 0.0f;
			if (GetCollisionFlag() == COLLISION_BOTTOM)
			{
				newvel.y = 0.0f;
			}
			SetVelocity(newvel);
		}
		
	}

	// not used
	if (Connectionmanager::isMultiplayer == true)
	{
		// Player climbing up the ladder
		if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y) == TileType::TILE_LADDER)
		{
			if (AEInputCheckCurr(AEVK_UP))
			{
				AEVec2 newvel = GetVelocity();
				newvel.y = 5.0f;
				SetVelocity(newvel);
			}
			else if (AEInputCheckReleased(AEVK_UP))
			{
				SetHasGravity(false);
				AEVec2 newvel = GetVelocity();
				newvel.y = 0.0f;
				SetVelocity(newvel);
			}
		}

		// Player climbing down the ladder
		if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y - GetScale() * 0.5f) == TileType::TILE_LADDER)
		{
			if (AEInputCheckCurr(AEVK_DOWN))
			{
				AEVec2 newvel = GetVelocity();
				newvel.y = -5.0f;
				SetVelocity(newvel);
			}
			else if (AEInputCheckReleased(AEVK_DOWN))
			{
				SetHasGravity(false);
				AEVec2 newvel = GetVelocity();
				newvel.y = 0.0f;
				SetVelocity(newvel);
			}
		}

	}
	else
	{
		// Player climbing up the ladder
		if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y) == TileType::TILE_LADDER)
		{
			if (AEInputCheckCurr(AEVK_W))
			{
				AEVec2 newvel = GetVelocity();
				newvel.y = 5.0f;
				SetVelocity(newvel);
			}
			else if (AEInputCheckReleased(AEVK_W))
			{
				SetHasGravity(false);
				AEVec2 newvel = GetVelocity();
				newvel.y = 0.0f;
				SetVelocity(newvel);
			}
		}

		// Player climbing down the ladder
		if (_tm.GetTileTypeAt(GetPosition().x, GetPosition().y - GetScale() * 0.5f) == TileType::TILE_LADDER)
		{
			if (AEInputCheckCurr(AEVK_S))
			{
				AEVec2 newvel = GetVelocity();
				newvel.y = -5.0f;
				SetVelocity(newvel);
			}
			else if (AEInputCheckReleased(AEVK_S))
			{
				SetHasGravity(false);
				AEVec2 newvel = GetVelocity();
				newvel.y = 0.0f;
				SetVelocity(newvel);
			}
		}
	}



	if (Connectionmanager::isMultiplayer == true)
	{
		// Player jump
		if (AEInputCheckTriggered(AEVK_UP) && ((GetCollisionFlag() & COLLISION_BOTTOM) || isStanding ||
			_tm.GetTileTypeAt(GetPosition().x, GetPosition().y - GetScale() * 0.5f) == TileType::TILE_LADDER))
		{
			AEVec2 vel = GetVelocity();
			vel.y = PLAYER_JUMP;
			SetVelocity(vel);
			isStanding = false;
		}
	}
	else
	{
		// Player jump
		if (AEInputCheckTriggered(AEVK_SPACE) && ((GetCollisionFlag() & COLLISION_BOTTOM) || isStanding ||
			_tm.GetTileTypeAt(GetPosition().x, GetPosition().y - GetScale() * 0.5f) == TileType::TILE_LADDER))
		{
			AEVec2 vel = GetVelocity();
			vel.y = PLAYER_JUMP;
			SetVelocity(vel);
			isStanding = false;
		}
	}
	

	if (Connectionmanager::isMultiplayer==true)
	{
		// Direction player is facing when pulling the box
		if (AEInputCheckCurr(AEVK_M) && AEInputCheckCurr(AEVK_LEFT))
		{
			SetDirection(0.0f);
		}
		else if (AEInputCheckCurr(AEVK_M) && AEInputCheckCurr(AEVK_RIGHT))
		{
			SetDirection(pi);
		}
	}
	else
	{
		// Direction player is facing when pulling the box
		if (AEInputCheckCurr(AEVK_LCTRL) && AEInputCheckCurr(AEVK_A))
		{
			SetDirection(0.0f);
		}
		else if (AEInputCheckCurr(AEVK_LCTRL) && AEInputCheckCurr(AEVK_D))
		{
			SetDirection(pi);
		}

	}

	

	// Read color.txt file to see if player has unlocked that color so to be able to use it
	std::ifstream colorfile;
	std::string line;

	colorfile.open("Resources/color.txt");

	if (colorfile.is_open())
	{
		while (getline(colorfile, line))
		{
			size_t found;
			// Red color
			if (((found = line.find("A")) != std::string::npos))
			{
				if (AEInputCheckTriggered(AEVK_COMMA) &&
					(_bm.GetCounter() <= 0.0f))
				{
					SetColor(Color::COLOR_RED);
					if (GetColor() != _bm.GetColor())
						_bm.ChangeColor(Color::COLOR_RED);

					const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
					for (auto it = list.begin(); it != list.end(); it++)
					{
						if (it->second->GetColor() != Color::COLOR_BLACK)
						{
							if (it->second->GetColor() == GetColor())
							{
								it->second->SetIsCollidable(false);
							}
							else
							{
								it->second->SetIsCollidable(true);
							}
						}
					}
				}
			}
			// Blue color
			if (((found = line.find("B")) != std::string::npos))
			{
				if (Connectionmanager::isMultiplayer == true)
				{

				}
				else
				{

					if (AEInputCheckTriggered(AEVK_2) &&
						(_bm.GetCounter() <= 0.0f))
					{
						SetColor(Color::COLOR_BLUE);
						if (GetColor() != _bm.GetColor())
							_bm.ChangeColor(Color::COLOR_BLUE);

						const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
						for (auto it = list.begin(); it != list.end(); it++)
						{
							if (it->second->GetColor() != Color::COLOR_BLACK)
							{
								if (it->second->GetColor() == GetColor())
								{
									it->second->SetIsCollidable(false);
								}
								else
								{
									it->second->SetIsCollidable(true);
								}
							}
						}
					}

				}
		
			}
			// Green color
			if (((found = line.find("C")) != std::string::npos))
			{
				if (AEInputCheckTriggered(AEVK_PERIOD) &&
					(_bm.GetCounter() <= 0.0f))
				{
					SetColor(Color::COLOR_GREEN);
					if (GetColor() != _bm.GetColor())
						_bm.ChangeColor(Color::COLOR_GREEN);

					const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
					for (auto it = list.begin(); it != list.end(); it++)
					{
						if (it->second->GetColor() != Color::COLOR_BLACK)
						{
							if (it->second->GetColor() == GetColor())
							{
								it->second->SetIsCollidable(false);
							}
							else
							{
								it->second->SetIsCollidable(true);
							}
						}
					}
				}
			}
			// Yellow color
			if (((found = line.find("D")) != std::string::npos))
			{

				if (Connectionmanager::isMultiplayer == true)
				{

				}
				else
				{
					if (AEInputCheckTriggered(AEVK_4) &&
						(_bm.GetCounter() <= 0.0f))
					{
						SetColor(Color::COLOR_YELLOW);
						if (GetColor() != _bm.GetColor())
							_bm.ChangeColor(Color::COLOR_YELLOW);

						const std::map<int, GameObject*>& list = _em::GetInstance().GetEntityList();
						for (auto it = list.begin(); it != list.end(); it++)
						{
							if (it->second->GetColor() != Color::COLOR_BLACK)
							{
								if (it->second->GetColor() == GetColor())
								{
									it->second->SetIsCollidable(false);
								}
								else
								{
									it->second->SetIsCollidable(true);
								}
							}
						}
					}
				}
		
			}
		}
		colorfile.close();
	}

	// Setting of position of Player
	AEVec2 distance, velocity, position;
	velocity = GetVelocity();
	position = GetPosition();
	AEVec2Scale(&distance, &velocity, (float)AEFrameRateControllerGetFrameTime());
	AEVec2Add(&position, &position, &distance);
	SetPosition(position);

	// Setting of bounding box for Player
	AABB boundbox;
	boundbox.min.x = -0.3f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.3f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.3f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.3f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
}

/***************************************************************************/
/*!
\brief
	A function that draws the player object during each game state.
*/
/**************************************************************************/
void Player::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale = GetScale();

	// If current direction is left make scale left.
	if (half_pi < GetDirection() &&
		three_pi_half > GetDirection())
	{
		AEMtx33Scale(&mScale, -theScale, theScale);
	}
	else
		AEMtx33Scale(&mScale, theScale, theScale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMTrans(mTrans);

	AEGfxSetCamPosition(pos.x, pos.y);   //Set Camera
}

/***************************************************************************/
/*!
\brief
	A function that set the boolean check in which whether the player is
	standing hence to be able to enable jumping of player.

\param standing
	The boolean that is set to change the variable isStanding.
*/
/**************************************************************************/
void Player::SetisStanding(bool standing)
{
	isStanding = standing;
}

/***************************************************************************/
/*!
\brief
	A function that returns the boolean of the variable pull for checks
	if player can pull.
*/
/**************************************************************************/
bool Player::GetPull() const
{
	return pull;
}

/***************************************************************************/
/*!
\brief
	A function that set the boolean check in which whether the player can
	pull, hence allowing pulling of objects of player.

\param able
	The boolean that is set to change the variable pull.
*/
/**************************************************************************/
void Player::SetPull(bool able)
{
	pull = able;
}