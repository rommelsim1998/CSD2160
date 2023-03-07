/******************************************************************************/
/*!
\file		GameState_Credits.cpp
\brief		Scrolling Credits that can be skipped with escape or space bar
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "GameState_Credits.h"
#include "Main.h"
#include <iostream>
#include "External Libs/AlphaEngine_V3.08/include/AEEngine.h"

f32 timeR = 90.0f;
f32 counteR;
AEMtx33 Cscale, Position, finish;
AEVec2 Cpos{ 0.0f, 0.0f };
AEGfxVertexList* pMesh2 = 0;
AEGfxTexture* pTex2;
f32 y,x;
f32 scrolling_speed = 0.01f;
/**
 * @brief Load function for the game state credits
 *
 * @param void
 * @return void
 */

void GameStateCreditsLoad()
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

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "fail to create object!!");
}
/**
 * @brief Init function for the game state credits, loads the texture and sets the camera position
 *
 * @param void
 * @return void
 */
void GameStateCreditsInit()
{

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0.0f, (f32)AEGetWindowHeight() + 1300.0f); 
	pTex2 = AEGfxTextureLoad("Resources/credits2.png");
	AE_ASSERT_MESG(pTex2, "fail!!");
	y = 0.0f;
	counteR = timeR;
}
/**
 * @brief Update function for the game state credits. Updates the counter and y value
 *
 * @param void
 * @return void
 */

void GameStateCreditsUpdate()
{
	counteR -= g_dt;
	if (counteR <= 0.0f || AEInputCheckCurr(AEVK_SPACE) || AEInputCheckCurr(AEVK_ESCAPE))
	{
		next = GS_MAINMENU;
	}
	y += g_dt * scrolling_speed;
}
/**
 * @brief Draw function for the game state credits
 *
 * @param void
 * @return void
 */

void GameStateCreditsDraw()
{
	AEMtx33Scale(&Cscale, (f32)AEGetWindowWidth() , (f32)AEGetWindowHeight() + 3500.f); // not sure how it will turn out on full screen
	AEMtx33Trans(&Position, Cpos.x, y);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pTex2, 0.0f, 0.0f);
	AEMtx33Concat(&finish, &Cscale, &Position);
	AEGfxSetTransparency(1.0f);
	AEGfxSetTransform(finish.m);
	AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
}
/**
 * @brief Free function for the game state credits
 *
 * @param void
 * @return void
 */
void GameStateCreditsFree()
{
	
}
/**
 * @brief Unload function for the game state credits
 *
 * @param void
 * @return void
 */
void GameStateCreditsUnload()
{
	AEGfxMeshFree(pMesh2);
	AEGfxTextureUnload(pTex2);
}
