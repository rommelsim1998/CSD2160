/******************************************************************************
* \file          OptionsMenuManager.h
* \brief         This file declares the Options Class
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#ifndef OPTIONSMENUMANAGER_H
#define OPTIONSMENUMANAGER_H

#include "Constants.h"

class OptionsMenuManager
{
public:
	struct OptionsUI
	{
		int flag = 1;
		AEVec2 pos{ 0.0f, 0.0f };
		AEGfxVertexList* rendMesh = nullptr;
		AEGfxTexture* rendTexture = nullptr;
		float thescale = 0.0f;
		bool showflag = 0;
	};

private:

	AEGfxVertexList* defaultMesh = nullptr;

	// Below is for the background 
	//float scale;
	//AEGfxVertexList* rendMesh = nullptr;
	//AEGfxTexture* rendTexture = nullptr;

	// List of UIparts
	std::vector<OptionsUI*> OptionsMenuPartList;
	std::vector<OptionsUI*> BGVollist;
	std::vector<OptionsUI*> SEVollist;

	OptionsUI backgroundTint;
	OptionsUI resumeButton;
	OptionsUI BGimg;
	OptionsUI BGimgmain1;
	OptionsUI BGimgmain2;
	OptionsUI BGimgmain3;
	OptionsUI BGimgmain4;
	OptionsUI BGimgmain5;
	OptionsUI BGimgmain6;
	OptionsUI BGimgmain7;
	OptionsUI BGimgmain8;
	OptionsUI BGimgmain9;
	OptionsUI BGimgmain10;
	OptionsUI sevol;
	OptionsUI sevolmain1;
	OptionsUI sevolmain2;
	OptionsUI sevolmain3;
	OptionsUI sevolmain4;
	OptionsUI sevolmain5;
	OptionsUI sevolmain6;
	OptionsUI sevolmain7;
	OptionsUI sevolmain8;
	OptionsUI sevolmain9;
	OptionsUI sevolmain10;
	OptionsUI logo1;
	OptionsUI logo2;
	OptionsUI instructionsImg;
	OptionsUI reset;

	OptionsUI* selectedVol = nullptr;
	OptionsUI* selectedBG = nullptr;
	OptionsUI* selectedSE = nullptr;

public:
	/*===================================*
				Constructors
	*====================================*/
	OptionsMenuManager() = default;
	~OptionsMenuManager() = default;

	void OptionsMenuManagerLoad();
	void OptionsMenuManagerUpdate();
	void OptionsMenuManagerDraw();
	void OptionsMenuManagerUnload();



	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static OptionsMenuManager& GetInstance()
	{
		static OptionsMenuManager _instance;
		return _instance;
	}

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	OptionsMenuManager(const OptionsMenuManager&) = delete;
	OptionsMenuManager(OptionsMenuManager&&) = delete;
	OptionsMenuManager& operator=(const OptionsMenuManager&) = delete;
	OptionsMenuManager& operator=(OptionsMenuManager&&) = delete;
};


#endif