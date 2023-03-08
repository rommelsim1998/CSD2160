/******************************************************************************
* \file			RenderManager.cpp
* \brief        This file contains the class definition of the Render Manager
*				class.
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The Render Manager handles the rendering for tiles and objects
*				and also setting of what textures are to be used for the objects.
*				It will also render certain objects with indicated colours
*				based on their colours.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "RenderManager.h"
#include <map>
#include <iostream>
#include <vector>

static TileManager& _tm = TileManager::GetInstance();
static EntityManager& _em = EntityManager::GetInstance();

/*===================================*
			Render Man Load
*====================================*/
/***************************************************************************/
/*!
	\brief
		The Load function of Render Manager which assigns textures to tiles.
*/
/**************************************************************************/
void RenderManager::RenderManagerLoad()
{
	//Initialize Tile Render Textures.
	std::vector<Tile>& tileList = _tm.GetTileList();
	for (Tile& tile : tileList)
	{
		if (tile.getTileType() == TileType::TILE_WALL)
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/wall.png"));
		else if (tile.getTileType() == TileType::TILE_LADDER)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/ladder.png"));
		}
		else if (tile.getTileType() == TileType::TILE_PLATFORM)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/platform.png"));
		}
		else if (tile.getTileType() == TileType::TILE_SIGN1)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/sign1.png"));
		}

		else if (tile.getTileType() == TileType::TILE_SIGN2)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/sign2.png"));
		}

		else if (tile.getTileType() == TileType::TILE_SIGN3)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/sign3.png"));
		}
		else if (tile.getTileType() == TileType::TILE_SIGN4)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/sign4.png"));
		}
		else if (tile.getTileType() == TileType::TILE_SIGN5)
		{
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/sign5.png"));
		}
		else
			tile.getRenderData()->SetRendTexture(AEGfxTextureLoad("Resources/empty.png"));


		/*
			Any new TILE you made and want to load textures for them. Load here!
		*/

	}
}

/*===================================*
		Render Man Draw
*====================================*/
/***************************************************************************/
/*!
	\brief
		The Draw function of Render Manager which draws both tiles
		and game objects. It will call the draw function of all game objects
		first to process their draw functions.
*/
/**************************************************************************/
void RenderManager::RenderManagerDraw()
{
	// Update all trans matrices of objects.
	std::map<int, GameObject*>& list = _em.GetEntityList();
	for (auto& obj : list)
	{
		obj.second->GameObjectDraw();
	}

	// Then actually renders them with below functions.
	RenderTiles();
	RenderObjects();
}

/*===================================*
			Render Objects
*====================================*/
/***************************************************************************/
/*!
	\brief
		The function render objects.
*/
/**************************************************************************/
void RenderManager::RenderObjects()
{
	// Render all Game Objects.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEMtx33 mtx;
	// Iterate through all objects and set their transforms.
	std::vector<GameObject*> objOrderList = _em.GetEntityOrder();
	for (int i = 0; i < objOrderList.size(); ++i)
	{
		GameObject* obj = objOrderList[i];
		AEMtx33 trans = obj->GetMTrans();
		AEMtx33 scale = obj->GetMScale();
		AEMtx33 rotation = obj->GetMRotation();
		// Flag 1 means it is activated. 0 is deactivated and will not render it.
		if (obj->GetFlag() == 0)
			continue;
		if (obj->GetRenderData()->GetRendTexture() == nullptr)	// If no texture don't render.
			continue;

		// Concatenate the 3 matrix in the correct order in the object instance's "transform" matrix
		AEMtx33Concat(&mtx, &rotation, &scale);
		AEMtx33Concat(&mtx, &trans, &mtx);

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		/*===================================*
				Object Color Render
		*====================================*/
		/*
			Will Render the color of the object based on
			their "ColorList.h" enum value.
		*/
		if (obj->GetType() != TYPE_PLAYER && obj->GetColor() != Color::COLOR_BLACK
			&& obj->GetType() != TYPE_WALL_BLUE && obj->GetType() != TYPE_WALL_RED && obj->GetType() != TYPE_WALL_YELLOW
			&& obj->GetType() != TYPE_WALL_GREEN)
		{
			switch (obj->GetColor())
			{
			case Color::COLOR_RED:
			{
				AEGfxSetTintColor(1.0f, 0.310f, 0.310f, 1.0f);
				break;
			}
			case Color::COLOR_YELLOW:
			{
				AEGfxSetTintColor(1.0f, 1.0f, 0.5f, 1.0f);
				break;
			}
			case Color::COLOR_BLUE:
			{
				AEGfxSetTintColor(0.369f, 0.612f, 1.0f, 1.0f);
				break;
			}
			case Color::COLOR_GREEN:
			{
				AEGfxSetTintColor(0.310f, 1.0f, 0.459f, 1.0f);
				break;
			}

			}
		}
		else
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		AEGfxSetTransparency(1.0f);
		AEGfxTextureSet(obj->GetRenderData()->GetRendTexture(), 0, 0);
		AEGfxSetTransform(mtx.m);
		AEGfxMeshDraw(obj->GetRenderData()->GetRendMesh(), AE_GFX_MDM_TRIANGLES);
	}
}

