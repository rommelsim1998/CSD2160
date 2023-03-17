/******************************************************************************
* \file			ImageBox.cpp
* \brief        This file contains the class definition of the ImageBox object
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*				Sebastian, _____ Code Contribution
*
*				The ImageBox class object is used for displaying background
*				related things that don't affect the gameplay but only to an
*				extent which includes dialogue boxes
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "ImageBox.h"

/*
	HOW TO USE IMAGEBOX

	- Set what you want to render in Rendering Manager's
		AssignImageBoxTexture() function.
		Based on GS and the imagebox type you want to set.

	- Set again here in Initialize based on GS and imagebox type.
*/

/***************************************************************************/
/*!
	\brief
		The double overloaded constructor of ImageBox which takes in the id
		and type of the object.

	\param id
		The id of the object to be set.

	\param type
		The type of the object to be set.
*/
/**************************************************************************/
ImageBox::ImageBox(int id, int type) : GameObject(type, id),
	horizontal_Range{ 0.0f }, vertical_Range{ 0.0f }, showOnNearEffect{ false }{
	// Empty By Design
}

/***************************************************************************/
/*!
	\brief
		The default deconstructor of the object.
*/
/**************************************************************************/
ImageBox::~ImageBox() {
	// Empty By Design
}

/***************************************************************************/
/*!
	\brief
		The initialize overriden function Initialize from the base
		GameObject class.
*/
/**************************************************************************/
void ImageBox::GameObjectInitialize()
{
	SetHasGravity(false);
	SetIsCollidable(false);
	SetScale(TILE_HEIGHT);
	if (current == GS_LEVEL3 || current == GS_LEVEL4 || current == GS_LEVEL7)
	{
		if (GetType() == TYPE_IMAGEBOX1)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 1.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
	}
	else if (current == GS_MAINMENU || current == GS_LS || current == GS_LEVEL2 || current == GS_LEVEL5 || current == GS_LEVEL6)
	{
		if (GetType() == TYPE_IMAGEBOX1)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 1.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX2)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 1.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
	}
	else if (current == GS_LEVEL1)
	{
		if (GetType() == TYPE_IMAGEBOX1)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 1.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX2)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 1.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX3)
		{
			// Check if the colorobj has been looted and stop showing, else show the text
			std::ifstream colorfile;
			std::string line;
			colorfile.open("Resources/color.txt");
			if (colorfile.is_open())
			{
				while (getline(colorfile, line))
				{
					size_t found;
					if (((found = line.find("A")) != std::string::npos) && (current == GS_LEVEL1))
					{
						SetFlag(false);
					}
					else if (((found = line.find("a")) != std::string::npos) && (current == GS_LEVEL1))
					{
						SetFlag(true);
						horizontal_Scale = 6.0f;
						vertical_Scale = 2.0f;
						horizontal_Range = 1.0f;
						vertical_Range = 7.0f;
						SetShowOnNearEffect(true);
					}
				}
				colorfile.close();
			}
		}
	}
	else if (current == GS_END)
	{
		if (GetType() == TYPE_IMAGEBOX1)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX2)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX3)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX4)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX5)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
		}
		if (GetType() == TYPE_IMAGEBOX6)
		{
			horizontal_Scale = 6.0f;
			vertical_Scale = 2.0f;
			horizontal_Range = 7.0f;
			vertical_Range = 7.0f;
			SetShowOnNearEffect(true);
			SetTimerMode(true);
			SetTimer(10.0f);
		}
	}
	else
	{
		horizontal_Scale = 4.0f;
		vertical_Scale = 1.0f;
	}
	//horizontalDetectRange = 10;
	AEVec2 resPos = GetRestartPos();
	SetPosition(resPos);
	return;
}

/***************************************************************************/
/*!
	\brief
		The initialize overriden function Update from the base
		GameObject class.
*/
/**************************************************************************/
void ImageBox::GameObjectUpdate()
{
	AABB boundbox;
	boundbox.min.x = -0.5f * GetScale() * horizontal_Range + GetPosition().x;
	boundbox.max.x = 0.5f * GetScale() * horizontal_Range + GetPosition().x;
	boundbox.min.y = -0.5f * GetScale() * vertical_Range + GetPosition().y;
	boundbox.max.y = 0.5f * GetScale() * vertical_Range + GetPosition().y;
	SetDetectionBox(boundbox);
	if (timerMode)
	{
		timer -= g_dt;
		if (timer < 0.0f)
		{
			timerMode = false;
			SetFlag(false);
		}
	}
}

