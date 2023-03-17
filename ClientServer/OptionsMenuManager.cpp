/******************************************************************************
* \file          OptionsMenuManager.cpp
* \brief         This file defines the Options Menu Manager to run Options
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "OptionsMenuManager.h"
#include "AudioManager.h"
#include <fmod.hpp>

static AudioManager& _am = AudioManager::GetInstance();

void OptionsMenuManager::OptionsMenuManagerLoad()
{
	/*===================================*
				Load Options UI
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

	defaultMesh = AEGfxMeshEnd();

	// Later change to white texture
	backgroundTint.rendMesh = defaultMesh;
	backgroundTint.rendTexture = AEGfxTextureLoad("Resources/White.png");
	backgroundTint.thescale = PAUSE_BACKGROUND_TINT_SCALE;

	resumeButton.rendMesh = defaultMesh;
	resumeButton.rendTexture = AEGfxTextureLoad("Resources/ResumeIcon.png");
	resumeButton.thescale = BUTTON_SCALE;

	BGimg.rendMesh = defaultMesh;
	BGimg.rendTexture = AEGfxTextureLoad("Resources/bgvol.png");
	BGimg.thescale = BUTTON_SCALE;

	BGimgmain10.rendMesh = defaultMesh;
	BGimgmain10.rendTexture = AEGfxTextureLoad("Resources/bgvolmain10.png");
	BGimgmain10.thescale = BUTTON_SCALE;

	BGimgmain9.rendMesh = defaultMesh;
	BGimgmain9.rendTexture = AEGfxTextureLoad("Resources/bgvolmain9.png");
	BGimgmain9.thescale = BUTTON_SCALE;

	BGimgmain8.rendMesh = defaultMesh;
	BGimgmain8.rendTexture = AEGfxTextureLoad("Resources/bgvolmain8.png");
	BGimgmain8.thescale = BUTTON_SCALE;

	BGimgmain7.rendMesh = defaultMesh;
	BGimgmain7.rendTexture = AEGfxTextureLoad("Resources/bgvolmain7.png");
	BGimgmain7.thescale = BUTTON_SCALE;

	BGimgmain6.rendMesh = defaultMesh;
	BGimgmain6.rendTexture = AEGfxTextureLoad("Resources/bgvolmain6.png");
	BGimgmain6.thescale = BUTTON_SCALE;

	BGimgmain5.rendMesh = defaultMesh;
	BGimgmain5.rendTexture = AEGfxTextureLoad("Resources/bgvolmain5.png");
	BGimgmain5.thescale = BUTTON_SCALE;

	BGimgmain4.rendMesh = defaultMesh;
	BGimgmain4.rendTexture = AEGfxTextureLoad("Resources/bgvolmain4.png");
	BGimgmain4.thescale = BUTTON_SCALE;

	BGimgmain3.rendMesh = defaultMesh;
	BGimgmain3.rendTexture = AEGfxTextureLoad("Resources/bgvolmain3.png");
	BGimgmain3.thescale = BUTTON_SCALE;

	BGimgmain2.rendMesh = defaultMesh;
	BGimgmain2.rendTexture = AEGfxTextureLoad("Resources/bgvolmain2.png");
	BGimgmain2.thescale = BUTTON_SCALE;

	BGimgmain1.rendMesh = defaultMesh;
	BGimgmain1.rendTexture = AEGfxTextureLoad("Resources/bgvolmain1.png");
	BGimgmain1.thescale = BUTTON_SCALE;

	sevol.rendMesh = defaultMesh;
	sevol.rendTexture = AEGfxTextureLoad("Resources/sevol.png");
	sevol.thescale = BUTTON_SCALE;

	sevolmain10.rendMesh = defaultMesh;
	sevolmain10.rendTexture = AEGfxTextureLoad("Resources/sevolmain10.png");
	sevolmain10.thescale = BUTTON_SCALE;

	sevolmain9.rendMesh = defaultMesh;
	sevolmain9.rendTexture = AEGfxTextureLoad("Resources/sevolmain9.png");
	sevolmain9.thescale = BUTTON_SCALE;

	sevolmain8.rendMesh = defaultMesh;
	sevolmain8.rendTexture = AEGfxTextureLoad("Resources/sevolmain8.png");
	sevolmain8.thescale = BUTTON_SCALE;

	sevolmain7.rendMesh = defaultMesh;
	sevolmain7.rendTexture = AEGfxTextureLoad("Resources/sevolmain7.png");
	sevolmain7.thescale = BUTTON_SCALE;

	sevolmain6.rendMesh = defaultMesh;
	sevolmain6.rendTexture = AEGfxTextureLoad("Resources/sevolmain6.png");
	sevolmain6.thescale = BUTTON_SCALE;

	sevolmain5.rendMesh = defaultMesh;
	sevolmain5.rendTexture = AEGfxTextureLoad("Resources/sevolmain5.png");
	sevolmain5.thescale = BUTTON_SCALE;

	sevolmain4.rendMesh = defaultMesh;
	sevolmain4.rendTexture = AEGfxTextureLoad("Resources/sevolmain4.png");
	sevolmain4.thescale = BUTTON_SCALE;

	sevolmain3.rendMesh = defaultMesh;
	sevolmain3.rendTexture = AEGfxTextureLoad("Resources/sevolmain3.png");
	sevolmain3.thescale = BUTTON_SCALE;

	sevolmain2.rendMesh = defaultMesh;
	sevolmain2.rendTexture = AEGfxTextureLoad("Resources/sevolmain2.png");
	sevolmain2.thescale = BUTTON_SCALE;

	sevolmain1.rendMesh = defaultMesh;
	sevolmain1.rendTexture = AEGfxTextureLoad("Resources/sevolmain1.png");
	sevolmain1.thescale = BUTTON_SCALE;

	logo1.rendMesh = defaultMesh;
	logo1.rendTexture = AEGfxTextureLoad("Resources/CHR.png");
	logo1.thescale = PAUSE_UI_LOGO_SCALE;

	logo2.rendMesh = defaultMesh;
	logo2.rendTexture = AEGfxTextureLoad("Resources/OMA.png");
	logo2.thescale = PAUSE_UI_LOGO_SCALE;

	instructionsImg.rendMesh = defaultMesh;
	instructionsImg.rendTexture = AEGfxTextureLoad("Resources/optioninstruct.png");
	instructionsImg.thescale = VOLIMG_SCALE;
	

	reset.rendMesh = defaultMesh;
	reset.rendTexture = AEGfxTextureLoad("Resources/reset.png");
	reset.thescale = BUTTON_SCALE;

	//pauseUIPartList.reserve(7);
	OptionsMenuPartList.push_back(&backgroundTint);
	OptionsMenuPartList.push_back(&resumeButton);
	OptionsMenuPartList.push_back(&BGimg);
	OptionsMenuPartList.push_back(&sevol);
	OptionsMenuPartList.push_back(&logo1);
	OptionsMenuPartList.push_back(&logo2);
	OptionsMenuPartList.push_back(&instructionsImg);
	OptionsMenuPartList.push_back(&reset);

	BGVollist.push_back(&BGimgmain1);
	BGVollist.push_back(&BGimgmain2);
	BGVollist.push_back(&BGimgmain3);
	BGVollist.push_back(&BGimgmain4);
	BGVollist.push_back(&BGimgmain5);
	BGVollist.push_back(&BGimgmain6);
	BGVollist.push_back(&BGimgmain7);
	BGVollist.push_back(&BGimgmain8);
	BGVollist.push_back(&BGimgmain9);
	BGVollist.push_back(&BGimgmain10);

	SEVollist.push_back(&sevolmain1);
	SEVollist.push_back(&sevolmain2);
	SEVollist.push_back(&sevolmain3);
	SEVollist.push_back(&sevolmain4);
	SEVollist.push_back(&sevolmain5);
	SEVollist.push_back(&sevolmain6);
	SEVollist.push_back(&sevolmain7);
	SEVollist.push_back(&sevolmain8);
	SEVollist.push_back(&sevolmain9);
	SEVollist.push_back(&sevolmain10);

	selectedVol = &resumeButton;
	selectedBG = &BGimgmain10;
	selectedSE = &sevolmain10;
}

void OptionsMenuManager::OptionsMenuManagerUpdate()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		isOptionsEnabled = false;

	// Update all PauseUIPart positions.
	AEVec2 cameraCentrePos;
	AEGfxGetCamPosition(&cameraCentrePos.x, &cameraCentrePos.y);
	for (OptionsUI*& part : OptionsMenuPartList)
		part->pos = cameraCentrePos;
	resumeButton.pos.y = cameraCentrePos.y + 80.0f;
	BGimg.pos.y = cameraCentrePos.y + 10.0f;

	for (OptionsUI*& BG : BGVollist)
	{
		BG->pos.x = cameraCentrePos.x;
		BG->pos.y = cameraCentrePos.y - 60.0f;
	}
	sevol.pos.y = cameraCentrePos.y - 130.0f;
	for (OptionsUI*& SE : SEVollist)
	{
		SE->pos.x = cameraCentrePos.x;
		SE->pos.y = cameraCentrePos.y - 200.0f;
	}
	reset.pos.y = cameraCentrePos.y - 270.0f;
	logo1.pos.y = cameraCentrePos.y + PAUSE_UI_LOGO_OFFSET_Y;
	logo1.pos.x = cameraCentrePos.x - PAUSE_UI_LOGO_OFFSET_X;
	logo2.pos.y = cameraCentrePos.y + PAUSE_UI_LOGO_OFFSET_Y;
	logo2.pos.x = cameraCentrePos.x + PAUSE_UI_LOGO_OFFSET_X;
	instructionsImg.pos.x = cameraCentrePos.x + INSTRUCTIONS_IMAGE_OFFSET_X;

	/*===================================*
				Paused Input
	*====================================*/
	if (isOptionsEnabled)
	{
		if (AEInputCheckTriggered(AEVK_UP))
		{
			if (selectedVol == &resumeButton)
				selectedVol = &reset;
			else if (selectedVol == &BGimg)
				selectedVol = &resumeButton;
			else if (selectedVol == &sevol)
				selectedVol = &BGimg;
			else if (selectedVol = &reset)
				selectedVol = &sevol;
		}
		else if (AEInputCheckTriggered(AEVK_DOWN))
		{
			if (selectedVol == &resumeButton)
				selectedVol = &BGimg;
			else if (selectedVol == &BGimg)
				selectedVol = &sevol;
			else if (selectedVol == &sevol)
				selectedVol = &reset;
			else if (selectedVol == &reset)
				selectedVol = &resumeButton;
			
		}
		else if (AEInputCheckTriggered(AEVK_LEFT))
		{
			if (selectedVol == &resumeButton)
			{

			}
			else if (selectedVol == &BGimg)
			{
				if (_am.bgvol <= 0.1f && _am.bgvol > 0.0f)
				{
					selectedBG = &BGimgmain1;
				}
				if (_am.bgvol <= 0.2f && _am.bgvol > 0.1f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain2;
				}
				if (_am.bgvol <= 0.3f && _am.bgvol > 0.2f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain3;
				}
				if (_am.bgvol <= 0.4f && _am.bgvol > 0.3f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain4;
				}
				if (_am.bgvol <= 0.5f && _am.bgvol > 0.4f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain5;
				}
				if (_am.bgvol <= 0.6f && _am.bgvol > 0.5f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain6;
				}
				if (_am.bgvol <= 0.7f && _am.bgvol > 0.6f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain7;
				}
				if (_am.bgvol <= 0.8f && _am.bgvol > 0.7f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain8;
				}
				if (_am.bgvol <= 0.9f && _am.bgvol > 0.8f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain9;
				}
				if (_am.bgvol <= 1.0f && _am.bgvol > 0.9f)
				{
					_am.bgvol = _am.bgvol - 0.1f;
					selectedBG = &BGimgmain10;
				}
			}

			else if (selectedVol == &sevol)
			{
				if (_am.sevol <= 0.1f && _am.sevol > 0.0f)
				{
					selectedSE = &sevolmain1;
				}
				if (_am.sevol <= 0.2f && _am.sevol > 0.1f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain2;
				}
				if (_am.sevol <= 0.3f && _am.sevol > 0.2f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain3;
				}
				if (_am.sevol <= 0.4f && _am.sevol > 0.3f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain4;
				}
				if (_am.sevol <= 0.5f && _am.sevol > 0.4f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain5;
				}
				if (_am.sevol <= 0.6f && _am.sevol > 0.5f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain6;
				}
				if (_am.sevol <= 0.7f && _am.sevol > 0.6f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain7;
				}
				if (_am.sevol <= 0.8f && _am.sevol > 0.7f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain8;
				}
				if (_am.sevol <= 0.9f && _am.sevol > 0.8f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain9;
				}
				if (_am.sevol <= 1.0f && _am.sevol > 0.9f)
				{
					_am.sevol = _am.sevol - 0.1f;
					selectedSE = &sevolmain10;
				}
			}
		}
		else if (AEInputCheckTriggered(AEVK_RIGHT))
		{
			if (selectedVol == &resumeButton)
			{
				// do nothing
			}
			else if (selectedVol == &BGimg)
			{
				if (_am.bgvol <= 1.0f && _am.bgvol > 0.9f)
				{

					selectedBG = &BGimgmain10;
				}
				else if (_am.bgvol <= 0.9f && _am.bgvol > 0.8f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain9;
				}
				else if (_am.bgvol <= 0.8f && _am.bgvol > 0.7f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain8;
				}
				else if (_am.bgvol <= 0.7f && _am.bgvol > 0.6f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain7;
				}
				else  if (_am.bgvol <= 0.6f && _am.bgvol > 0.5f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain6;
				}
				else if (_am.bgvol <= 0.5f && _am.bgvol > 0.4f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain5;
				}
				else  if (_am.bgvol <= 0.4f && _am.bgvol > 0.3f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain4;
				}

				else if (_am.bgvol <= 0.3f && _am.bgvol > 0.2f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain3;
				}
				else if (_am.bgvol <= 0.2f && _am.bgvol > 0.1f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain2;
				}
				else if (_am.bgvol <= 0.1f && _am.bgvol > 0.0f)
				{
					_am.bgvol = _am.bgvol + 0.1f;
					selectedBG = &BGimgmain1;
				}
			}
				
			else if (selectedVol == &sevol)
			{
				if (_am.sevol <= 1.0f && _am.sevol > 0.9f)
				{

					selectedSE = &sevolmain10;
				}
				else if (_am.sevol <= 0.9f && _am.sevol > 0.8f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain9;
				}
				else if (_am.sevol <= 0.8f && _am.sevol > 0.7f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain8;
				}
				else if (_am.sevol <= 0.7f && _am.sevol > 0.6f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain7;
				}
				else if (_am.sevol <= 0.6f && _am.sevol > 0.5f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain6;
				}
				else if (_am.sevol <= 0.5f && _am.sevol > 0.4f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain5;
				}
				else if (_am.sevol <= 0.4f && _am.sevol > 0.3f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain4;
				}
				else if (_am.sevol <= 0.3f && _am.sevol > 0.2f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain3;
				}
				else if (_am.sevol <= 0.2f && _am.sevol > 0.1f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain2;
				}
				else if (_am.sevol <= 0.1f && _am.sevol > 0.0f)
				{
					_am.sevol = _am.sevol + 0.1f;
					selectedSE = &sevolmain1;
				}
			}
		}
		// user space bar to select
		else if (AEInputCheckTriggered(AEVK_SPACE))
		{
			if (selectedVol == &resumeButton)
			{
				isOptionsEnabled = false;
				_am.bgm_paused = false;
				_am.backgroundmusic->setPaused(_am.bgm_paused);
			}
			else if (selectedVol == &reset)
			{
				if (remove("Resources/color.txt") != 0)
				{
					perror("Error deleting file\n");
				}
				if (remove("Resources/levels.txt") != 0)
				{
					perror("Error deleting file\n");
				}
			}
		}
	}
}

