/******************************************************************************
* \file			EnemyStateList.h
* \brief		This file contains the enum for enemy AI states on how the
*				enemy will perform.
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef ENEMYSTATELIST_H
#define ENEMYSTATELIST_H

enum class ENEMY_STATE {
	STATE_TOP,
	STATE_MOVE_LEFT,
	STATE_MOVE_RIGHT,
	STATE_CHASE_PLAYER,
	STATE_ENEMY_DEATH
};

enum class ENEMY_INNER_STATE {
	INNER_STATE_ON_ENTER,
	INNER_STATE_ON_UPDATE,
	INNER_STATE_ON_EXIT
};

#endif