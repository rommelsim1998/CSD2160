/******************************************************************************
* \file			EntityManager.cpp
* \brief        This file contains the class definition of the Entity Manager
*				class.
* \author       Kyle Vincent Velasco Gatchalian, 30.4%% Code Contribution
*				Sebastian, 19.73%% Code Contribution
*				Jian Jie, 22.67%% Code Contribution
*				Felicia, 27.2%% Code Contribution
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
#include "EntityManager.h"

const unsigned int MAX_ENTITY_INSTANCE = 500;

static TileManager& _tm = TileManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();

int EntityManager::idCounter;

// Declare helper functions.
void QuickSort(std::vector<GameObject*>& objs, size_t low, size_t high);
size_t Partition(std::vector<GameObject*>& objs, size_t low, size_t high);

/*===================================*
			Entity Man Load
*====================================*/
/***************************************************************************/
/*!
	\brief
		The Load function of the manager which initializes the game
		objects read from the Tile Manager's tile information.
*/
/**************************************************************************/
void EntityManager::EntityManagerLoad()
{
	idCounter = 0;
	gameObjOrder.reserve(MAX_ENTITY_INSTANCE);
	// Gets Map Information and create their objects. Setting pos too.
	std::vector<Tile>& list = _tm.GetTileList();
	for (Tile const& tile : list)
	{
		GameObject* obj;
		AEVec2 pos;
		if (tile.getTileType() == TileType::TILE_PLAYER)
		{
			obj = CreateEntity(TYPE_PLAYER);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_PLAYER2)
		{
			obj = CreateEntity(TYPE_PLAYER2);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_ENEMY)
		{
			obj = CreateEntity(TYPE_ENEMY);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BOX)
		{
			obj = CreateEntity(TYPE_BOX);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE1)
		{
			obj = CreateEntity(TYPE_CAVE1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE2)
		{
			obj = CreateEntity(TYPE_CAVE2);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE3)
		{
			obj = CreateEntity(TYPE_CAVE3);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE4)
		{
			obj = CreateEntity(TYPE_CAVE4);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE5)
		{
			obj = CreateEntity(TYPE_CAVE5);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE6)
		{
			obj = CreateEntity(TYPE_CAVE6);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_CAVE7)
		{
			obj = CreateEntity(TYPE_CAVE7);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_WALL_BLUE)
		{
			obj = CreateEntity(TYPE_WALL_BLUE);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_WALL_GREEN)
		{
			obj = CreateEntity(TYPE_WALL_GREEN);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_WALL_RED)
		{
			obj = CreateEntity(TYPE_WALL_RED);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_WALL_YELLOW)
		{
			obj = CreateEntity(TYPE_WALL_YELLOW);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_SPIKE)
		{
			obj = CreateEntity(TYPE_SPIKE);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BOX_BLUE)
		{
			obj = CreateEntity(TYPE_BOX);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_BLUE);
		}
		else if (tile.getTileType() == TileType::TILE_BOX_YELLOW)
		{
			obj = CreateEntity(TYPE_BOX);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_YELLOW);
		}
		else if (tile.getTileType() == TileType::TILE_BOX_GREEN)
		{
			obj = CreateEntity(TYPE_BOX);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_GREEN);
		}
		else if (tile.getTileType() == TileType::TILE_BOX_RED)
		{
			obj = CreateEntity(TYPE_BOX);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_RED);
		}
		else if (tile.getTileType() == TileType::TILE_BUTTON)
		{
			obj = CreateEntity(TYPE_BUTTON);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_LEVER)
		{
			obj = CreateEntity(TYPE_LEVER);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_LEVER_GATE)
		{
			obj = CreateEntity(TYPE_LEVER_GATE);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BUTTON_GATE)
		{
			obj = CreateEntity(TYPE_BUTTON_GATE);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BUTTON1)
		{
			obj = CreateEntity(TYPE_BUTTON1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);

		}
		else if (tile.getTileType() == TileType::TILE_BUTTON_GATE1)
		{
			obj = CreateEntity(TYPE_BUTTON_GATE1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BUTTON2)
		{
			obj = CreateEntity(TYPE_BUTTON2);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);

		}
		else if (tile.getTileType() == TileType::TILE_BUTTON_GATE2)
		{
			obj = CreateEntity(TYPE_BUTTON_GATE2);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_BUTTON3)
		{
			obj = CreateEntity(TYPE_BUTTON3);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);

		}
		else if (tile.getTileType() == TileType::TILE_BUTTON_GATE3)
		{
			obj = CreateEntity(TYPE_BUTTON_GATE3);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}

		else if (tile.getTileType() == TileType::TILE_LEVER1)
		{
			obj = CreateEntity(TYPE_LEVER1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);

		}

		else if (tile.getTileType() == TileType::TILE_LEVER_GATE1)
		{
			obj = CreateEntity(TYPE_LEVER_GATE1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);

		}
		else if (tile.getTileType() == TileType::TILE_COLOROBJ_BLUE)
		{
			obj = CreateEntity(TYPE_COLOROBJ);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_BLUE);
		}
		else if (tile.getTileType() == TileType::TILE_COLOROBJ_RED)
		{
			obj = CreateEntity(TYPE_COLOROBJ);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_RED);
		}
		else if (tile.getTileType() == TileType::TILE_COLOROBJ_GREEN)
		{
			obj = CreateEntity(TYPE_COLOROBJ);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_GREEN);
		}
		else if (tile.getTileType() == TileType::TILE_COLOROBJ_YELLOW)
		{
			obj = CreateEntity(TYPE_COLOROBJ);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
			obj->SetColor(Color::COLOR_YELLOW);
		}
		else if (tile.getTileType() == TileType::TILE_CHECKPOINT)
		{
			obj = CreateEntity(TYPE_CHCKPT);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX1)
		{
			obj = CreateEntity(TYPE_IMAGEBOX1);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX2)
		{
			obj = CreateEntity(TYPE_IMAGEBOX2);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX3)
		{
			obj = CreateEntity(TYPE_IMAGEBOX3);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX4)
		{
			obj = CreateEntity(TYPE_IMAGEBOX4);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX5)
		{
			obj = CreateEntity(TYPE_IMAGEBOX5);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else if (tile.getTileType() == TileType::TILE_IMAGEBOX6)
		{
			obj = CreateEntity(TYPE_IMAGEBOX6);
			pos = tile.getPosition();
			pos.x = (pos.x + 0.5f) * TILE_WIDTH;
			pos.y = (pos.y + 0.5f) * TILE_HEIGHT;
			obj->SetPosition(pos);
			obj->SetRestartPos(pos);
		}
		else
			continue;

		/*
			Create new entities here. (Based on map data)
			You can add a new "else if" for another new object type if there is any.
			Add your own, don't worry!

			It will take information from the map and based on it will create the desired object.

			IMPORTANT:
				Remember to also add the new codes for your object in CreateEntity()!

			Note:
				The position things are a bit repetitive, will change next time if have time.
		*/
	}
}

