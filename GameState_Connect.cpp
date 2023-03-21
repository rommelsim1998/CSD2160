/******************************************************************************
* \file          GameState_Connect.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include <WS2tcpip.h>
#include <winsock.h>
#include "GameState_Connect.h"
#include "ConnectionManager.h"
//#include "Network.h"
#include "Main.h"
#include <iostream>

// Networking Components
#include "NetworkingSystem/System.h"
std::unique_ptr<Client> ClientHandle;
const std::string ip = "192.168.128.173";
const short unsigned port = 54000;

#pragma comment(lib, "Ws2_32.lib")


#include "External Libs/AlphaEngine_V3.08/include/AEEngine.h"
static bool isConnected = false;

GameObject* go1;
AEMtx33 Connectscale, ConnectPosition, Connectfinish;
AEVec2 Connectpos{ 0.0f, 0.0f };
AEGfxVertexList* pMesh3 = 0;
AEGfxTexture* pTex3;
f32 cy, cx;

////************** CHANGE THIS TO SERVER IP *********************
//std::string ipAddr{ "192.168.189.56" }; 
//unsigned short port{ 5050 };

 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/

static UIManager& _um = UIManager::GetInstance();
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();
static AudioManager& _am = AudioManager::GetInstance();
static PauseMenuManager& _pmm = PauseMenuManager::GetInstance();
void GameStateLevelconnectLoad(void)
{
	/*
	_tm.TileManagerLoad("Resources/Level_connect.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();
	*/

	_tm.TileManagerLoad("Resources/Level 1.txt");
	_em.EntityManagerLoad();        // Makes the objects from map info.
	_rm.RenderManagerLoad();
	_um.UIManagerLoad();
	_bm.BackgroundManagerLoad();
	_pmm.PauseMenuManagerLoad();
	_am.AudioManagerLoad();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	pMesh3 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh3, "fail to create object!!");
}

/**************************************************************************/
/*!
	"Initialize" function of this state
	*/
	/**************************************************************************/
void GameStateLevelconnectInit(void)
{
	/*
	_em.EntityManagerInitialize();  // Initializes all object's init function.
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0, 0);
	*/

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0.0f, 0.0f);
	pTex3 = AEGfxTextureLoad("Resources/player_waiting.png");
	AE_ASSERT_MESG(pTex3, "fail!!");
	cy = 0.0f;
	//std::string ipAddr{ "172.20.10.2" };
	//unsigned short port{ 54000 };


	////Network::Initialize(ipAddr, port);
	//std::cout << "Client Side Initialized\n";
	//std::cout << "Client connecting to IP: "<<ipAddr<<"\n";
	//std::cout << "Client connecting to PORT: "<<port<<"\n";
	//Connectionmanager::Connect(ipAddr, port, isConnected);
	//if (isConnected)
	//{
	//	next = GS_STATES::GS_LEVEL1;
	//	std::cout << "Going to Level 1 now\n";
	//}

	auto& entities = EntityManager::GetInstance();		// check current stage entities

	ClientHandle = std::make_unique<Client>();
	ClientHandle->Init(ip, port);

}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateLevelconnectUpdate(void)
{
	//if (!Connectionmanager::is2PlayersConnected)
	//	Connectionmanager::ConnectionStageUpdate();
	//else
	//	Connectionmanager::GameLoopStageUpdate();
	//Network::ConnectionStageUpdate();
	//Connectionmanager::ConnectionStageUpdate();


	/*char buffer[1000] = "HEHE\n";
	ClientHandle->Send(buffer, 1000, ip, port);*/


	ClientHandle->Update();
	if (connectedClient >= 2)
		next = GS_LEVEL1;
	
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
void GameStateLevelconnectDraw(void)
{
	AEMtx33Scale(&Connectscale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight()); // not sure how it will turn out on full screen
	AEMtx33Trans(&ConnectPosition, 0,0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pTex3, 0.0f, 0.0f);
	AEMtx33Concat(&Connectfinish, &Connectscale, &ConnectPosition);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTransform(Connectfinish.m);
	AEGfxMeshDraw(pMesh3, AE_GFX_MDM_TRIANGLES);
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
void GameStateLevelconnectFree(void)
{
	
	// Empty
}

/**************************************************************************/
/*!
	"Unload" function of this state
	This will Free memory for the Program to not have Memory leak
	*/
	/**************************************************************************/
void GameStateLevelconnectUnload(void)
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

	AEGfxMeshFree(pMesh3);
	AEGfxTextureUnload(pTex3);
}
