#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
/******************************************************************************
* \file			EntityManager.h
* \brief        This file contains the class declaration of the Entity Manager
*				class.
* \author       Kyle Vincent Velasco Gatchalian, 65% Code Contribution
*				Sebastian, ___% Code Contribution
*				Jian Jie, ___% Code Contribution
*				Felicia, ___% Code Contribution
*
*				The Entity Manager manages the creation of the game objects after
*				the map has been loaded and assigns what their IDs are. It also
*				calls upon the render manager to assign their textures.
*				The Entity Manager will handle object pooling if there are unused
*				objects in the world that can be reused. It will also handle
*				sorting of the list of objects in order to render them properly
*				later in the Rendering Manager. Objects are separated into layers
*				when rendering. The sorting algorithm used to sort through the objects
*				is the quick sort algorithm.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

class EntityManager
{
	/*===================================*
			Private - Data Members
	*====================================*/
	// Keeps track of the next id to give object.
	static int idCounter;
	// Map container to store Game Objects with unique ID key
	std::map<int, GameObject*> gameObjList;
	// Vector container to store Game Object order for rendering.
	std::vector<GameObject*> gameObjOrder;

public:

	//inline const std::map<int, GameObject*>& GetObjectList() { return gameObjList; }	// Might need

	/*===================================*
				Constructors
	*====================================*/
	EntityManager() = default;
	~EntityManager() = default;

	/*===================================*
				Member Functions
	*====================================*/
	void EntityManagerLoad();
	void EntityManagerInitialize();
	void EntityManagerUpdate();
	void EntityManagerUnload();

	// Makes the entity and returns the ID of that new entity.
	GameObject* CreateEntity(int type);

	std::map<int, GameObject*>& GetEntityList();
	std::vector<GameObject*>& GetEntityOrder();
	void SortEntityOrder();
	void ClearEntityList();

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static EntityManager& GetInstance()
	{
		static EntityManager _instance;
		return _instance;
	}
	//static EntityManager& GetInstance();

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	EntityManager(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&&) = delete;
};


#endif