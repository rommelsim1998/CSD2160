/******************************************************************************
* \file			GameObject.cpp
* \brief        This file contains the class definition of the base class
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

#include "GameObject.h"
#include "Main.h"

// Call this for creating game objects of a type.
GameObject::GameObject(int objType, int id)
	: flag{ true }, type{ objType }, ID{ id }, isCollidable{ true },
	hasGravity{ true }, renderOrder{ 0 }
{
	ResetGameObject(1);
}

/*===================================*
				Accessors
*====================================*/

/***************************************************************************/
/*!
	\brief
		Returns the type of the object.
*/
/**************************************************************************/
int GameObject::GetType() const {
	return type;
}

/***************************************************************************/
/*!
	\brief
		Returns flag of the object
*/
/**************************************************************************/
bool GameObject::GetFlag() const {
	return flag;
}

/***************************************************************************/
/*!
	\brief
		Returns the ID of the object
*/
/**************************************************************************/
int GameObject::GetID() const {
	return ID;
}

/***************************************************************************/
/*!
	\brief
		Returns the colour of the object
*/
/**************************************************************************/
Color GameObject::GetColor() const
{
	return color;
}

/***************************************************************************/
/*!
	\brief
		Returns the scale of the object
*/
/**************************************************************************/
float GameObject::GetScale() const {
	return scale;
}

/***************************************************************************/
/*!
	\brief
		Returns the vector position of the object
*/
/**************************************************************************/
AEVec2 GameObject::GetPosition() const {
	return posCurr;
}

/***************************************************************************/
/*!
	\brief
		Returns the vector velocity of the object
*/
/**************************************************************************/
AEVec2 GameObject::GetVelocity() const {
	return velCurr;
}

/***************************************************************************/
/*!
	\brief
		Returns the direction of the object
*/
/**************************************************************************/
float GameObject::GetDirection() const {
	return dirCurr;
}

/***************************************************************************/
/*!
	\brief
		Returns the bounding box of the object
*/
/**************************************************************************/
AABB GameObject::GetBoundingBox() const {
	return boundingBox;
}

/***************************************************************************/
/*!
	\brief
		Returns the collision flag of the object
*/
/**************************************************************************/
int GameObject::GetCollisionFlag() const {
	return collisionFlag;
}

/***************************************************************************/
/*!
	\brief
		Returns the IsCollidable boolean of the object.
		This is related to whether the object is now collidable by other
		objects not the same as its colour due to the change in background
		color.
*/
/**************************************************************************/
bool GameObject::GetIsCollidable() const {
	return isCollidable;
}

/***************************************************************************/
/*!
	\brief
		Returns the hasGravity boolean of whether it is now affected
		by gravity.
*/
/**************************************************************************/
bool GameObject::GetHasGravity() const {
	return hasGravity;
}

/***************************************************************************/
/*!
	\brief
		Returns the restartPos of the object
*/
/**************************************************************************/
AEVec2 GameObject::GetRestartPos() const {
	return restartPos;
}

/***************************************************************************/
/*!
	\brief
		Returns the render data of the object.
*/
/**************************************************************************/
RenderData* GameObject::GetRenderData() {
	return &rendData;
}

/***************************************************************************/
/*!
	\brief
		Returns the render order of the object
*/
/**************************************************************************/
int GameObject::GetRenderOrder() const {
	return renderOrder;
}

/***************************************************************************/
/*!
	\brief
		Returns the transformation matrix of the object
*/
/**************************************************************************/
AEMtx33 GameObject::GetMTrans() const {
	return m_trans;
}

/***************************************************************************/
/*!
	\brief
		Returns the rotation matrix of the object
*/
/**************************************************************************/
AEMtx33 GameObject::GetMRotation() const {
	return m_rot;
}

/***************************************************************************/
/*!
	\brief
		Returns the scale matrix of the object
*/
/**************************************************************************/
AEMtx33 GameObject::GetMScale() const {
	return m_scale;
}

/*===================================*
				Mutators
*====================================*/

/***************************************************************************/
/*!
	\brief
		Sets the type of the object

	\t
		The type of the object to set.
*/
/**************************************************************************/
void GameObject::SetType(int t) {
	type = t;
}

/***************************************************************************/
/*!
	\brief
		Sets the flag of the object

	\param fl
		The boolean flag to set the object.
*/
/**************************************************************************/
void GameObject::SetFlag(bool fl)
{
	flag = fl;
}

/***************************************************************************/
/*!
	\brief
		Sets the scale of the object

	\param s
		The scale to set the scale of the object to
*/
/**************************************************************************/
void GameObject::SetScale(float s) {
	scale = s;
}

