/******************************************************************************
* \file			PauseMenuManager.cpp
* \brief        This file contains the class definition of the Pause Menu
*				Manager class.
* \author       Kyle Vincent Velasco Gatchalian, 95% Code Contribution
*				Tan Jian Jie, 5% Code Contribution
*
*				The Pause Menu Manager handles the pausing of the game and also
*				displaying of the necessary functions for what to do when
*				the game is paused.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "PauseMenuManager.h"
#include "AudioManager.h"
#include <fmod.hpp>

static AudioManager& _am = AudioManager::GetInstance();

/***************************************************************************/
/*!
	\brief
		The Load function of Pause Manager which initializes the different
		parts of the UI for displaying when the game is paused.
*/
/**************************************************************************/
void PauseMenuManager::PauseMenuManagerLoad()
{
	/*===================================*
				Load Pause UI
	*====================================*/
	AEGfxMeshStart();

	// Below is for square effect. use 0.65f in color change count speed.
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);  // Normalized
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	// Below is for circle effect. Use 0.50f in color change count speed.
	/*int Parts = 36;
	for (float i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf(i * 2 * PI / Parts) * 1.0f, sinf(i * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / Parts) * 1.0f, sinf((i + 1) * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f);
	}*/
	//rendMesh = AEGfxMeshEnd();

	defaultMesh = AEGfxMeshEnd();

	// Later change to white texture
	backgroundTint.rendMesh = defaultMesh;
	backgroundTint.rendTexture = AEGfxTextureLoad("Resources/White.png");
	backgroundTint.scale = PAUSE_BACKGROUND_TINT_SCALE;

	resumeButton.rendMesh = defaultMesh;
	resumeButton.rendTexture = AEGfxTextureLoad("Resources/ResumeIcon.png");
	resumeButton.scale = BUTTON_SCALE;

	menuButton.rendMesh = defaultMesh;
	menuButton.rendTexture = AEGfxTextureLoad("Resources/MenuIcon.png");
	menuButton.scale = BUTTON_SCALE;

	instructionsButton.rendMesh = defaultMesh;
	instructionsButton.rendTexture = AEGfxTextureLoad("Resources/InstrucIcon.png");
	instructionsButton.scale = BUTTON_SCALE;

	restartButton.rendMesh = defaultMesh;
	restartButton.rendTexture = AEGfxTextureLoad("Resources/RestartIcon.png");
	restartButton.scale = BUTTON_SCALE;

	quitButton.rendMesh = defaultMesh;
	quitButton.rendTexture = AEGfxTextureLoad("Resources/QuitIcon.png");
	quitButton.scale = BUTTON_SCALE;

	logo1.rendMesh = defaultMesh;
	logo1.rendTexture = AEGfxTextureLoad("Resources/CHR.png");
	logo1.scale = PAUSE_UI_LOGO_SCALE;

	logo2.rendMesh = defaultMesh;
	logo2.rendTexture = AEGfxTextureLoad("Resources/OMA.png");
	logo2.scale = PAUSE_UI_LOGO_SCALE;

	instructionsImg.rendMesh = defaultMesh;
	instructionsImg.rendTexture = AEGfxTextureLoad("Resources/instructions.png");
	instructionsImg.scale = INSTRUCTIONS_IMAGE_SCALE;

	pauseUIPartList.push_back(&backgroundTint);
	pauseUIPartList.push_back(&resumeButton);
	pauseUIPartList.push_back(&menuButton);
	pauseUIPartList.push_back(&instructionsButton);
	pauseUIPartList.push_back(&restartButton);
	pauseUIPartList.push_back(&quitButton);
	pauseUIPartList.push_back(&logo1);
	pauseUIPartList.push_back(&logo2);
	pauseUIPartList.push_back(&instructionsImg);

	selectedOption = &resumeButton;
}

