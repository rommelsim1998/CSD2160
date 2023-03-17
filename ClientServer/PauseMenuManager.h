#ifndef PAUSEMENUMANAGER_H
#define PAUSEMENUMANAGER_H

/******************************************************************************
* \file			PauseMenuManager.h
* \brief        This file contains the class declaratin of the Pause Menu
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

#include "Constants.h"

class PauseMenuManager
{
public:
	struct PauseUIPart
	{
		int flag = 1;
		AEVec2 pos{ 0.0f, 0.0f };
		AEGfxVertexList* rendMesh = nullptr;
		AEGfxTexture* rendTexture = nullptr;
		float scale = 0.0f;
		//AEMtx33 mtx;
	};

private:

	AEGfxVertexList* defaultMesh = nullptr;

	// List of UIparts
	std::vector<PauseUIPart*> pauseUIPartList;

	PauseUIPart backgroundTint;
	PauseUIPart resumeButton;
	PauseUIPart menuButton;
	PauseUIPart instructionsButton;
	PauseUIPart restartButton;
	PauseUIPart quitButton;
	PauseUIPart logo1;
	PauseUIPart logo2;
	PauseUIPart instructionsImg;

	PauseUIPart* selectedOption = nullptr;

public:
	/*===================================*
				Constructors
	*====================================*/
	PauseMenuManager() = default;
	~PauseMenuManager() = default;

	void PauseMenuManagerLoad();
	void PauseMenuManagerUpdate();
	void PauseMenuManagerDraw();
	void PauseMenuManagerUnload();

	/*===================================*
				Accessors
	*====================================*/

	/*===================================*
				Mutators
	*====================================*/

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static PauseMenuManager& GetInstance()
	{
		static PauseMenuManager _instance;
		return _instance;
	}

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	PauseMenuManager(const PauseMenuManager&) = delete;
	PauseMenuManager(PauseMenuManager&&) = delete;
	PauseMenuManager& operator=(const PauseMenuManager&) = delete;
	PauseMenuManager& operator=(PauseMenuManager&&) = delete;
};


#endif