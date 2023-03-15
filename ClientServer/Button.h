/******************************************************************************
* \file          Button.h
* \brief         This file is the Declaration Game Object Button
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#pragma once

/******************************************************************************/
/*!
\file		Button.h
\brief		Header file for Button.cpp
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <vector>
#include "GameObject.h"
#include "Gate3.h"
#include <unordered_set>

class Button : public GameObject
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	// vector to store pointer address of Gates/Door
	std::vector<Gate3*> gate;
	bool IsActivated;
	float timer;

	std::unordered_set<GameObject*> collided_objs;
	

public:
	/*===================================*
				Constructors
	*====================================*/
	Button() = delete;
	Button(int, int);
	~Button();

	void ActivateGate();
	void DeActivateGate();
	void UpdateGate();
	bool GetIsActivated();
	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;

	inline void AddObject(GameObject* obj)
	{
		collided_objs.emplace(obj);
	}

	inline void RemoveObj(GameObject* obj)
	{
		collided_objs.erase(obj);
	}

	inline const std::unordered_set<GameObject*>& GetObjects() const
	{
		return collided_objs;
	}

};
