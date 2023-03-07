#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

/******************************************************************************
* \file			BackgroundManager.h
* \brief        This file contains the class declaration of the Background
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

class BackgroundManager
{
private:
	// The background manager acts as the background itself also.
	// Hence has it's own data.

	AEVec2 backgroundPos{ 0.0f, 0.0f };
	float scale = 0.0f;
	AEGfxVertexList* rendMesh = nullptr;
	AEGfxTexture* rendTexture = nullptr;
	Color effectColor = Color::COLOR_BLACK;
	Color backgroundColor = Color::COLOR_BLACK;
	float counter = 0.0f;

public:
	/*===================================*
				Constructors
	*====================================*/
	BackgroundManager() = default;
	~BackgroundManager() = default;

	void BackgroundManagerLoad();
	void BackgroundManagerUpdate();
	void BackgroundManagerDraw();
	void BackgroundManagerUnload();

	/*===================================*
				Accessors
	*====================================*/
	AEVec2 GetBackgroundPos() const;
	AEGfxVertexList* GetVertex() const;
	AEGfxTexture* GetTexture() const;
	Color GetColor() const;
	Color GetBackgroundColor() const;
	float GetCounter() const;

	/*===================================*
				Mutators
	*====================================*/
	void SetBackgroundPos(AEVec2&);
	void SetVertex(AEGfxVertexList*);
	void SetTexture(AEGfxTexture*);
	void ChangeColor(Color);
	void SetBackgroundColor(Color);
	void SetCounter(float);
	void DecreaseCounter(float);
	void IncreaseScale(float);

	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static BackgroundManager& GetInstance()
	{
		static BackgroundManager _instance;
		return _instance;
	}

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	BackgroundManager(const BackgroundManager&) = delete;
	BackgroundManager(BackgroundManager&&) = delete;
	BackgroundManager& operator=(const BackgroundManager&) = delete;
	BackgroundManager& operator=(BackgroundManager&&) = delete;
};


#endif