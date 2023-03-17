/******************************************************************************/
/*!
\file		GameState_SplashScreen.cpp
\brief		Splash Screen
\author 	Ng Yuwen Felicia, 100%

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "Constants.h"

AEGfxVertexList* pMesh1 = 0;  
AEGfxTexture* pTex1; 
f32 timer, counter;
AEMtx33 scale;
AEVec2 pos{ 0.0f, 0.0f };
/**
 * @brief GameState function for the splash screen that loads the mesh required for the image
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenLoad()
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

	pMesh1 = AEGfxMeshEnd();
	//AE_ASSERT_MESG(pMesh1, "fail to create object!!");
}
/**
 * @brief Init function for the game state splash screen
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenInit()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetCamPosition(0.0f, 100.f);
	AEGfxSetTransparency(1.0f);
	AEMtx33Scale(&scale, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight());
	//pTex1 = AEGfxTextureLoad("Resources/DigiPen_Singapore_WEB_WHITE.png");
	pTex1 = AEGfxTextureLoad("Resources/splash.png");
	//AE_ASSERT_MESG(pTex1, "fail to find photo!!");
	timer = 3.0f;
	counter = timer;
}
/**
 * @brief Update function for the game state splash screen to progress to main menu
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenUpdate()
{
	if (counter <= 0.0f || AEInputCheckCurr(AEVK_SPACE))
	{
		next = GS_MAINMENU;
	}
	counter -= g_dt;
}
/**
 * @brief Draw function for the game state splash screen it sets the fade out effect of the splash screen as time passes
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenDraw()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(pTex1, 0.0f, 0.0f);
	AEGfxSetTransform(scale.m);
	AEGfxSetTransparency(counter / timer);
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
}
/**
 * @brief Free function for the game state splash screen
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenFree()
{
}
/**
 * @brief Unload function for the game state splash screen
 *
 * @param void
 * @return void
 */

void GameStateSplashScreenUnload()
{
	AEGfxMeshFree(pMesh1);
	AEGfxTextureUnload(pTex1);
}