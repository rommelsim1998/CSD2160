/******************************************************************************
* \file			Main.cpp
* \brief		This file contains the main which is where the actual game loop
*				occurs.
*				state
* \author		Kyle Vincent Velasco Gatchalian, 100% Code Contribution
*
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
// ---------------------------------------------------------------------------
// includes

#include "GameStateManager.h"
#include "GameStateList.h"
#include "AEEngine.h"
#include "Test_Level.h"
#include "Main.h"
#include <iostream>
#include <memory>
#include "EntityManager.h"

// ---------------------------------------------------------------------------
// global variable
float g_dt;
//double	 g_appTime;
s8 font;
bool full_screen_me;
bool isPaused;
bool isOptionsEnabled;

// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#if de  fined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//int* pi = new int;

	//int gGameRunning = 1;


	// Creates the singleton instance once function is called.
	EntityManager::GetInstance();

	// Using custom window procedure
	//AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);
	AESysInit(hInstance, nCmdShow, 1600, 800, 0, 60, true, NULL);
	//font = AEGfxCreateFont("Resources/Arial Italic.ttf", 50.0f);
	font = AEGfxCreateFont("Resources/Arial Italic.ttf", 20);

	AEGfxSetBackgroundColor(1.0f, 1.0f, 0.5f);
	// Changing the window title
	AESysSetWindowTitle("Chroma!");

	// reset the system modules
	AESysReset();

	isPaused = false;
	isOptionsEnabled = false;
	full_screen_me = true;
	AEToogleFullScreen(full_screen_me);

	GSM_Initialize(GS_SPLASHSCREEN);

	// Game Loop
	while (current != GS_QUIT)
	{

		if (current == GS_RESTART)
		{
			// Set current and next states to previous (SINCE RESTART)
			current = previous;
			next = previous;

		}
		else
		{
			GSM_Update();
			fpLoad();
		}
		fpInitialize();
		///////////////////
		// Game loop update
		while (current == next)
		{
			// Informing the system about the loop's start
			AESysFrameStart();
			// Handling Input
			AEInputUpdate();
			// check if forcing the application to quit
			/*if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
				next = GS_QUIT;*/
			if (0 == AESysDoesWindowExist())
				next = GS_QUIT;

			fpUpdate();
			fpDraw();

			// Informing the system about the loop's end
			AESysFrameEnd();
			g_dt = (f32)AEFrameRateControllerGetFrameTime();

			if (g_dt > 0.01667f)
				g_dt = 0.01667f;
		}

		fpFree();

		if (next != GS_RESTART)
		{
			fpUnload();
		}

		// Sets the current state to previous and current to next;
		previous = current;
		current = next;
	}

	// Freeing the objects and textures

	AEGfxDestroyFont(font);
	// free the systems
	AESysExit();

	// THIS LINE OF CODE IS FOR TEST BRANCH
}