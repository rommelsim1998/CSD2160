/******************************************************************************
* \file          GameState_Level1.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/


/******************************************************************************
						SERVER
******************************************************************************/

//#include "Constants.h"

#include <WS2tcpip.h>
#include <winsock.h>
#include "GameState_Connect.h"
#include "Main.h"
#include <iostream>
#include "../NetworkingSystem/System.h"

const std::string ip = "192.168.50.119";
const short unsigned port = 54000;

// Create manager instances. (Make them static)
static UIManager& _um = UIManager::GetInstance();
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();
static PauseMenuManager& _pmm = PauseMenuManager::GetInstance();
static Server& ServerHandle = Server::getInstance();
static Client& ClientHandle = Client::getInstance();

 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/

AEGfxTexture* Tex_ServerMode;
AEGfxVertexList* pMesh = 0;
void GameStateLevel1Load(void)
{
	_tm.TileManagerLoad("Resources/Level 1.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();

	Tex_ServerMode = AEGfxTextureLoad("Resources/servermode.png");
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	pMesh = AEGfxMeshEnd();
}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/

static bool flag = false;
void GameStateLevel1Init(void)
{
	ServerHandle.Init(ip, port);

	_em.EntityManagerInitialize();  // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);

	int count = 0;
	while (1)
	{
		count = ServerHandle.GetPlayers();
		ServerHandle.SendFlagFor2Players(flag);
		if (count == 2)
		{
			flag = true;
			ServerHandle.SendFlagFor2Players(flag);
			return;
		}
	}
}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateLevel1Update(void)
{
	/*int x1, y1, x2, y2;
	ServerHandle.Read(x1, y1, x2, y2);
	std::cout << "[Server]: " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << "\n";
	ServerHandle.Send(x1, y1, x2, y2);*/
}
/**************************************************************************/
/*!
	The "Drawing" function of this state
	*/
	/**************************************************************************/

AEMtx33 Scale, trans, concat;
void GameStateLevel1Draw(void)
{
	AEMtx33Scale(&Scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight()); // not sure how it will turn out on full screen
	AEMtx33Trans(&trans, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(Tex_ServerMode, 0.0f, 0.0f);
	AEMtx33Concat(&concat, &Scale, &trans);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTransform(concat.m);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

/**************************************************************************/
/*!
	"Free" function of this state
	Destroy the Objects
	*/
	/**************************************************************************/
void GameStateLevel1Free(void)
{
	
	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateLevel1Unload(void)
{
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(Tex_ServerMode);
}
