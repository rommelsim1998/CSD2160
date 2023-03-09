/******************************************************************************
* \file			UIManager.cpp
* \brief		This file does the loading of mesh of all UI images, updating
*               of UI positions, drawing of UI images on the screen, and 
*               unloading of all created UI images and their mesh.
* \author		Sebastian Yew Kai Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#include "Constants.h"

/***************************************************************************/
/*!
\brief
    A function that loads the meshes and give each UI a texture to load.
    Once done, it will be pushed back in to the respective vector that 
    will later loop through the entire vector to draw and update.
*/
/**************************************************************************/
void UIManager::UIManagerLoad()
{
    parts.reserve(20);

    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f); 
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
    normalMesh = AEGfxMeshEnd();

    aPart.rendMesh = normalMesh;
    aPart.rendTexture = AEGfxTextureLoad("Resources/RedUI.png");
    parts.push_back(&aPart);

    bPart.rendMesh = normalMesh;
    bPart.rendTexture = AEGfxTextureLoad("Resources/BlueUI.png");
    parts.push_back(&bPart);

    cPart.rendMesh = normalMesh;
    cPart.rendTexture = AEGfxTextureLoad("Resources/GreenUI.png");
    parts.push_back(&cPart);

    dPart.rendMesh = normalMesh;
    dPart.rendTexture = AEGfxTextureLoad("Resources/YellowUI.png");
    parts.push_back(&dPart);

    up.rendMesh = normalMesh;
    up.rendTexture = AEGfxTextureLoad("Resources/UpArrow.png");
    parts.push_back(&up);

    down.rendMesh = normalMesh;
    down.rendTexture = AEGfxTextureLoad("Resources/DownArrow.png");
    parts.push_back(&down);

    left.rendMesh = normalMesh;
    left.rendTexture = AEGfxTextureLoad("Resources/LeftArrow.png");
    parts.push_back(&left);

    right.rendMesh = normalMesh;
    right.rendTexture = AEGfxTextureLoad("Resources/RightArrow.png");
    parts.push_back(&right);

    ESC.rendMesh = normalMesh;
    ESC.rendTexture = AEGfxTextureLoad("Resources/ESC.png");
    parts.push_back(&ESC);

    LShft.rendMesh = normalMesh;
    LShft.rendTexture = AEGfxTextureLoad("Resources/Lshft.png");
    parts.push_back(&LShft);

    Space.rendMesh = normalMesh;
    Space.rendTexture = AEGfxTextureLoad("Resources/Space.png");
    parts.push_back(&Space);

    txtMove.rendMesh = normalMesh;
    txtMove.rendTexture = AEGfxTextureLoad("Resources/Move.png");
    parts.push_back(&txtMove);

    txtJump.rendMesh = normalMesh;
    txtJump.rendTexture = AEGfxTextureLoad("Resources/Jump.png");
    parts.push_back(&txtJump);

    txtMain.rendMesh = normalMesh;
    txtMain.rendTexture = AEGfxTextureLoad("Resources/Pause.png");
    parts.push_back(&txtMain);

    txtPull.rendMesh = normalMesh;
    txtPull.rendTexture = AEGfxTextureLoad("Resources/Pull.png");
    parts.push_back(&txtPull);

    txtColor.rendMesh = normalMesh;
    txtColor.rendTexture = AEGfxTextureLoad("Resources/Color.png");
    parts.push_back(&txtColor);

    if (current == GS_MAINMENU)
    {
        title.reserve(4);

        title1.rendMesh = normalMesh;
        title1.rendTexture = AEGfxTextureLoad("Resources/CHR.png");
        title.push_back(&title1);

        title2.rendMesh = normalMesh;
        title2.rendTexture = AEGfxTextureLoad("Resources/OMA.png");
        title.push_back(&title2);
    }

    if (current == GS_END)
    {
        image.reserve(2);
        king.rendMesh = normalMesh;
        king.rendTexture = AEGfxTextureLoad("Resources/king.png");
        image.push_back(&king);
    }

    if (current == GS_LS)
    {
        icon.reserve(7);
        lvicon1.rendMesh = normalMesh;
        lvicon1.rendTexture = AEGfxTextureLoad("Resources/Level1&2Sign.png");
        icon.push_back(&lvicon1);

        lvicon2.rendMesh = normalMesh;
        lvicon2.rendTexture = AEGfxTextureLoad("Resources/Level3&4Sign.png");
        icon.push_back(&lvicon2);

        lvicon3.rendMesh = normalMesh;
        lvicon3.rendTexture = AEGfxTextureLoad("Resources/Level5&6Sign.png");
        icon.push_back(&lvicon3);

        lvicon4.rendMesh = normalMesh;
        lvicon4.rendTexture = AEGfxTextureLoad("Resources/Level7&8Sign.png");
        icon.push_back(&lvicon4);

        lvicon5.rendMesh = normalMesh;
        lvicon5.rendTexture = AEGfxTextureLoad("Resources/FinalSign.png");
        icon.push_back(&lvicon5);

        lvicon6.rendMesh = normalMesh;
        lvicon6.rendTexture = AEGfxTextureLoad("Resources/MenuSign.png");
        icon.push_back(&lvicon6);
    }
}

