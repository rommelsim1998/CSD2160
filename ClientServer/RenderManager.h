#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
/******************************************************************************
* \file			RenderManager.h
* \brief        This file contains the class declaration of the Render Manager
*				class.
* \author       Kyle Vincent Velasco Gatchalian, 65% Code Contribution
*				Sebastian, ___% Code Contribution
*				Jian Jie, ___% Code Contribution
*				Felicia, ___% Code Contribution
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
#include "Constants.h"
#include <vector>
#include <map>

class RenderManager {
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	std::map<int, RenderData*> rendObjList;		// Map list for Game Objects to render
	//std::map<int, RenderData*> rendTileList;	// Map list for Tiles to render
	//std::vector<AEGfxTexture*> textureList;

public:
	/*===================================*
				Constructors
	*====================================*/
	RenderManager() = default;
	~RenderManager() = default;

	/*===================================*
				Member Functions
	*====================================*/
	void RenderManagerLoad();
	//void RenderManagerInitialize();
	void RenderManagerDraw();
	void RenderManagerUnload();

	void AssignTexture(int, int, RenderData*);	// Add RendData into List and assign textures
	void AssignImageBoxTexture(int, RenderData*);
	void RenderObjects();
	void RenderTiles();

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static RenderManager& GetInstance()
	{
		static RenderManager _instance;
		return _instance;
	}
	//static EntityManager& GetInstance();

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager& operator=(RenderManager&&) = delete;

};

#endif