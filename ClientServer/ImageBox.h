#ifndef IMAGEBOX_H
#define IMAGEBOX_H
/******************************************************************************
* \file			ImageBox.h
* \brief        This file contains the class declaration of the ImageBox object
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The ImageBox class object is used for displaying background
*				related things that don't affect the gameplay but only to an
*				extent which includes dialogue boxes
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

class ImageBox : public GameObject {
private:
	/*===================================*
			Private - Data Members
	*====================================*/

	float horizontal_Scale;
	float vertical_Scale;
	float horizontal_Range;			// Horizontal Range of detection
	float vertical_Range;			// Horizontal Range of detection
	float timer;
	bool showOnNearEffect;
	bool timerMode;

	AABB detectionBox;

public:

	/*===================================*
				Constructors
	*====================================*/
	ImageBox() = delete;
	ImageBox(int, int);
	~ImageBox();

	/*===================================*
				Accessors
	*====================================*/
	float GetHorizontalScale() const;
	float GetHorizontalRange() const;
	float GetVerticalScale() const;
	float GetVerticalRange() const;
	bool GetShowOnNearEffect() const;
	AABB GetDetectionBox() const;

	/*===================================*
				Mutators
	*====================================*/
	void SetHorizontalScale(float);
	void SetHorizontalRange(float);
	void SetVerticalScale(float);
	void SetVerticalRange(float);
	void SetDetectionBox(AABB const&);
	void SetTimer(float);
	void SetShowOnNearEffect(bool);
	void SetTimerMode(bool);

	void GameObjectInitialize() override;
	void GameObjectUpdate() override;
	void GameObjectDraw() override;
};

#endif