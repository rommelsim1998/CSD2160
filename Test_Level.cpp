/******************************************************************************/
/*!
\file		Test_Level.cpp
\brief		Test level to save time
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Constants.h"

// Create manager instances. (Make them static)
static EntityManager& _em = EntityManager::GetInstance();
static RenderManager& _rm = RenderManager::GetInstance();
static PhysicsManager& _pm = PhysicsManager::GetInstance();
static TileManager& _tm = TileManager::GetInstance();
static CollisionManager& _cm = CollisionManager::GetInstance();
static BackgroundManager& _bm = BackgroundManager::GetInstance();


void TestLevel_Load()
{
    _tm.TileManagerLoad("Resources/map.txt");
    _em.EntityManagerLoad();        // Makes the objects from map info.
    _rm.RenderManagerLoad();
    _bm.BackgroundManagerLoad();
    //sButton Level1,Level2,exit;
}

void TestLevel_Initialize()
{
    _em.EntityManagerInitialize();  // Initializes all object's init function.
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
    AEGfxSetCamPosition(0, 0);
}

void TestLevel_Update()
{
    _em.EntityManagerUpdate();      // Logic
    _pm.PhysicsManagerUpdate();     // Physics
    _cm.CollisionManagerUpdate();   // Collision (And Collision Response)
    _bm.BackgroundManagerUpdate();
}

void TestLevel_Draw()
{
    _bm.BackgroundManagerDraw();
    // Object's Draw functions called inside RenderManagerDraw();
    _rm.RenderManagerDraw();
}

void TestLevel_Free()
{
    // Empty
}

void TestLevel_Unload()
{
    _rm.RenderManagerUnload();
    _em.EntityManagerUnload();
    _tm.TileManagerUnload();
    _bm.BackgroundManagerUnload();
}