/***************************************************************************/
/*!
\brief
    A function that updates the UI position displaying the screen, either 
    permanently in that spot, or following the camera position.
*/
/**************************************************************************/
void UIManager::UIManagerUpdate()
{
    AEVec2 campos;
    AEGfxGetCamPosition(&campos.x, &campos.y);
    AEVec2Set(&aPart.pos, campos.x + 350.0f, campos.y - 300.0f);
    AEVec2Set(&bPart.pos, aPart.pos.x + 100.0f, aPart.pos.y);
    AEVec2Set(&cPart.pos, bPart.pos.x + 100.0f, aPart.pos.y);
    AEVec2Set(&dPart.pos, cPart.pos.x + 100.0f, aPart.pos.y);
    AEVec2Set(&txtColor.pos, bPart.pos.x + 50.0f, bPart.pos.y + 70.0f);
    AEVec2Set(&up.pos, campos.x - 650.0f, campos.y - 250.0f);
    AEVec2Set(&txtMove.pos, up.pos.x, up.pos.y + 70.0f);
    AEVec2Set(&down.pos, up.pos.x, up.pos.y - 70.0f);
    AEVec2Set(&left.pos, down.pos.x - 70.0f, down.pos.y);
    AEVec2Set(&right.pos, down.pos.x + 70.0f, down.pos.y);
    AEVec2Set(&ESC.pos, campos.x - 450.0f, aPart.pos.y);
    AEVec2Set(&txtMain.pos, ESC.pos.x, ESC.pos.y + 70.0f);
    AEVec2Set(&Space.pos, ESC.pos.x + 100.0f, ESC.pos.y);
    AEVec2Set(&txtJump.pos, Space.pos.x, Space.pos.y + 70.0f);
    AEVec2Set(&LShft.pos, Space.pos.x + 100.0f, ESC.pos.y);
    AEVec2Set(&txtPull.pos, LShft.pos.x, LShft.pos.y + 70.0f);

    for (size_t i = 0; i < parts.size(); ++i)
    {
        AEMtx33 trans, scale;
        AEVec2 pos = parts[i]->pos;
        AEMtx33Scale(&scale, 60.0f, 60.0f);
        AEMtx33Trans(&trans, pos.x, pos.y);
        AEMtx33Concat(&parts[i]->mtx, &trans, &scale);
    }
   
    if (current == GS_MAINMENU)
    {
        AEVec2Set(&title1.pos, 780.0f, 500.0f);
        AEVec2Set(&title2.pos, 955.0f, 500.0f);

        for (size_t j = 0; j < title.size(); ++j)
        {
            AEMtx33 trans, scale;
            AEVec2 pos = title[j]->pos;
            AEMtx33Scale(&scale, 200.0f, 200.0f);
            AEMtx33Trans(&trans, pos.x, pos.y);
            AEMtx33Concat(&title[j]->mtx, &trans, &scale);
        }
    }

    if (current == GS_END)
    {
        AEVec2Set(&king.pos, campos.x, 375.0f);

        for (size_t k = 0; k < image.size(); ++k)
        {
            AEMtx33 trans, scale;
            AEVec2 pos = image[k]->pos;
            AEMtx33Scale(&scale, 200.0f, 200.0f);
            AEMtx33Trans(&trans, pos.x, pos.y);
            AEMtx33Concat(&image[k]->mtx, &trans, &scale);
        }
    }

    if (current == GS_LS)
    {
        AEVec2Set(&lvicon1.pos, 1170.0f, 200.0f);
        AEVec2Set(&lvicon2.pos, 450.0f, 560.0f);
        AEVec2Set(&lvicon3.pos, 1170.0f, 560.0f);
        AEVec2Set(&lvicon4.pos, 450.0f, 800.0f);
        AEVec2Set(&lvicon5.pos, 1170.0f, 800.0f);
        AEVec2Set(&lvicon6.pos, 210.0f, 200.0f);

        for (size_t l = 0; l < icon.size(); ++l)
        {
            AEMtx33 trans, scale;
            AEVec2 pos = icon[l]->pos;
            AEMtx33Scale(&scale, 100.0f, 50.0f);
            AEMtx33Trans(&trans, pos.x, pos.y);
            AEMtx33Concat(&icon[l]->mtx, &trans, &scale);
        }
    }
}