/*===================================*
		Render Tile (Background)
*====================================*/
/***************************************************************************/
/*!
	\brief
		The function to render tiles.
*/
/**************************************************************************/
void RenderManager::RenderTiles()
{
	/*
		Things like ladder are background tiles. Give them a value and texture.
	*/
	// Render all Tiles.
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);

	AEMtx33 mtx;
	std::vector<Tile>& tileList = _tm.GetTileList();
	for (Tile& tile : tileList)
	{
		// Actually transforms based on data from each tile.
		AEMtx33 trans, scale;
		AEVec2 pos = tile.getPosition();
		AEMtx33Scale(&scale, TILE_WIDTH, TILE_HEIGHT);
		AEMtx33Trans(&trans, (pos.x + 0.5f) * TILE_WIDTH, (pos.y + 0.5f) * TILE_HEIGHT);
		AEMtx33Concat(&mtx, &trans, &scale);


		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (tile.getTileType() == TileType::TILE_EMPTY)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetTintColor(0.0f, 0.0f, 0.0f, 0.0f);
			AEGfxSetTransparency(0.0f);
			AEGfxTextureSet(tile.getRenderData()->GetRendTexture(), 0, 0);
			AEGfxSetTransform(mtx.m);
			AEGfxMeshDraw(tile.getRenderData()->GetRendMesh(), AE_GFX_MDM_TRIANGLES);
		}
		else
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			//AEGfxSetRenderMode(AE_GFX_RM_COLOR);

			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetTransparency(1.0f);
			//AEGfxTextureSet(it->second->GetRendTexture(), obj->GetPosition().x, obj->GetPosition().y);
			AEGfxTextureSet(tile.getRenderData()->GetRendTexture(), 0, 0);
			//AEGfxTextureSet(NULL, 0.0f, 0.0f);
			AEGfxSetTransform(mtx.m);
			AEGfxMeshDraw(tile.getRenderData()->GetRendMesh(), AE_GFX_MDM_TRIANGLES);
		}
	}
}

