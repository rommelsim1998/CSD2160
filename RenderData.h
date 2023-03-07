#ifndef RENDERDATA_H
#define RENDERDATA_H

/******************************************************************************
* \file			RenderData.cpp
* \brief        This file contains the class declaration of the RenderData object.
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The RenderData object class
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include <AEEngine.h>

class RenderData {
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	AEGfxVertexList* rendMesh = nullptr;
	AEGfxTexture* rendTexture = nullptr;
	// Add Sprite Sheet Object.

public:
	/*===================================*
				Constructors
	*====================================*/
	RenderData();
	RenderData(AEGfxVertexList*, AEGfxTexture*);
	~RenderData() = default;

	/*===================================*
					Accessors
	*====================================*/
	//float GetRenderOrder() const;
	AEGfxVertexList* GetRendMesh() const;
	AEGfxTexture* GetRendTexture() const;

	/*===================================*
					Mutators
	*====================================*/
	//void SetRenderOrder(float);
	void SetRendMesh(AEGfxVertexList* const&);
	void SetRendTexture(AEGfxTexture* const&);

	// Below are virtual functions to be implemented for the objects themselves.
};

#endif