/*===================================*
		Entity Man Initialize
*====================================*/
/***************************************************************************/
/*!
	\brief
		The initialize function of the manager that handles the initializing
		of all game objects in the game.
*/
/**************************************************************************/
void EntityManager::EntityManagerInitialize()
{
	// After creating objects based on map. Initialize their initializers.
	for (auto it = gameObjList.begin(); it != gameObjList.end(); it++)
	{
		it->second->GameObjectInitialize();
	}

}
/*===================================*
			Entity Man Update
*====================================*/
/***************************************************************************/
/*!
	\brief
		The update function of the Entity Manager which handles updating
		the update functions of all game objects.
*/
/**************************************************************************/
void EntityManager::EntityManagerUpdate()
{
	// Calls all entities' update function.
	for (auto it = gameObjList.begin(); it != gameObjList.end(); it++)
	{
		it->second->GameObjectUpdate();
	}
}

/*===================================*
			Entity Man Unload
*====================================*/
/***************************************************************************/
/*!
	\brief
		The unload function of the Entity Manager which clears the memory
		assigned to the Entity List.
*/
/**************************************************************************/
void EntityManager::EntityManagerUnload()
{
	// Frees the Entity addresses stored.
	ClearEntityList();
}

/*===================================*
			Create Entity
*====================================*/
/***************************************************************************/
/*!
	\brief
		The function to create entity separate from the load function. This
		is so that entities can be made during run time. It will also call
		the render manager to assign textures.

	\param
		The type of the new object to be created.
*/
/**************************************************************************/
GameObject* EntityManager::CreateEntity(int type)
{
	/*
		Creates new entities here too. (Not from Map Data, but from gameplay. E.g Bullets)

		This function can be called outside of the Init function of the EntityManager
		for things like making bullets or anything not loaded from map.
	*/
	GameObject* gameObject = nullptr;

	// Object Pooling.
	for (auto it = gameObjList.begin(); it != gameObjList.end(); it++)
	{
		if (it->second->GetType() != type)
			continue;
		if (it->second->GetFlag())				// Test this if ! or not.
			continue;
		it->second->ResetGameObject(true);
		return it->second;
	}
	switch (type)
	{
	case TYPE_PLAYER:
	{
		Player* player{ new Player(++idCounter) };
		gameObjList.emplace(idCounter, player);
		gameObject = player;
		gameObject->SetRenderOrder(2);
		break;
	}
	case TYPE_PLAYER2:
	{
		Player2* player2{ new Player2(++idCounter) };
		gameObjList.emplace(idCounter, player2);
		gameObject = player2;
		gameObject->SetRenderOrder(2);
		break;
	}
	case TYPE_ENEMY:
	{
		Enemy* enemy{ new Enemy(++idCounter) };
		gameObjList.emplace(enemy->GetID(), enemy);
		gameObject = enemy;
		gameObject->SetRenderOrder(2);
		break;
	}
	case TYPE_BOX:
	{
		Box* box{ new Box(++idCounter) };
		gameObjList.emplace(box->GetID(), box);
		gameObject = box;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_CAVE1:
	{
		Cave1* cave1{ new Cave1(++idCounter) };
		gameObjList.emplace(cave1->GetID(), cave1);
		gameObject = cave1;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE2:
	{
		Cave2* cave2{ new Cave2(++idCounter) };
		gameObjList.emplace(cave2->GetID(), cave2);
		gameObject = cave2;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE3:
	{
		Cave3* cave3{ new Cave3(++idCounter) };
		gameObjList.emplace(cave3->GetID(), cave3);
		gameObject = cave3;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE4:
	{
		Cave4* cave4{ new Cave4(++idCounter) };
		gameObjList.emplace(cave4->GetID(), cave4);
		gameObject = cave4;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE5:
	{
		Cave5* cave5{ new Cave5(++idCounter) };
		gameObjList.emplace(cave5->GetID(), cave5);
		gameObject = cave5;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE6:
	{
		Cave6* cave6{ new Cave6(++idCounter) };
		gameObjList.emplace(cave6->GetID(), cave6);
		gameObject = cave6;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_CAVE7:
	{
		Cave7* cave7{ new Cave7(++idCounter) };
		gameObjList.emplace(cave7->GetID(), cave7);
		gameObject = cave7;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_WALL_GREEN:
	{
		Wall_Green* wall_green{ new Wall_Green(++idCounter) };
		gameObjList.emplace(wall_green->GetID(), wall_green);
		gameObject = wall_green;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_WALL_RED:
	{
		Wall_Red* wall_red{ new Wall_Red(++idCounter) };
		gameObjList.emplace(wall_red->GetID(), wall_red);
		gameObject = wall_red;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_WALL_YELLOW:
	{
		Wall_Yellow* wall_yellow{ new Wall_Yellow(++idCounter) };
		gameObjList.emplace(wall_yellow->GetID(), wall_yellow);
		gameObject = wall_yellow;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_WALL_BLUE:
	{
		Wall_Blue* Wall_blue{ new Wall_Blue(++idCounter) };
		gameObjList.emplace(Wall_blue->GetID(), Wall_blue);
		gameObject = Wall_blue;
		gameObject->SetRenderOrder(4);
		break;
	}

	case TYPE_SPIKE:
	{
		Spikes* spike{ new Spikes(++idCounter) };
		gameObjList.emplace(spike->GetID(), spike);
		gameObject = spike;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_LEVER:
	{
		Lever* lever{ new Lever(++idCounter) };
		gameObjList.emplace(lever->GetID(), lever);
		gameObject = lever;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_LEVER_GATE:
	{
		Gate* gate{ new Gate(++idCounter) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_LEVER1:
	{
		Lever1* lever{ new Lever1(++idCounter) };
		gameObjList.emplace(lever->GetID(), lever);
		gameObject = lever;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_LEVER_GATE1:
	{
		Gate2* gate{ new Gate2(++idCounter) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_COLOROBJ:
	{
		ColorObj* colorobj{ new ColorObj(++idCounter) };
		gameObjList.emplace(colorobj->GetID(), colorobj);
		gameObject = colorobj;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_BUTTON:
	{
		Button* button{ new Button(++idCounter, TYPE_BUTTON) };
		gameObjList.emplace(button->GetID(), button);
		gameObject = button;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_BUTTON1:
	{
		Button* button{ new Button(++idCounter, TYPE_BUTTON1) };
		gameObjList.emplace(button->GetID(), button);
		gameObject = button;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_BUTTON2:
	{
		Button* button{ new Button(++idCounter, TYPE_BUTTON2) };
		gameObjList.emplace(button->GetID(), button);
		gameObject = button;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_BUTTON3:
	{
		Button* button{ new Button(++idCounter, TYPE_BUTTON3) };
		gameObjList.emplace(button->GetID(), button);
		gameObject = button;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_BUTTON_GATE:
	{
		Gate3* gate{ new Gate3(++idCounter, TYPE_BUTTON_GATE) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_BUTTON_GATE1:
	{
		Gate3* gate{ new Gate3(++idCounter, TYPE_BUTTON_GATE1) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_BUTTON_GATE2:
	{
		Gate3* gate{ new Gate3(++idCounter, TYPE_BUTTON_GATE2) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_BUTTON_GATE3:
	{
		Gate3* gate{ new Gate3(++idCounter, TYPE_BUTTON_GATE3) };
		gameObjList.emplace(gate->GetID(), gate);
		gameObject = gate;
		gameObject->SetRenderOrder(3);
		break;
	}
	case TYPE_CHCKPT:
	{
		Checkpoint* checkpoint{ new Checkpoint(++idCounter) };
		gameObjList.emplace(checkpoint->GetID(), checkpoint);
		gameObject = checkpoint;
		gameObject->SetRenderOrder(1);
		break;
	}
	case TYPE_IMAGEBOX1:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX1) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_IMAGEBOX2:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX2) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_IMAGEBOX3:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX3) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_IMAGEBOX4:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX4) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_IMAGEBOX5:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX5) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	case TYPE_IMAGEBOX6:
	{
		ImageBox* imageBox{ new ImageBox(++idCounter, TYPE_IMAGEBOX6) };
		gameObjList.emplace(imageBox->GetID(), imageBox);
		gameObject = imageBox;
		gameObject->SetRenderOrder(4);
		break;
	}
	default:
		return nullptr;
	}
	_rm.AssignTexture(gameObject->GetID(), gameObject->GetType(), gameObject->GetRenderData());
	gameObjOrder.push_back(gameObject);	// Store into vector of game object rendering order.
	SortEntityOrder();		// Re-sort the render order after new object is created.
	return gameObject;
	
}

/***************************************************************************/
/*!
	\brief
		Returns the list of entities.
*/
/**************************************************************************/
std::map<int, GameObject*>& EntityManager::GetEntityList()
{
	return gameObjList;
}

/***************************************************************************/
/*!
	\brief
		Returns the entity list that is organized in rendering order.
*/
/**************************************************************************/
std::vector<GameObject*>& EntityManager::GetEntityOrder()
{
	return gameObjOrder;
}

/***************************************************************************/
/*!
	\brief
		The function to quick sort the entities inside of the game render order
		list.
*/
/**************************************************************************/
void EntityManager::SortEntityOrder()
{
	/*
	algorithm quicksort(A, lo, hi) is
	if lo < hi then
		p := partition(A, lo, hi)
		quicksort(A, lo, p - 1)
		quicksort(A, p + 1, hi)

	algorithm partition(A, lo, hi) is
		pivot := A[hi]
		i := lo
		for j := lo to hi do
			if A[j] < pivot then
				swap A[i] with A[j]
				i := i + 1
		swap A[i] with A[hi]
		return i
	*/
	QuickSort(gameObjOrder, 0, gameObjOrder.size());
}

/***************************************************************************/
/*!
	\brief
		The actual QuickSort recursive function to sort the objects.
*/
/**************************************************************************/
void QuickSort(std::vector<GameObject*>& objs, size_t low, size_t high)
{
	if (low < high)
	{
		size_t objPivot = Partition(objs, low, high);
		QuickSort(objs, low, objPivot);
		QuickSort(objs, objPivot + 1, high);
	}
}

size_t Partition(std::vector<GameObject*>& objs, size_t low, size_t high)
{
	GameObject* pivot = objs[low];
	size_t leftWall = low;

	for (size_t i = low; i < high; ++i)
	{
		if (objs[i]->GetRenderOrder() < pivot->GetRenderOrder())
		{
			GameObject* tmp = objs[i];
			objs[i] = objs[leftWall];
			objs[leftWall] = tmp;
			leftWall += 1;
		}
		/*GameObject* tmp2 = pivot;
		pivot = objs[leftWall];
		objs[leftWall] = pivot;*/
	}
	return leftWall;
}

/*===================================*
		Clear Entity List
*====================================*/
void EntityManager::ClearEntityList() {
	// clear list.
	for (auto it = gameObjList.begin(); it != gameObjList.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	gameObjList.clear();
	gameObjOrder.clear();
}