/***************************************************************************/
/*!
\brief
    This function loops through the entire vector that has the UI and draws
    it out on the screen. 4 of the UIs will display based on the player's
    progress on unlocking the color by reading the color.txt file. Hence 
    only by unlocking the color (e.g. Green), will the Green color UI 
    display on the screen. Else, it will not display.
*/
/**************************************************************************/
void UIManager::UIManagerDraw()
{
    for (size_t i = 0; i < parts.size(); ++i)
    {
        if (parts[i] == &aPart || parts[i] == &bPart || parts[i] == &cPart || parts[i] == &dPart)
        {
            std::ifstream colorfile;
            std::string line;

            colorfile.open("Resources/color.txt");
            if (colorfile.is_open())
            {
                while (getline(colorfile, line))
                {
                    size_t found;
                    if (parts[i] == &aPart && ((found = line.find("A")) != std::string::npos))
                    {
                        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
                        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
                        AEGfxSetTransparency(1.0f);
                        AEGfxSetTransform(parts[i]->mtx.m);
                        AEGfxTextureSet(parts[i]->rendTexture, 0, 0);
                        AEGfxMeshDraw(parts[i]->rendMesh, AE_GFX_MDM_TRIANGLES);
                    }
                    if (parts[i] == &bPart && ((found = line.find("B")) != std::string::npos))
                    {
                        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
                        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
                        AEGfxSetTransparency(1.0f);
                        AEGfxSetTransform(parts[i]->mtx.m);
                        AEGfxTextureSet(parts[i]->rendTexture, 0, 0);
                        AEGfxMeshDraw(parts[i]->rendMesh, AE_GFX_MDM_TRIANGLES);
                    }
                    if (parts[i] == &cPart && ((found = line.find("C")) != std::string::npos))
                    {
                        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
                        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
                        AEGfxSetTransparency(1.0f);
                        AEGfxSetTransform(parts[i]->mtx.m);
                        AEGfxTextureSet(parts[i]->rendTexture, 0, 0);
                        AEGfxMeshDraw(parts[i]->rendMesh, AE_GFX_MDM_TRIANGLES);
                    }
                    if (parts[i] == &dPart && ((found = line.find("D")) != std::string::npos))
                    {
                        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
                        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
                        AEGfxSetTransparency(1.0f);
                        AEGfxSetTransform(parts[i]->mtx.m);
                        AEGfxTextureSet(parts[i]->rendTexture, 0, 0);
                        AEGfxMeshDraw(parts[i]->rendMesh, AE_GFX_MDM_TRIANGLES);
                    }
                }
                colorfile.close();
            }
        }
        else
        {
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            AEGfxSetTransparency(1.0f);
            AEGfxSetTransform(parts[i]->mtx.m);
            AEGfxTextureSet(parts[i]->rendTexture, 0, 0);
            AEGfxMeshDraw(parts[i]->rendMesh, AE_GFX_MDM_TRIANGLES);
        }
        
    }

    if (current == GS_MAINMENU)
    {
        for (size_t j = 0; j < title.size(); ++j)
        {
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            AEGfxSetTransparency(1.0f);
            AEGfxSetTransform(title[j]->mtx.m);
            AEGfxTextureSet(title[j]->rendTexture, 0, 0);
            AEGfxMeshDraw(title[j]->rendMesh, AE_GFX_MDM_TRIANGLES);
        }
    }

    if (current == GS_END)
    {
        for (size_t k = 0; k < image.size(); ++k)
        {
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            AEGfxSetTransparency(1.0f);
            AEGfxSetTransform(image[k]->mtx.m);
            AEGfxTextureSet(image[k]->rendTexture, 0, 0);
            AEGfxMeshDraw(image[k]->rendMesh, AE_GFX_MDM_TRIANGLES);
        }
    }

    if (current == GS_LS)
    {
        for (size_t l = 0; l < icon.size(); ++l)
        {
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            AEGfxSetTransparency(1.0f);
            AEGfxSetTransform(icon[l]->mtx.m);
            AEGfxTextureSet(icon[l]->rendTexture, 0, 0);
            AEGfxMeshDraw(icon[l]->rendMesh, AE_GFX_MDM_TRIANGLES);
        }
    }
}

