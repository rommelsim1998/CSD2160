/******************************************************************************
* \file          TileManager.h
* \brief         This file declares the Tile class
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include "GameObject.h"
#include <vector>
#include <string>
#include "Tile.h"
	
class TileManager
{
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	// Keeps track of the next id to give object.
	int Map_Width = 0;
	int Map_Height = 0;


public:

	std::vector<Tile> MapTile; //MapTile 1D array vector to be created in 2d format
	std::vector<int> CollisionMap; //Coilisionmap 1D array vector to be created in 2d format

	std::vector<TileType> MapTileVal; //MapTile 1D array vector to be created in 2d format

	/*===================================*
				Constructors
	*====================================*/
	TileManager() = default;
	~TileManager() = default;

	/*===================================*
				Member Functions
	*====================================*/


	void TileManagerLoad(std::string const& filename);

	//void Init();

	void TileManagerFree();
	void TileManagerUnload();

	/*===================================*
					Accessors
	*====================================*/

	int Getwidth() const;
	int Getheight() const;
	std::vector<Tile>& GetTileList();

	AEVec2 GetTilePosAt(float x, float y) const;
	TileType GetTileTypeAt(float x, float y) const;
	int GetColMapValue(float x, float y) const;


	/*===================================*
					Mutators
	*====================================*/

	void Setwidth(int);
	void Setheight(int);

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static TileManager& GetInstance()
	{
		static TileManager _instance;
		return _instance;
	}
	//static EntityManager& GetInstance();

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	TileManager(const TileManager&) = delete;
	TileManager(TileManager&&) = delete;
	TileManager& operator=(const TileManager&) = delete;
	TileManager& operator=(TileManager&&) = delete;
};
#endif
