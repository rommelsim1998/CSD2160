/******************************************************************************
* \file          TileManager.cpp
* \brief         This file defines Functions to read text from a file and save it in a vector for use
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "TileManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Tiletype.h"

// main logic to be here
// load
// init
// free

/***************************************************************************/
/*!
	Accessor functions 
*/
/**************************************************************************/
int TileManager::Getwidth() const
{
	return Map_Width;
}

int TileManager::Getheight() const
{
	return Map_Height;
}

std::vector<Tile>& TileManager::GetTileList()
{
	return MapTile;
}

AEVec2 TileManager::GetTilePosAt(float x, float y) const
{
	
	int pos = (Map_Width * (Map_Height - (static_cast<int>(ceil(y / TILE_HEIGHT)))) + (static_cast<int>(x / TILE_WIDTH)));

	return MapTile[pos].getPosition();
}

TileType TileManager::GetTileTypeAt(float x, float y) const
{
	

	int pos = (Map_Width * (Map_Height - (static_cast<int>(ceil(y / TILE_HEIGHT)))) + (static_cast<int>(x / TILE_WIDTH)));

	
	return MapTile[pos].getTileType();
}


int TileManager::GetColMapValue(float x, float y) const
{
	int val1 = static_cast<int>(y / TILE_HEIGHT);
	int val2 = static_cast<int>(x / TILE_WIDTH);
	//std::cout << "Val y: " << val2 << std::endl;
	//std::cout << "Map Width : " << Map_Width << std::endl;
	int pos = (Map_Width * (Map_Height - val1 - 1)) + (val2);
	return CollisionMap[pos];
}

void TileManager::Setwidth(int NMap_width)
{
	Map_Width = NMap_width;
}
void TileManager::Setheight(int NMap_height)
{
	Map_Height = NMap_height;
}

/*===================================*
			Tile Man Load
*====================================*/
void TileManager::TileManagerLoad(std::string const& filename)
{
	std::string buffer;
	std::ifstream fp;
	int pos1;


	fp.open(filename);
	// "./resources/map.txt"
	if (fp.is_open())
	{
		std::getline(fp, buffer);

		//MapTile;

		//count width and height
		Map_Width = static_cast<int>(buffer.find_last_of("xX*PEL_qwebBlR|Suiop6789nNmMaAcC%^&@#$!dfghjkrt(yz)}D"));
		Map_Width++;

		while (std::getline(fp, buffer))
		{
			Map_Height++;

		}
		Map_Height++;

		//std::cout << "Map Height is " << Map_Height << "\nMap Width is " << Map_Width << "\n";


			// calculation to get total map size
			int Map_Totalsize = Map_Height * Map_Width;


			MapTile.resize(Map_Totalsize);
			CollisionMap.resize(Map_Totalsize);

		//MapTile.reserve(Map_Totalsize);
		//Colisionmap.reserve(Map_Totalsize);

		fp.close();
	}
	else
	{
		std::cout << "File failed to open, please check if location is correct and map name exists\n" << "Resources/map.txt\n";
	}


	fp.open(filename);

	if (fp.is_open())
	{
		int counter = 0;
		for (int p = 0; p < Map_Height; ++p)
		{
			std::getline(fp, buffer);

			for (int i = 0; i < Map_Width; ++i)
			{
				/*===================================*
							Setting Map Tile
				*====================================*/
				pos1 = static_cast<int>(buffer.find_first_of("xX*PEL_qwebBlR|Suiop6789nNmMaAcC%^&@#$!dfghjkrt(yz)}D"));
				//MapTile[i] = buffer.substr(pos1, 1);

				MapTile[counter].setTileType(static_cast<TileType>(buffer[pos1]));
				MapTile[counter].setTileID(counter);

				/*
					Setting Position Data for each tile.
					Used in Entity Manager and Render Manager.
				*/
				AEVec2 pos;
				AEVec2Set(&pos, static_cast<float>(i), static_cast<float>(Map_Height - 1 - p));	// Must have -1
				//std::cout << "NEW TILE POS : " << pos.x << " and " << pos.y << std::endl;
				MapTile[counter].setPosition(pos);
				MapTileVal.push_back(static_cast<TileType>(buffer[pos1]));
				buffer.erase(pos1, 1);

				/*===================================*
						Setting Collision Map
				*====================================*/
				if (MapTile[counter].getTileType() == TileType::TILE_WALL)
				{
					CollisionMap[counter] = 1;
				}
				else
				{
					CollisionMap[counter] = 0;
				}

				++counter;
			}
		}

		//std::cout << "====MAP TILE====\n";
		counter = 0;
		for (int p = 0; p < Map_Height; ++p)
		{
			for (int i = 0; i < Map_Width; ++i)
			{
				//std::cout << static_cast<char>(MapTile[counter].getTileType());
				counter++;
			}

			//std::cout << "\n";
		}

		//std::cout << "====MAP COLLISION====\n";
		counter = 0;
		for (int p = 0; p < Map_Height; ++p)
		{
			for (int i = 0; i < Map_Width; ++i)
			{
				//std::cout << CollisionMap[counter];
				counter++;
			}

			//std::cout << "\n";
		}

		fp.close();
		/*std::cout << "Size Map START : " << MapTile.size() << std::endl;
		std::cout << "Size ColMap START : " << CollisionMap.size() << std::endl;
		std::cout << "Size MapVal START : " << MapTileVal.size() << std::endl;*/
	}
	else
	{
		//std::cout << "unable to open file";
	}
}

/*===================================*
			Tile Man Free
*====================================*/
void TileManager::TileManagerFree()
{
	// Memory already deallocated.

	//// Free binary map
	//for (int i = 0; i < Map_Height; i++)
	//{
	//	delete CollisionMap;
	//}

	//// Free map
	//for (int i = 0; i < Map_Height; i++)
	//{
	//	delete[] MapData[i];
	//}
	//delete[] MapData;
	/*std::cout << "Size Map Before : " << MapTile.size() << std::endl;
	std::cout << "Size ColMap Before : " << CollisionMap.size() << std::endl;
	std::cout << "Size MapVal Before : " << MapTileVal.size() << std::endl;
	Map_Width = 0;
	Map_Height = 0;
	CollisionMap.clear();
	MapTile.clear();
	MapTileVal.clear();
	std::cout << "Size Map After : " << MapTile.size() << std::endl;
	std::cout << "Size ColMap After : " << CollisionMap.size() << std::endl;
	std::cout << "Size MapVal After : " << MapTileVal.size() << std::endl;*/
}

void TileManager::TileManagerUnload()
{
	Map_Width = 0;
	Map_Height = 0;
	CollisionMap.clear();
	MapTile.clear();
	MapTileVal.clear();
}



