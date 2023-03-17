/******************************************************************************
* \file			RenderData.cpp
* \brief        This file contains the class definition of the RenderData object.
* \author       Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
*				The RenderData object class
*
*Copyright (C) 2021 DigiPen Institute of Technology.
*Reproduction or disclosure of this file or its contents without the
*prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "RenderData.h"

/***************************************************************************/
/*!
    \brief
        Default constructor of RenderData that also uses memory to set the
        mesh of the assigned RenderData.
*/
/**************************************************************************/
RenderData::RenderData()
{
    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);  // Normalized
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

    rendMesh = AEGfxMeshEnd();
}

/***************************************************************************/
/*!
    \brief
    The overloaded constructor of the RenderData object that takes in
    a mesh and texture data.

*/
/**************************************************************************/
RenderData::RenderData(AEGfxVertexList* rMesh, AEGfxTexture* rTex)
    : rendMesh{ rMesh }, rendTexture{ rTex }{
    // Empty by Design
}

/***************************************************************************/
/*!
    \brief
        Returns the vertex list mesh data of the RenderData object.
*/
/**************************************************************************/
AEGfxVertexList* RenderData::GetRendMesh() const {
    return rendMesh;
}

/***************************************************************************/
/*!
    \brief
        Returns the texture data of the RenderData object.
*/
/**************************************************************************/
AEGfxTexture* RenderData::GetRendTexture() const {
    return rendTexture;
}

/***************************************************************************/
/*!
    \brief
        Sets the Vertext List mesh data for the object.

    \param rMesh
        The mesh data to set the object's mesh.
*/
/**************************************************************************/
void RenderData::SetRendMesh(AEGfxVertexList* const& rMesh) {
    rendMesh = rMesh;
}

/***************************************************************************/
/*!
    \brief
        Sets the texture of the object

    \param rMesh
        The texture data of the object's texture.
*/
/**************************************************************************/
void RenderData::SetRendTexture(AEGfxTexture* const& rTex) {
    rendTexture = rTex;
}