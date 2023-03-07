/******************************************************************************
* \file          Tile.cpp
* \brief         This file is the main file for Tiles
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "Tile.h"

int Tile::getTileID() const
{
	return tileID;
}

void Tile::setTileID(int NtileID)
{
	tileID = NtileID;
}

AEVec2 Tile::getPosition() const
{
	return position;
}

void Tile::setPosition(AEVec2 pos)
{
	position = pos;
}

TileType Tile::getTileType() const
{
	return type;
}

void Tile::setTileType(TileType Ntype)
{
	type = Ntype;
}

RenderData* Tile::getRenderData() {
	return &rendData;
}
