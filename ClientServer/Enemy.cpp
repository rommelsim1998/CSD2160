/******************************************************************************
* \file			Enemy.cpp
* \brief        This file contains the class definition of the Enemy class
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The Enemy object is an object entity in the game that represents
*				the knights of King Mono.
*				It has the it's own simple AI state system.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Enemy.h"

static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();

/***************************************************************************/
/*!
	\brief
		The single parameter constructor for Enemy.

	\param id
		The new id to be assigned to this enemy.
*/
/**************************************************************************/
Enemy::Enemy(int id)
	: GameObject(TYPE_ENEMY, id), horizontalDetectRange{ 0 },
	moveCounter{ 0 }, idleCounter{ IDLE_COUNT },
	innerState{ ENEMY_INNER_STATE::INNER_STATE_ON_ENTER }, previousState{ ENEMY_STATE::STATE_MOVE_RIGHT },
	state{ ENEMY_STATE::STATE_MOVE_LEFT }{
	AEVec2 zero;
	AEVec2Zero(&zero);
	detectionBox.max = zero;
	detectionBox.min = zero;
}

/***************************************************************************/
/*!
	\brief
		The deconstructor for the Enemy object.
*/
/**************************************************************************/
Enemy::~Enemy() {
	// Empty By Design
}

/***************************************************************************/
/*!
	\brief
		Gets the State of the enemy.
*/
/**************************************************************************/
ENEMY_STATE Enemy::GetState() const {
	return state;
}

/***************************************************************************/
/*!
	\brief
		Gets the Inner State of the enemy.
*/
/**************************************************************************/
ENEMY_INNER_STATE Enemy::GetInnerState() const {
	return innerState;
}

/***************************************************************************/
/*!
	\brief
		Get the Detection Box of the enemy.
*/
/**************************************************************************/
AABB Enemy::GetDetectionBox() const {
	return detectionBox;
}

/***************************************************************************/
/*!
	\brief
		Sets the state of the enemy.

	\param nowState
		The state to set onto the enemy.
*/
/**************************************************************************/
void Enemy::SetState(ENEMY_STATE const nowState) {
	state = nowState;
}

/***************************************************************************/
/*!
	\brief
		Sets the previous state of the enemy.

	\param prevState
		The previous state of the enemy.
*/
/**************************************************************************/
void Enemy::SetPreviousState(ENEMY_STATE const prevState) {
	previousState = prevState;
}

/***************************************************************************/
/*!
	\brief
		Sets the Inner State of the enemy.

	\param nowInnerState
		The inner state to set the inner state into now.

*/
/**************************************************************************/
void Enemy::SetInnerState(ENEMY_INNER_STATE const nowInnerState) {
	innerState = nowInnerState;
}

/***************************************************************************/
/*!
	\brief
		Sets the Detection Box of the enemy.

	\param detBox
		The detection box to set onto the enemy.
*/
/**************************************************************************/
void Enemy::SetDetectionBox(AABB const detBox) {
	detectionBox = detBox;
}

/***************************************************************************/
/*!
	\brief
		Sets the move counter of the enemy.

	\param count
		The count to set the move counter to.

*/
/**************************************************************************/
void Enemy::SetMoveCounter(float const count) {
	moveCounter = count;
}

/***************************************************************************/
/*!
	\brief
		Decreases the idleCounter time by a specified time.

	\param time
		The amount of time to decrease onto the idleCounte of enemy.

*/
/**************************************************************************/
void Enemy::DecreaseIdleTime(float const time)
{
	idleCounter -= time;
}

/***************************************************************************/
/*!
	\brief
		Decreases the move time of the enemy by specified time.

	\param time
		The time to decrease the move counter by.

*/
/**************************************************************************/
void Enemy::DecreaseMoveTime(float const time) {
	moveCounter -= time;
}

