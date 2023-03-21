/******************************************************************************
* \file          GameState_Connect.cpp
* \brief         This file is the main file for Game state of level 1
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#pragma once

#include "Network.h"
#include "Constants.h"
#include "Main.h"
#include "GameState_Connect.h"

// Networking Components
#include "../NetworkingSystem/System.h"
//std::unique_ptr<Server> ServerHandle;
const std::string ip = "192.168.50.119";
const short unsigned port = 54000;

/*
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
*/

#include "../External Libs/AlphaEngine_V3.08/include/AEEngine.h"

AEMtx33 Connectscale, ConnectPosition, Connectfinish;
AEVec2 Connectpos{ 0.0f, 0.0f };
AEGfxVertexList* pMesh3 = 0;
AEGfxTexture* pTex3;
f32 cy, cx;

static Server& ServerHandle = Server::getInstance();
static Client& ClientHandle = Client::getInstance();

 /**************************************************************************/
/*!
	"Load" function of this state
	*/
	/**************************************************************************/
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
	//AE_ASSERT_MESG(pMesh3, "fail to create object!!");
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
	pTex3 = AEGfxTextureLoad("Resources/servermode.png");
	//AE_ASSERT_MESG(pTex3, "fail!!");
	cy = 0.0f;

	// Server Init
	//ServerHandle = std::make_unique<Server>();
	ServerHandle.Init(ip, port);
	/*ServerHandle = std::make_unique<System>();
	ServerHandle->Init(ip, port, System::SERVER);*/
	//Network::Init(ip, port);

	//// gets host name and ip address of the host automatically, no need to key in manually
	//char hostname[1024];
	//gethostname(hostname, 1024);

	//struct addrinfo hints, * addr;
	//ZeroMemory(&hints, sizeof(hints));
	//hints.ai_family = AF_INET;

	//getaddrinfo(hostname, NULL, &hints, &addr);

	//char ipstr[INET_ADDRSTRLEN];
	//inet_ntop(addr->ai_family, &(((struct sockaddr_in*)addr->ai_addr)->sin_addr), ipstr, sizeof(ipstr));
	//std::cout << "IP address: " << ipstr << std::endl;




	//std::cout << "Server Side initialized \n";>	Chroma.exe!Client::Update() Line 157	C++

	//std::cout << "Server Ip Address: "<<ip <<"\n";
	//std::cout << "Server Port is "<<port<<"\n";
}

/**************************************************************************/
/*!
	"Update" function of this state
	*/
	/**************************************************************************/
void GameStateLevelconnectUpdate(void)
{

	/*
	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
		next = GS_MAINMENU; // To main menu
	}
	*/

	ServerHandle.Update();
	if (connectedClient >= 2)
		next = GS_LEVEL1;
	//Network::ClientConnectionStageUpdate();

	//
	//if (Network::connectedClientCount == 2)
	//{
	//	std::cout<<"2 clients connected \n";

	//	//next = GS_MLEVEL1;
	//}


	//if its in pause state
	/*
	if (!isPaused)
	{
		_em.EntityManagerUpdate();      // Logic
		_pm.PhysicsManagerUpdate(5);     // Physics
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
	AEMtx33Trans(&ConnectPosition, 0, 0);
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