void OptionsMenuManager::OptionsMenuManagerDraw()
{
	/*===================================*
				Options UI Draw
	*====================================*/
	// If not paused, draw.
	if (isOptionsEnabled)
	{
		for (OptionsUI*& part : OptionsMenuPartList)
		{
			if (part->flag == 0)
				continue; 
			if (selectedVol != &BGimg)
				if (part == &instructionsImg)
					continue;
			AEMtx33 mtx;
			AEMtx33 trans, scale, rot;
			if (part == &logo1 || part == &logo2 ||
				part == &backgroundTint || part == &instructionsImg)
			{
				AEMtx33Scale(&scale, part->thescale, part->thescale);
			}
			else
			{
				if(part == selectedVol)
					AEMtx33Scale(&scale, BUTTON_WIDTH * (part->thescale + 3.0f), BUTTON_HEIGHT * (part->thescale + 3.0f));
				else
					AEMtx33Scale(&scale, BUTTON_WIDTH * part->thescale, BUTTON_HEIGHT * part->thescale);
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

		for (OptionsUI*& BG : BGVollist)
		{
			if (selectedBG == BG)
			{
				AEMtx33 mtx;
				AEMtx33 trans, scale, rot;
				AEMtx33Scale(&scale, BUTTON_WIDTH * BG->thescale, BUTTON_HEIGHT * BG->thescale);
				AEMtx33Trans(&trans, BG->pos.x, BG->pos.y);
				AEMtx33Identity(&rot);
				AEMtx33Concat(&mtx, &rot, &scale);
				AEMtx33Concat(&mtx, &trans, &mtx);
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetTransparency(1.0f);
				AEGfxTextureSet(BG->rendTexture, 0, 0);
				AEGfxSetTransform(mtx.m);
				AEGfxMeshDraw(BG->rendMesh, AE_GFX_MDM_TRIANGLES);
			}
		}

		for (OptionsUI*& SE : SEVollist)
		{
			if (selectedSE == SE)
			{
				AEMtx33 mtx;
				AEMtx33 trans, scale, rot;
				AEMtx33Scale(&scale, BUTTON_WIDTH * SE->thescale, BUTTON_HEIGHT * SE->thescale);
				AEMtx33Trans(&trans, SE->pos.x, SE->pos.y);
				AEMtx33Identity(&rot);
				AEMtx33Concat(&mtx, &rot, &scale);
				AEMtx33Concat(&mtx, &trans, &mtx);
				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
				AEGfxSetTransparency(1.0f);
				AEGfxTextureSet(SE->rendTexture, 0, 0);
				AEGfxSetTransform(mtx.m);
				AEGfxMeshDraw(SE->rendMesh, AE_GFX_MDM_TRIANGLES);
			}
		}
		std::string textOut = "Options";
		const char* test = textOut.c_str();
		AEGfxPrint(font, const_cast<char*>(test), -0.1f, 0.35f, 2.0f, 2.0f, 1.0f, 1.0f);
	}
}
 
void OptionsMenuManager::OptionsMenuManagerUnload()
{
	/*===================================*
			Free Options UI Memory
	*====================================*/
	for (OptionsUI*& part : OptionsMenuPartList)
	{
		AEGfxTextureUnload(part->rendTexture);
	}
	for(OptionsUI*& BG : BGVollist)
	{
		AEGfxTextureUnload(BG->rendTexture);
	}
	for (OptionsUI*& SE : SEVollist)
	{
		AEGfxTextureUnload(SE->rendTexture);
	}
	AEGfxMeshFree(defaultMesh);
	OptionsMenuPartList.clear();
	BGVollist.clear();
	SEVollist.clear();
}