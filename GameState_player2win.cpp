/******************************************************************************
* \file          GameState_Connect.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

//#include "Network.h"
#include "Main.h"
#include <iostream>


#pragma comment(lib, "Ws2_32.lib")


#include "../../External Libs/AlphaEngine_V3.08/include/AEEngine.h"
static bool isConnected = false;

//GameObject* go1;
AEMtx33 p2scale, p2Position, p2finish;
AEVec2 player2winpos{ 0.0f, 0.0f };
AEGfxVertexList* pMesh5 = 0;
AEGfxTexture* pTex5;
f32 p2y, p2x;

////************** CHANGE THIS TO SERVER IP *********************
//std::string ipAddr{ "192.168.189.56" }; 
//unsigned short port{ 5050 };

 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/

void GameStateplayer2winLoad(void)
{


	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	pMesh5 = AEGfxMeshEnd();
	//AE_ASSERT_MESG(pMesh3, "fail to create object!!");
}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/
void GameStateplayer2winInit(void)
{

	//_em.EntityManagerInitialize();  // Initializes all object's init function.
	//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	//AEGfxSetCamPosition(0, 0);


	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0.0f, 0.0f);
	pTex5 = AEGfxTextureLoad("Resources/player2win.png");
	//AE_ASSERT_MESG(pTex3, "fail!!");
	p2y = 0.0f;


}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateplayer2winUpdate(void)
{
	//if (!Connectionmanager::is2PlayersConnected)
	//	Connectionmanager::ConnectionStageUpdate();
	//else
	//	Connectionmanager::GameLoopStageUpdate();
	//Network::ConnectionStageUpdate();
	//Connectionmanager::ConnectionStageUpdate();


	/*
	//if its in pause state
	if (!isPaused)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate();     // Physics
		_cm.CollisionManagerUpdate();   // Collision (And Collision Response)
		_bm.BackgroundManagerUpdate();
		_um.UIManagerUpdate();

	}
	_am.AudioManagerUpdate();
	_pmm.PauseMenuManagerUpdate();

	*/
}
/**************************************************************************/
/*!
	The "Drawing" function of this state
	*/
	/**************************************************************************/
void GameStateplayer2winDraw(void)
{
	AEMtx33Scale(&p2scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight()); // not sure how it will turn out on full screen
	AEMtx33Trans(&p2Position, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pTex5, 0.0f, 0.0f);
	AEMtx33Concat(&p2finish, &p2scale, &p2Position);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTransform(p2finish.m);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	/*
	// Object's Draw functions called inside RenderManagerDraw();
	_bm.BackgroundManagerDraw();
	_rm.RenderManagerDraw();
	_um.UIManagerDraw();
	_pmm.PauseMenuManagerDraw();
	*/
}

/**************************************************************************/
/*!
	"Free" function of this state
	Destroy the Objects
	*/
	/**************************************************************************/
void GameStateplayer2winFree(void)
{

	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateplayer2winUnload(void)
{
	/*
	_rm.RenderManagerUnload();
	_em.EntityManagerUnload();
	_tm.TileManagerUnload();
	_bm.BackgroundManagerUnload();
	_um.UIManagerUnload();
	_pmm.PauseMenuManagerUnload();
	_am.AudioManagerUnload();
	*/

	AEGfxMeshFree(pMesh5);
	AEGfxTextureUnload(pTex5);
}