/***************************************************************************/
/*!
\brief
    This function unloads all the texture of the UI and frees the mesh that
    was stored in each UI.
*/
/**************************************************************************/
void UIManager::UIManagerUnload()
{
    AEGfxTextureUnload(aPart.rendTexture);
    AEGfxTextureUnload(bPart.rendTexture);
    AEGfxTextureUnload(cPart.rendTexture);
    AEGfxTextureUnload(dPart.rendTexture);
    AEGfxTextureUnload(up.rendTexture);
    AEGfxTextureUnload(down.rendTexture);
    AEGfxTextureUnload(left.rendTexture);
    AEGfxTextureUnload(right.rendTexture);
    AEGfxTextureUnload(ESC.rendTexture);
    AEGfxTextureUnload(Space.rendTexture);
    AEGfxTextureUnload(LShft.rendTexture);
    AEGfxTextureUnload(txtColor.rendTexture);
    AEGfxTextureUnload(txtPull.rendTexture);
    AEGfxTextureUnload(txtMain.rendTexture);
    AEGfxTextureUnload(txtMove.rendTexture);
    AEGfxTextureUnload(txtJump.rendTexture);

    if (current == GS_MAINMENU)
    {
        AEGfxTextureUnload(title1.rendTexture);
        AEGfxTextureUnload(title2.rendTexture);
    }

    if (current == GS_END)
    {
        AEGfxTextureUnload(king.rendTexture);
    }

    if (current == GS_LS)
    {
        AEGfxTextureUnload(lvicon1.rendTexture);
        AEGfxTextureUnload(lvicon2.rendTexture);
        AEGfxTextureUnload(lvicon3.rendTexture);
        AEGfxTextureUnload(lvicon4.rendTexture);
        AEGfxTextureUnload(lvicon5.rendTexture);
        AEGfxTextureUnload(lvicon6.rendTexture);
    }

    AEGfxMeshFree(normalMesh);
}