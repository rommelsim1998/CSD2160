/******************************************************************************
* \file			BackgroundManager.cpp
* \brief        This file contains the class definition of the Background
*				Manager class.
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The background manager handles the background effect when
*				the player changes the colour of the background.
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include <iostream>
#include "Main.h"
#include "BackgroundManager.h"
#include "ColorList.h"
#include "Constants.h"

/***************************************************************************/
/*!
	\brief
		The Load function of Background Manager which assigns texture
		to the background effect.
*/
/**************************************************************************/
void BackgroundManager::BackgroundManagerLoad()
{
	// Load the normalized mesh of the background.
	// Sets the position of the background in the middle of the screen.
	AEGfxMeshStart();
	
	// Below is for square effect. use 0.65f in color change count speed.
	//AEGfxTriAdd(
	//	-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
	//	-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);  // Normalized
	//AEGfxTriAdd(
	//	0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	// Below is for circle effect. Use 0.50f in color change count speed.
	int Parts = 36;
	for (float i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf(i * 2 * PI / Parts) * 1.0f, sinf(i * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / Parts) * 1.0f, sinf((i + 1) * 2 * PI / Parts) * 1.0f, 0xFFFFFF00, 0.0f, 0.0f);
	}
	rendMesh = AEGfxMeshEnd();

	// Later change to white texture
	rendTexture = AEGfxTextureLoad("Resources/White.png");

	f32 camX, camY;
	AEGfxGetCamPosition(&camX, &camY);
	backgroundPos.x = static_cast<float>(camX);
	backgroundPos.y = static_cast<float>(camY);
	effectColor = Color::COLOR_GREY;
	scale = 1.0f;
}

/***************************************************************************/
/*!
	\brief
		The Update function of background manager which updates the effects
		of the background and handles switching of which colour is now being
		shown.
*/
/**************************************************************************/
void BackgroundManager::BackgroundManagerUpdate()
{
	// Update the background.
	AEGfxGetCamPosition(&backgroundPos.x, &backgroundPos.y);
	// If counter is greater than 0.0f
	if (GetCounter() > 0.0f)
	{
		// Decrease and cause animation scaling.
		DecreaseCounter(g_dt);
		IncreaseScale((scale * g_dt) + COLOR_POWER_SPEED);
	}
	else
	{
		backgroundColor = effectColor;
		switch (backgroundColor)
		{
			case Color::COLOR_YELLOW:
				AEGfxSetBackgroundColor(1.0f, 1.0f, 0.5f);
				break;
			case Color::COLOR_BLUE:
				AEGfxSetBackgroundColor(0.369f, 0.612f, 1.0f);
				break;
			case Color::COLOR_GREEN:
				AEGfxSetBackgroundColor(0.310f, 1.0f, 0.459f);
				break;
			case Color::COLOR_RED:
				AEGfxSetBackgroundColor(1.0f, 0.310f, 0.310f);
				break;
			case Color::COLOR_GREY:
				AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);
				break;
			default:
				// Default is grey.
				AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);
		}
	}
}

/***************************************************************************/
/*!
	\brief
		The Draw function of the background manager which draws out the effects.
*/
/**************************************************************************/
void BackgroundManager::BackgroundManagerDraw()
{
	// Based on colour, render it that colour.
	// Transform based on the scale also.
	AEMtx33 mtx;
	AEMtx33 Backgroundtrans, Backgroundscale, Backgroundrotation;
	AEMtx33Scale(&Backgroundscale, scale, scale);
	AEMtx33Trans(&Backgroundtrans, backgroundPos.x, backgroundPos.y);
	AEMtx33Identity(&Backgroundrotation);
	AEMtx33Concat(&mtx, &Backgroundrotation, &Backgroundscale);
	AEMtx33Concat(&mtx, &Backgroundtrans, &mtx);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	switch (effectColor)
	{
		case Color::COLOR_RED:
		{
			AEGfxSetTintColor(1.0f, 0.310f, 0.310f, 1.0f);
			break;
		}
		case Color::COLOR_YELLOW:
		{
			AEGfxSetTintColor(1.0f, 1.0f, 0.5f, 1.0f);
			break;
		}
		case Color::COLOR_BLUE:
		{
			AEGfxSetTintColor(0.369f, 0.612f, 1.0f, 1.0f);
			break;
		}
		case Color::COLOR_GREEN:
		{
			AEGfxSetTintColor(0.310f, 1.0f, 0.459f, 1.0f);
			break;
		}
		case Color::COLOR_GREY:
		{
			AEGfxSetTintColor(0.5f, 0.5f, 0.5f, 1.0f);
			break;
		}
		default:
		{
			AEGfxSetTintColor(0.5f, 0.5f, 0.5f, 1.0f);
			break;
		}
	}
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(rendTexture, 0, 0);
	AEGfxSetTransform(mtx.m);
	AEGfxMeshDraw(rendMesh, AE_GFX_MDM_TRIANGLES);
}

/***************************************************************************/
/*!
	\brief
		The Unload function of the background manager which frees the rendering
		data of the effects.
*/
/**************************************************************************/
void BackgroundManager::BackgroundManagerUnload()
{
	// Unload renderData.
	//delete rendMesh;
	AEGfxMeshFree(rendMesh);
	AEGfxTextureUnload(rendTexture);
	rendTexture = nullptr;
	rendMesh = nullptr;
}

AEVec2 BackgroundManager::GetBackgroundPos() const {
	return backgroundPos;
}

AEGfxVertexList* BackgroundManager::GetVertex() const {
	return rendMesh;
}

AEGfxTexture* BackgroundManager::GetTexture() const {
	return rendTexture;
}

Color BackgroundManager::GetColor() const {
	return effectColor;
}

Color BackgroundManager::GetBackgroundColor() const {
	return backgroundColor;
}

float BackgroundManager::GetCounter() const {
	return counter;
}

void BackgroundManager::SetBackgroundPos(AEVec2& pos) {
	backgroundPos = pos;
}

void BackgroundManager::SetVertex(AEGfxVertexList* mesh) {
	rendMesh = mesh;
}

void BackgroundManager::SetTexture(AEGfxTexture* tex) {
	rendTexture = tex;
}

void BackgroundManager::ChangeColor(Color col) {
	// Also will reset background effect scale and timer
	if(col != effectColor)
		scale = RESET_BACKGROUND_SIZE;
		counter = COLOR_CHANGE_COUNT;
	effectColor = col;
}

void BackgroundManager::SetBackgroundColor(Color col) {
	// Sets both effect color and background color.
	effectColor = col;
	backgroundColor = col;
}

void BackgroundManager::SetCounter(float count) {
	counter = count;
}

void BackgroundManager::DecreaseCounter(float count) {
	counter -= count;
}

void BackgroundManager::IncreaseScale(float count) {
	scale += count;
}