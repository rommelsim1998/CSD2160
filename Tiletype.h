/******************************************************************************
* \file          Tiletype.h
* \brief         This file declares the Tile Types class
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#ifndef TILETYPE_H
#define TILETYPE_H

#define TILE_HEIGHT 60.0f
#define TILE_WIDTH 60.0f

#define TILE_OFFSET 1.0f;

enum class TileType :char {
	TILE_EMPTY = 'x',	
	TILE_BOX = 'X',			
	TILE_BOX_YELLOW = '6',			
	TILE_BOX_BLUE = '7',		
	TILE_BOX_RED = '8',			
	TILE_BOX_GREEN = '9',			
	TILE_WALL = '*',		
	TILE_PLAYER = 'P',		
	TILE_ENEMY= 'E',		
	TILE_LADDER = '|',		
	TILE_PLATFORM = '_',	
	TILE_CAVE1 = 'q',		
	TILE_CAVE2 = 'w',		
	TILE_CAVE3 = 'e',		
	TILE_CAVE4 = 'r',
	TILE_CAVE5 = 't',
	TILE_CAVE6 = 'y',
	TILE_BUTTON = 'b',		
	TILE_BUTTON_GATE = 'B',	
	TILE_LEVER = 'L',		
	TILE_LEVER_GATE = 'l',	
	TILE_BUTTON1 = 'n',		
	TILE_BUTTON_GATE1 = 'N',	
	TILE_BUTTON2 = 'a',
	TILE_BUTTON_GATE2 = 'A',
	TILE_BUTTON3 = 'c',
	TILE_BUTTON_GATE3 = 'C',
	TILE_LEVER1 = 'm',		
	TILE_LEVER_GATE1 = 'M',	
	TILE_SPIKE = 'S',		
	TILE_ROCKS = 'R',		
	TILE_WALL_GREEN ='u',	
	TILE_WALL_RED = 'i',	
	TILE_WALL_YELLOW = 'o',	
	TILE_WALL_BLUE = 'p',	
	TILE_SIGN1 = '%',
	TILE_SIGN2 = '^',
	TILE_SIGN3 = '&',
	TILE_SIGN4 = ')',
	TILE_COLOROBJ_BLUE = '@',
	TILE_COLOROBJ_GREEN = '#',
	TILE_COLOROBJ_YELLOW = '$',
	TILE_COLOROBJ_WHITE = '!',
	TILE_IMAGEBOX1 = 'd',
	TILE_IMAGEBOX2 = 'f',
	TILE_IMAGEBOX3 = 'g',
	TILE_IMAGEBOX4 = 'h',
	TILE_IMAGEBOX5 = 'j',
	TILE_IMAGEBOX6 = 'k',
	TILE_COLOROBJ_RED = '(',
	TILE_CHECKPOINT = '!'

};
#endif