/*===================================*
			Assign Texture
*====================================*/
/***************************************************************************/
/*!
	\brief
		This function assigns texture to a given id of an object and store
		it's render data into the manager's list of rendering data.
*/
/**************************************************************************/
void RenderManager::AssignTexture(int id, int type, RenderData* rendData)
{
	// Now made it a separate function so can create objects
	// easier even after loading level.
	rendObjList.emplace(id, rendData);
	// This function stores the already made RenderData from object into list.
	if (type == TYPE_PLAYER)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/Idle Player.png"));
	}
	else if (type == TYPE_ENEMY)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/Enemy.png"));
	}
	else if (type == TYPE_BOX)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/Box.png"));
	}
	else if (type == TYPE_CAVE1)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE2)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE3)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE4)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE5)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE6)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_CAVE7)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/cave 1.png"));
	}
	else if (type == TYPE_WALL_BLUE)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/BlueWall.png"));
	}
	else if (type == TYPE_WALL_GREEN)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/GreenWall.png"));
	}
	else if (type == TYPE_WALL_YELLOW)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/YellowWall.png"));
	}
	else if (type == TYPE_WALL_RED)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/RedWall.png"));
	}
	else if (type == TYPE_SPIKE)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/spike.png"));
	}
	else if (type == TYPE_LEVER)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/lever2.png"));
	}
	else if (type == TYPE_LEVER_GATE)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_BUTTON)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/button.png"));
	}
	else if (type == TYPE_BUTTON_GATE)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_LEVER1)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/lever2.png"));
	}
	else if (type == TYPE_LEVER_GATE1)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_BUTTON1)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/button.png"));
	}
	else if (type == TYPE_BUTTON_GATE1)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_BUTTON2)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/button.png"));
	}
	else if (type == TYPE_BUTTON_GATE2)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_BUTTON3)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/button.png"));
	}
	else if (type == TYPE_BUTTON_GATE3)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/gate.png"));
	}
	else if (type == TYPE_COLOROBJ)
	{
		rendData->SetRendTexture(AEGfxTextureLoad("Resources/coloractive.png"));
	}
	else if (type == TYPE_CHCKPT)
	{
	rendData->SetRendTexture(AEGfxTextureLoad("Resources/checkpoint.png"));
	}
	AssignImageBoxTexture(type, rendData);
}

/*===================================*
		Assign ImageBox Textures
*====================================*/
/***************************************************************************/
/*!
	\brief
		This function assigns Image box textures to the render data of
		the object if the object is indeed of an ImageBox type.
		This is specialised for indicating what texture to use as different
		levels have different textures to be used.
*/
/**************************************************************************/
void RenderManager::AssignImageBoxTexture(int type, RenderData* rendData)
{
	// For developer freedom to assign whatever texture they want for Image box object

	// Hardcodedly assign proper help textures here.
	if (current == GS_MAINMENU)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog1.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog2.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LS)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog3.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog4.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL1)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog5.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog6.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog7.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL2)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog8.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog9.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL3)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog10.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL4)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog12.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL5)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog15.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog16.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL6)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog11.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog14.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL7)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/KingDialog.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_LEVEL8)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/white.png"));
			break;
		}
	}
	else if (current == GS_END)
	{
		switch (type)
		{
		case TYPE_IMAGEBOX1:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/EndDialog1.png"));
			break;
		case TYPE_IMAGEBOX2:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/EndDialog2.png"));
			break;
		case TYPE_IMAGEBOX3:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/EndDialog3.png"));
			break;
		case TYPE_IMAGEBOX4:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/EndDialog4.png"));
			break;
		case TYPE_IMAGEBOX5:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/EndDialog5.png"));
			break;
		case TYPE_IMAGEBOX6:
			rendData->SetRendTexture(AEGfxTextureLoad("Resources/TrixDialog13.png"));
			break;
		}
	}
}

/*===================================*
			Render Man Unload
*====================================*/
/***************************************************************************/
/*!
	\brief
		The unload function of the render manager which cleans the rendering
		data, both mesh and textures of the object.
*/
/**************************************************************************/
void RenderManager::RenderManagerUnload()
{
	// Will free all OBJECTS and TILES mesh and textures
	for (auto it = rendObjList.begin(); it != rendObjList.end(); it++)
	{
		AEGfxMeshFree(it->second->GetRendMesh());
		if (it->second->GetRendTexture() != nullptr)
		{
			AEGfxTextureUnload(it->second->GetRendTexture());
		}
		it->second = nullptr;
	}
	rendObjList.clear();
	std::vector<Tile>& tileList = _tm.GetTileList();
	for (Tile& tile : tileList)
	{
		AEGfxMeshFree(tile.getRenderData()->GetRendMesh());
		if (tile.getRenderData()->GetRendTexture() != nullptr)
			AEGfxTextureUnload(tile.getRenderData()->GetRendTexture());
	}

}