/***************************************************************************/
/*!
	\brief
		The Update function of Pause Manager which updates the position
		and selected button of the pause UI.
*/
/**************************************************************************/
void PauseMenuManager::PauseMenuManagerUpdate()
{

	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
 		isPaused = !isPaused;
		_am.bgm_paused = !_am.bgm_paused;
		_am.backgroundmusic->setPaused(_am.bgm_paused);

	}

	// Update all PauseUIPart positions.
	AEVec2 cameraCentrePos;
	AEGfxGetCamPosition(&cameraCentrePos.x, &cameraCentrePos.y);
	for (PauseUIPart*& part : pauseUIPartList)
		part->pos = cameraCentrePos;
	resumeButton.pos.y = cameraCentrePos.y + 80.0f;
	menuButton.pos.y = cameraCentrePos.y + 10.0f;
	instructionsButton.pos.y = cameraCentrePos.y - 60.0f;
	restartButton.pos.y = cameraCentrePos.y - 130.0f;
	quitButton.pos.y = cameraCentrePos.y - 200.0f;
	logo1.pos.y = cameraCentrePos.y + PAUSE_UI_LOGO_OFFSET_Y;
	logo1.pos.x = cameraCentrePos.x - PAUSE_UI_LOGO_OFFSET_X;
	logo2.pos.y = cameraCentrePos.y + PAUSE_UI_LOGO_OFFSET_Y;
	logo2.pos.x = cameraCentrePos.x + PAUSE_UI_LOGO_OFFSET_X;
	instructionsImg.pos.x = cameraCentrePos.x + INSTRUCTIONS_IMAGE_OFFSET_X;

	/*===================================*
				Paused Input
	*====================================*/
	if (isPaused)
	{
		if (AEInputCheckTriggered(AEVK_UP))
		{
			if (selectedOption == &resumeButton)
				selectedOption = &quitButton;
			else if (selectedOption == &menuButton)
				selectedOption = &resumeButton;
			else if (selectedOption == &instructionsButton)
				selectedOption = &menuButton;
			else if (selectedOption == &restartButton)
				selectedOption = &instructionsButton;
			else if (selectedOption == &quitButton)
				selectedOption = &restartButton;
		}
		else if (AEInputCheckTriggered(AEVK_DOWN))
		{
			if (selectedOption == &resumeButton)
				selectedOption = &menuButton;
			else if (selectedOption == &menuButton)
				selectedOption = &instructionsButton;
			else if (selectedOption == &instructionsButton)
				selectedOption = &restartButton;
			else if (selectedOption == &restartButton)
				selectedOption = &quitButton;
			else if (selectedOption == &quitButton)
				selectedOption = &resumeButton;
		}
		else if (AEInputCheckTriggered(AEVK_SPACE))
		{
			if (selectedOption == &resumeButton)
			{
				isPaused = false;
				_am.bgm_paused = false;
				_am.backgroundmusic->setPaused(_am.bgm_paused);

			}
			else if (selectedOption == &menuButton)
			{
				next = GS_MAINMENU;
				isPaused = false;

				_am.bgm_paused = false;
				_am.backgroundmusic->setPaused(_am.bgm_paused);

			}
			else if (selectedOption == &restartButton)
			{
				next = GS_RESTART;
				isPaused = false;
				//ensure that when on main menu and select restart this resets the counter

				_am.bgm_paused = false;
				_am.backgroundmusic->setPaused(_am.bgm_paused);
			}
			else if (selectedOption == &quitButton)
				next = GS_QUIT;
		}
	}

}

/***************************************************************************/
/*!
	\brief
		The Draw function of the Pause Menu Manager which handles how the
		parts of the UI are drawn.
*/
/**************************************************************************/
void PauseMenuManager::PauseMenuManagerDraw()
{
	/*===================================*
				Paused UI Draw
	*====================================*/
	// If not paused, draw.
	if (isPaused)
	{
		for (PauseUIPart*& part : pauseUIPartList)
		{
			if (part->flag == 0)
				continue; 
			if (selectedOption != &instructionsButton)
				if (part == &instructionsImg)
					continue;
			AEMtx33 mtx;
			AEMtx33 trans, scale, rot;
			if (part == &logo1 || part == &logo2 ||
				part == &backgroundTint || part == &instructionsImg)
			{
				AEMtx33Scale(&scale, part->scale, part->scale);
			}
			else
			{
				if(part == selectedOption)
					AEMtx33Scale(&scale, BUTTON_WIDTH * (part->scale + 3.0f), BUTTON_HEIGHT * (part->scale + 3.0f));
				else
					AEMtx33Scale(&scale, BUTTON_WIDTH * part->scale, BUTTON_HEIGHT * part->scale);
			}
			AEMtx33Trans(&trans, part->pos.x, part->pos.y);
			AEMtx33Identity(&rot);
			AEMtx33Concat(&mtx, &rot, &scale);
			AEMtx33Concat(&mtx, &trans, &mtx);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			if (part == &backgroundTint)
			{
				AEGfxSetTintColor(0.0f, 0.0f, 0.0f, 0.6f);
				AEGfxSetTransparency(0.8f);
			}
			else
			{
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetTransparency(1.0f);
			}
			AEGfxTextureSet(part->rendTexture, 0, 0);
			AEGfxSetTransform(mtx.m);
			AEGfxMeshDraw(part->rendMesh, AE_GFX_MDM_TRIANGLES);
		}
		std::string textOut = "Paused";
		const char* test = textOut.c_str();
		AEGfxPrint(font, const_cast<char*>(test), -0.1f, 0.35f, 2.0f, 2.0f, 1.0f, 1.0f);
	}
}
 
/***************************************************************************/
/*!
	\brief
		The Unload function of the Pause Menu Manager to free the rendering
		data assets used.
*/
/**************************************************************************/
void PauseMenuManager::PauseMenuManagerUnload()
{
	/*===================================*
			Free Pause UI Memory
	*====================================*/
	for (PauseUIPart*& part : pauseUIPartList)
	{
		AEGfxTextureUnload(part->rendTexture);

		part->rendMesh = nullptr;
		part->rendTexture = nullptr;

	}

	selectedOption = nullptr;
	AEGfxMeshFree(defaultMesh);
	pauseUIPartList.clear();
}