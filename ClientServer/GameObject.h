#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/******************************************************************************
* \file			GameObject.h
* \brief        This file contains the class declaration of the base class
*				GameObject.
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The GameObject class is the base class for all of the derived
*				classes of Entities in this game and engine.
*				It contains the virtual functions to be overridden and defined
*				in the derived class for Load, Initialize, Update, Draw, Free
*				and Unload. It also contains the data members for being a
*				Game Object
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "RenderData.h"
#include "ColorList.h"

/*===================================*
			Collision Flags
*====================================*/

static const unsigned int	COLLISION_LEFT = 0x00000001;	//0001
static const unsigned int	COLLISION_RIGHT = 0x00000002;	//0010
static const unsigned int	COLLISION_TOP = 0x00000004;		//0100
static const unsigned int	COLLISION_BOTTOM = 0x00000008;	//1000

/*===================================*
			AABB Struct
*====================================*/
struct AABB
{
	AEVec2  min;
	AEVec2  max;
};

class GameObject {
private:
	/*===================================*
			Private - Data Members
	*====================================*/
	const int ID;
	int type;
	bool flag;
	Color color = Color::COLOR_BLACK;

	float scale;
	AEVec2 posCurr;
	AEVec2 velCurr;
	float dirCurr;
	AABB boundingBox;
	int collisionFlag;
	bool isCollidable;
	bool hasGravity;

	// For initializing position on GS_RESTART
	AEVec2 restartPos;

	// Saves more space to store pointer.
	RenderData rendData;
	int renderOrder;			// Which layer to render object in.

	AEMtx33 m_trans, m_rot, m_scale;



public:

	/*===================================*
				Constructors
	*====================================*/
	GameObject() = delete;
	GameObject(int, int);

	virtual ~GameObject() = default;

	/*===================================*
					Accessors
	*====================================*/
	int GetType() const;
	bool GetFlag() const;
	int GetID() const;
	float GetScale() const;
	AEVec2 GetPosition() const;
	AEVec2 GetVelocity() const;
	float GetDirection() const;
	Color GetColor() const;
	AABB GetBoundingBox() const;
	int GetCollisionFlag() const;
	bool GetIsCollidable() const;
	bool GetHasGravity() const;

	AEVec2 GetRestartPos() const;

	RenderData* GetRenderData();
	int GetRenderOrder() const;
	AEMtx33 GetMTrans() const;
	AEMtx33 GetMRotation() const;
	AEMtx33 GetMScale() const;

	/*===================================*
					Mutators
	*====================================*/

	void SetType(int);
	void SetFlag(bool);
	void SetScale(float);
	void SetPosition(AEVec2&);
	void SetVelocity(AEVec2&);
	void SetDirection(float);
	void SetColor(Color);
	void SetBoundingBox(AABB&);
	void ToggleFlag();
	void SetCollisionFlag(int);
	void SetIsCollidable(bool);
	void SetHasGravity(bool);

	void SetRestartPos(AEVec2&);
	void SetRenderOrder(int);
	void SetMTrans(AEMtx33);
	void SetMRotation(AEMtx33);
	void SetMScale(AEMtx33);

	void ResetGameObject(bool);

	// pure virtual function. Must be defined by Derived class.
	virtual void GameObjectInitialize() = 0;
	virtual void GameObjectUpdate() = 0;
	virtual void GameObjectDraw() = 0;
};

#endif