/***************************************************************************/
/*!
	\brief
		Initializes the enemy class.
*/
/**************************************************************************/
void Enemy::GameObjectInitialize()
{
	SetScale(70.0f);
	horizontalDetectRange = 10;
	SetState(ENEMY_STATE::STATE_MOVE_LEFT);
	SetInnerState(ENEMY_INNER_STATE::INNER_STATE_ON_ENTER);
	SetDirection(0.0f);
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
	return;
}

/***************************************************************************/
/*!
	\brief
		Updates the enemy class
*/
/**************************************************************************/
void Enemy::GameObjectUpdate()
{
	// Setting normal bounding box of enemy.
	AABB boundbox;
	boundbox.min.x = -0.4f * GetScale() + GetPosition().x;
	boundbox.max.x = 0.4f * GetScale() + GetPosition().x;
	boundbox.min.y = -0.4f * GetScale() + GetPosition().y;
	boundbox.max.y = 0.4f * GetScale() + GetPosition().y;
	SetBoundingBox(boundbox);
	ChangeState();
}

/***************************************************************************/
/*!
	\brief
		Draws the enemy object for rendering.
*/
/**************************************************************************/
void Enemy::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale;
	theScale = GetScale();

	// Changes direction of enemy based on state.
	if (state == ENEMY_STATE::STATE_MOVE_RIGHT || (state == ENEMY_STATE::STATE_CHASE_PLAYER &&
		previousState == ENEMY_STATE::STATE_MOVE_RIGHT))
		AEMtx33Scale(&mScale, theScale, theScale);
	else if (state == ENEMY_STATE::STATE_MOVE_LEFT || (state == ENEMY_STATE::STATE_CHASE_PLAYER &&
		previousState == ENEMY_STATE::STATE_MOVE_LEFT))
		AEMtx33Scale(&mScale, -theScale, theScale);
	else
		AEMtx33Scale(&mScale, theScale, theScale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mRot;
	AEMtx33Rot(&mRot, GetDirection());
	//AEMtx33Rot(&mRot, -half_pi);
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMRotation(mRot);
	SetMTrans(mTrans);
	return;
}

