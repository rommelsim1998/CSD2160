/******************************************************************************
* \file			UIManager.h
* \brief		This file declares the UIManager class
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Constants.h"

class UIManager
{
public:
	struct UIPart
	{
		AEVec2 pos{};
		AEGfxVertexList* rendMesh = nullptr;
		AEGfxTexture* rendTexture = nullptr;
		AEMtx33 mtx{};
	};

private:
	AEGfxVertexList* normalMesh = nullptr;
	std::vector<UIPart*> parts;
	std::vector<UIPart*> title;
	std::vector<UIPart*> image;
	std::vector<UIPart*> icon;
	UIPart title1;
	UIPart title2;
	UIPart aPart;
	UIPart bPart;
	UIPart cPart;
	UIPart dPart;
	UIPart up;
	UIPart down;
	UIPart left;
	UIPart right;
	UIPart LShft;
	UIPart Space;
	UIPart ESC;
	UIPart txtMove;
	UIPart txtColor;
	UIPart txtPull;
	UIPart txtMain;
	UIPart txtJump;
	UIPart king;
	UIPart lvicon1;
	UIPart lvicon2;
	UIPart lvicon3;
	UIPart lvicon4;
	UIPart lvicon5;
	UIPart lvicon6;

public:
	/*===================================*
				Constructors
	*====================================*/
	UIManager() = default;
	~UIManager() = default;

	void UIManagerLoad();
	void UIManagerUpdate();
	void UIManagerDraw();
	void UIManagerUnload();

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static UIManager& GetInstance()
	{
		static UIManager _instance;
		return _instance;
	}

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	UIManager(const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator=(const UIManager&) = delete;
	UIManager& operator=(UIManager&&) = delete;
};


#endif