/***************************************************************************/
/*!
	\brief
		Sets the position of the object

	\param pos
		The position to set the object's position to
*/
/**************************************************************************/
void GameObject::SetPosition(AEVec2& pos) {
	posCurr = pos;
}

/***************************************************************************/
/*!
	\brief
		Sets the velocity of the object

	\param vel
		The velocity of the object to set to.
*/
/**************************************************************************/
void GameObject::SetVelocity(AEVec2& vel) {
	velCurr = vel;
}

/***************************************************************************/
/*!
	\brief
		Sets the direction of the object.

	\param dir
		The direction of the object to set to.
*/
/**************************************************************************/
void GameObject::SetDirection(float dir) {
	dirCurr = dir;
}

/***************************************************************************/
/*!
	\brief
		Sets the colour of the object

	\param colo
		The colour of the object to set to. Uses the ColorList.
*/
/**************************************************************************/
void GameObject::SetColor(Color colo)
{
	color = colo;
}

/***************************************************************************/
/*!
	\brief
		Sets the bounding box of the object

	\param bb
		The bounding box of the object to set to.
*/
/**************************************************************************/
void GameObject::SetBoundingBox(AABB& bb) {
	boundingBox = bb;
}

/***************************************************************************/
/*!
	\brief
		Toggles the flag condition of the object.
*/
/**************************************************************************/
void GameObject::ToggleFlag() {
	flag = !flag;
}

/***************************************************************************/
/*!
	\brief
		Sets the collision flag of the object

	\param colFlag
		The collision flag to set for the object.
*/
/**************************************************************************/
void GameObject::SetCollisionFlag(int colFlag) {
	collisionFlag = colFlag;
}

/***************************************************************************/
/*!
	\brief
		Sets the isCollidable boolean. IsCollidable only for colour based
		objects affected by Player background change power.

	\param isCol
		The boolean value to set the IsCollidable of object.
*/
/**************************************************************************/
void GameObject::SetIsCollidable(bool isCol) {
	isCollidable = isCol;
}

/***************************************************************************/
/*!
	\brief
		Sets the HasGravity of the object. It handles if the object is
		affected by gravity.

	\param hasGrav
		The boolean value to set if the object has gravity
*/
/**************************************************************************/
void GameObject::SetHasGravity(bool hasGrav)
{
	hasGravity = hasGrav;
}

/***************************************************************************/
/*!
	\brief
		Sets the restart position value of the object.

	\param resPos
		The vector position to set the restart position.
*/
/**************************************************************************/
void GameObject::SetRestartPos(AEVec2& resPos) {
	restartPos = resPos;
}

/***************************************************************************/
/*!
	\brief
		Sets the rendering order of the object.

	\param order
		The rendering order of the object to be set.
*/
/**************************************************************************/
void GameObject::SetRenderOrder(int order) {
	renderOrder = order;
}

/***************************************************************************/
/*!
	\brief
		Sets the transformation matrix of the object.

	\param mtrans
		The transformation matrix to set.
*/
/**************************************************************************/
void GameObject::SetMTrans(AEMtx33 mtrans) {
	m_trans = mtrans;
}

/***************************************************************************/
/*!
	\brief
		Sets the rotation matrix of the object.

	\param mrot
		The rotatation matrix to set.
*/
/**************************************************************************/
void GameObject::SetMRotation(AEMtx33 mrot) {
	m_rot = mrot;
}

/***************************************************************************/
/*!
	\brief
		Sets the scaling matrix of the object.

	\param mscale
		The scaling matrix of the object to set.
*/
/**************************************************************************/
void GameObject::SetMScale(AEMtx33 mscale) {
	m_scale = mscale;
}

/***************************************************************************/
/*!
	\brief
		This function resets the game object. Which is used for both
		new creation of the object and also for object pooling in
		the entity manager.

	\param flag
		The flag to set, if not indicated then it is default false.
*/
/**************************************************************************/
void GameObject::ResetGameObject(bool theFlag = false)
{
	AEVec2 zero;
	AEVec2Zero(&zero);
	scale = 0.0f;
	posCurr = zero;
	velCurr = zero;
	dirCurr = 0.0f;
	boundingBox.min = zero;
	boundingBox.max = zero;
	isCollidable = true;
	if (theFlag) {}
	// Set automatically to identity matrix. Must set in logic.
	AEMtx33 matrix;
	AEMtx33Identity(&matrix);
	m_trans = matrix;
	m_rot = matrix;
	m_scale = matrix;
}