/***************************************************************************/
/*!
	\brief
		Changes the state of the enemy class by 4 different types.
		The move distance is randomized.
			- Chase Player
				When the enemy's detection area detects the player done at
				the collision manager, it will set it to this state.
				If the detection is lost, it will end it and go to the
				opposite direction state of previous state.
			- Move Left
				The state for the enemy to move left.
			- Move Right
				The state for the enemy to move right.
			- Death
				The state for the enemy to not function and "die" when
				the spike is touched.
*/
/**************************************************************************/
void Enemy::ChangeState()
{
	// Make the bounding box first.
	/*===================================*
			Chase Player State
	*====================================*/
	if (state == ENEMY_STATE::STATE_CHASE_PLAYER)
	{
		switch (innerState)
		{
		case ENEMY_INNER_STATE::INNER_STATE_ON_ENTER:
		{
			//idleCounter = IDLE_COUNT - 2.0f;
			idleCounter = IDLE_COUNT;
			// Make enemy move faster to simulate chase.
			AEVec2 vel = GetVelocity();
			if (previousState == ENEMY_STATE::STATE_MOVE_LEFT)
				vel.x = -ENEMY_CHASE_SPEED;
			else if (previousState == ENEMY_STATE::STATE_MOVE_RIGHT)
				vel.x = ENEMY_CHASE_SPEED;
			SetVelocity(vel);
			innerState = ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE;

			//load audio manager and play sound
			_am.playeffect("Resources/enemyfoundu.wav", _am.sound, _am.soundeffect, _am.bgm_paused, &_am.test);

			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE:
		{
			// Set detection box of the enemy.
			AABB detectBox;
			float range = horizontalDetectRange * TILE_WIDTH;
			if (previousState == ENEMY_STATE::STATE_MOVE_LEFT)
			{
				detectBox.min.x = -0.5f * range + GetPosition().x;
				detectBox.max.x = -0.5f * GetScale() + GetPosition().x;

				// Stops enemy if on ledge or wall while chasing.
				if ((_tm.GetTileTypeAt(GetPosition().x - (GetScale() * 0.5f),
					GetPosition().y) == TileType::TILE_WALL) ||
					(_tm.GetTileTypeAt(GetPosition().x - (GetScale()),
						GetPosition().y - (GetScale() * 0.5f) - (TILE_HEIGHT * 0.5f)) == TileType::TILE_EMPTY))
				{
					AEVec2 vel = GetVelocity();
					vel.x = 0.0f;
					SetVelocity(vel);
				}
			}
			else if (previousState == ENEMY_STATE::STATE_MOVE_RIGHT)
			{
				detectBox.min.x = 0.5f * GetScale() + GetPosition().x;
				detectBox.max.x = 0.5f * range + GetPosition().x;

				// Stops enemy if on ledge or wall while chasing.
				if ((_tm.GetTileTypeAt(GetPosition().x + (GetScale() * 0.5f),
					GetPosition().y) == TileType::TILE_WALL) ||
					(_tm.GetTileTypeAt(GetPosition().x + (GetScale()),
						GetPosition().y - (GetScale() * 0.5f) - (TILE_HEIGHT * 0.5f)) == TileType::TILE_EMPTY))
				{
					AEVec2 vel = GetVelocity();
					vel.x = 0.0f;
					SetVelocity(vel);
				}
			}
			detectBox.min.y = -0.5f * GetScale() + GetPosition().y;
			detectBox.max.y = 0.5f * GetScale() + GetPosition().y;
			SetDetectionBox(detectBox);
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_EXIT:
		{
			AEVec2 vel = GetVelocity();
			vel.x = 0.0f;
			SetVelocity(vel);
			if (idleCounter < 0)
			{

				idleCounter = IDLE_COUNT;
				// On exit, randomize which state left or right to go.
				float randNum = AERandFloat();
				if (randNum < 0.5f)
				{
					state = ENEMY_STATE::STATE_MOVE_LEFT;
					previousState = ENEMY_STATE::STATE_MOVE_RIGHT;


				}
				else if (randNum >= 0.5f)
				{
					state = ENEMY_STATE::STATE_MOVE_RIGHT;
					previousState = ENEMY_STATE::STATE_MOVE_LEFT;

				}

				innerState = ENEMY_INNER_STATE::INNER_STATE_ON_ENTER;
				break;
			}
			idleCounter -= g_dt;
			break;
		}
		}
	}
	/*===================================*
				Move Left State
	*====================================*/
	if (state == ENEMY_STATE::STATE_MOVE_LEFT)
	{
		switch (innerState)
		{
		case ENEMY_INNER_STATE::INNER_STATE_ON_ENTER:
		{
			// Setting the movement speed of the enemy
			AEVec2 vel = GetVelocity();
			vel.x = -ENEMY_SPEED;
			SetVelocity(vel);

			// Setting how far player move in this state.
			moveCounter = ENEMY_MOVE_MIN + (AERandFloat() * ENEMY_MOVE_MAX);
			innerState = ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE;
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE:
		{
			// Set detection box of the enemy.
			AABB detectBox;
			float range = horizontalDetectRange * TILE_WIDTH;
			detectBox.min.x = -0.5f * range + GetPosition().x;
			detectBox.max.x = -0.5f * GetScale() + GetPosition().x;
			detectBox.min.y = -0.5f * GetScale() + GetPosition().y;
			detectBox.max.y = 0.5f * GetScale() + GetPosition().y;
			SetDetectionBox(detectBox);

			// Decrease moveCounter
			moveCounter -= g_dt;
			// Change to exit state when at maximum boundary or when move counter runs out.
			if ((_tm.GetTileTypeAt(GetPosition().x - (GetScale() * 0.5f),
				GetPosition().y) == TileType::TILE_WALL) ||
				(_tm.GetTileTypeAt(GetPosition().x - (GetScale()),
					GetPosition().y - (GetScale() * 0.5f) - (TILE_HEIGHT * 0.5f)) == TileType::TILE_EMPTY) ||
				(moveCounter < 0))
			{
				AEVec2 vel = GetVelocity();
				vel.x = 0.0f;
				SetVelocity(vel);
				innerState = ENEMY_INNER_STATE::INNER_STATE_ON_EXIT;
			}
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_EXIT:
		{
			if (idleCounter < 0)
			{
				idleCounter = IDLE_COUNT;
				state = ENEMY_STATE::STATE_MOVE_RIGHT;
				innerState = ENEMY_INNER_STATE::INNER_STATE_ON_ENTER;
				previousState = ENEMY_STATE::STATE_MOVE_LEFT;
				break;
			}
			idleCounter -= g_dt;
			break;
		}
		}
	}
	/*===================================*
				Move Right State
	*====================================*/
	if (GetState() == ENEMY_STATE::STATE_MOVE_RIGHT)
	{
		switch (innerState)
		{
		case ENEMY_INNER_STATE::INNER_STATE_ON_ENTER:
		{
			// Setting the movement speed of the enemy
			AEVec2 vel = GetVelocity();
			vel.x = ENEMY_SPEED;
			SetVelocity(vel);

			// Setting how far player move in this state.
			moveCounter = ENEMY_MOVE_MIN + (AERandFloat() * ENEMY_MOVE_MAX);
			innerState = ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE;
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE:
		{
			// Set detection box of the enemy.
			AABB detectBox;
			float range = horizontalDetectRange * TILE_WIDTH;
			detectBox.min.x = 0.5f * GetScale() + GetPosition().x;
			detectBox.max.x = 0.5f * range + GetPosition().x;
			detectBox.min.y = -0.5f * GetScale() + GetPosition().y;
			detectBox.max.y = 0.5f * GetScale() + GetPosition().y;
			SetDetectionBox(detectBox);

			// Decrease moveCounter
			moveCounter -= g_dt;

			// Change to exit state when at maximum boundary or when move counter runs out.
			if ((_tm.GetTileTypeAt(GetPosition().x + (GetScale() * 0.5f),
				GetPosition().y) == TileType::TILE_WALL) ||
				(_tm.GetTileTypeAt(GetPosition().x + (GetScale()),
					GetPosition().y - (GetScale() * 0.5f) - (TILE_HEIGHT * 0.5f)) == TileType::TILE_EMPTY) ||
				(moveCounter < 0))
			{
				AEVec2 vel = GetVelocity();
				vel.x = 0.0f;
				SetVelocity(vel);
				innerState = ENEMY_INNER_STATE::INNER_STATE_ON_EXIT;
			}
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_EXIT:
		{
			if (idleCounter < 0)
			{
				idleCounter = IDLE_COUNT;
				state = ENEMY_STATE::STATE_MOVE_LEFT;
				innerState = ENEMY_INNER_STATE::INNER_STATE_ON_ENTER;
				previousState = ENEMY_STATE::STATE_MOVE_RIGHT;
				break;
			}
			idleCounter -= g_dt;
			break;
		}
		}
	}
	/*===================================*
				Death state
	*====================================*/
	if (GetState() == ENEMY_STATE::STATE_ENEMY_DEATH)
	{
		switch (innerState)
		{
		case ENEMY_INNER_STATE::INNER_STATE_ON_ENTER:
		{
			AEVec2 vel = GetVelocity();
			vel.x = 0.0f;
			SetVelocity(vel);
			innerState = ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE;
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_UPDATE:
		{
			SetInnerState(ENEMY_INNER_STATE::INNER_STATE_ON_EXIT);
			SetDirection(half_pi);
			break;
		}
		case ENEMY_INNER_STATE::INNER_STATE_ON_EXIT:
		{
			break;
		}
		}
	}
}