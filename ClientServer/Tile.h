/******************************************************************************
* \file          Tile.h
* \brief         This file is the Declaration class Tile
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#ifndef TILE_H
#define TILE_H
#include "Tiletype.h"
#include "RenderData.h"

class Tile{
private:

	int tileID;
	TileType type;
	AEVec2 position;
	RenderData rendData;

public:

	int getTileID() const;

	void setTileID(int);

	AEVec2 getPosition() const;

	void setPosition(AEVec2);

	TileType getTileType() const;

	void setTileType(TileType);

	RenderData* getRenderData();

};
#endif 
