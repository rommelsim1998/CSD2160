#ifndef GS_MANAGER_H
#define GS_MANAGER_H

/*!*************************************************************************
****
\file GameStateManager.h
\author Kyle Vincent Velasco Gatchalian
\par DP email: gatchaliankyle.v@digipen.edu
\brief
This .h file contains the function definitions for the Game State Manager.
These functions include :

- GSM_Initialize
    This function initializes the first game state _____ (INSERT HERE)

- GSM_Update
    This function updates the current game state
****************************************************************************
***/

typedef void(*FP)(void);

extern int current, previous, next;

extern FP fpLoad, fpInitialize, fpUpdate, fpDraw, fpFree, fpUnload;

void GSM_Initialize(int starting_state);
void GSM_Update();

#endif