/***************************************************************************/
/*!
	\brief
		The initialize overriden function Draw from the base
		GameObject class.
*/
/**************************************************************************/
void ImageBox::GameObjectDraw()
{
	// Setting matrix for render.
	AEMtx33 mScale;
	float theScale = GetScale();
	AEMtx33Scale(&mScale, theScale * horizontal_Scale, theScale * vertical_Scale);

	SetMScale(mScale);

	AEVec2 pos = GetPosition();
	AEMtx33 mTrans;
	AEMtx33Trans(&mTrans, pos.x, pos.y);
	SetMTrans(mTrans);
	return;
}

/***************************************************************************/
/*!
	\brief
		Returns the horizontal scale of the object.
*/
/**************************************************************************/
float ImageBox::GetHorizontalScale() const {
	return horizontal_Scale;
}
/***************************************************************************/
/*!
	\brief
		Returns the horizontal range of the object.
*/
/**************************************************************************/
float ImageBox::GetHorizontalRange() const {
	return horizontal_Range;
}
/***************************************************************************/
/*!
	\brief
		Returns the vertical scale of the object.
*/
/**************************************************************************/
float ImageBox::GetVerticalScale() const {
	return vertical_Scale;
}
/***************************************************************************/
/*!
	\brief
		Returns the vertical range of the object.
*/
/**************************************************************************/
float ImageBox::GetVerticalRange() const {
	return vertical_Range;
}
/***************************************************************************/
/*!
	\brief
		Returns the ShowEffectNear boolean value.
*/
/**************************************************************************/
bool ImageBox::GetShowOnNearEffect() const {
	return showOnNearEffect;
}
/***************************************************************************/
/*!
	\brief
		Returns the DetectionBox of the object.
*/
/**************************************************************************/
AABB ImageBox::GetDetectionBox() const
{
	return detectionBox;
}

/***************************************************************************/
/*!
	\brief
		Sets the horizontal scale of the object.

	\param scale
		The horizontal scale of the object to be set.
*/
/**************************************************************************/
void ImageBox::SetHorizontalScale(float theScale) {
	horizontal_Scale = theScale;
}
/***************************************************************************/
/*!
	\brief
		Sets the horizontal range of the object.

	\param
		The range value to set onto the object's horizontal range.
*/
/**************************************************************************/
void ImageBox::SetHorizontalRange(float range) {
	horizontal_Range = range;
}
/***************************************************************************/
/*!
	\brief
		Sets the vertical scale of the object.

	\param scale
		The vertical scale of the object to be set.
*/
/**************************************************************************/
void ImageBox::SetVerticalScale(float theScale) {
	vertical_Scale = theScale;
}
/***************************************************************************/
/*!
	\brief
		Sets the vertical range of the object.

	\param range
		The vertical range of the object to be set.
*/
/**************************************************************************/
void ImageBox::SetVerticalRange(float range) {
	vertical_Range = range;
}
/***************************************************************************/
/*!
	\brief
		Sets the timer of the object.

	\param time
		The time to set the object's timer.
*/
/**************************************************************************/
void ImageBox::SetTimer(float time) {
	timer = time;
}
/***************************************************************************/
/*!
	\brief
		Sets the ShowOnNearEffect by a given boolean value.

	\param bol
		The boolean value to set the ShowOnNearEffect boolean
*/
/**************************************************************************/
void ImageBox::SetShowOnNearEffect(bool bol) {
	showOnNearEffect = bol;
}
/***************************************************************************/
/*!
	\brief
		Sets the TimerMode boolean to a specified boolean value.

	\param bol
		The boolean value to set the TimeMode boolean.
*/
/**************************************************************************/
void ImageBox::SetTimerMode(bool bol) {
	timerMode = bol;
}
/***************************************************************************/
/*!
	\brief
		Sets the detection box of the object.

	\param boundingBox
		The collision box to set for the detectionBox's bounding box.
*/
/**************************************************************************/
void ImageBox::SetDetectionBox(AABB const& bBox)
{
	detectionBox = bBox;
}