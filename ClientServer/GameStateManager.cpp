#include "main.h"
#include <iostream>

int current = 0, previous = 0, next = 0;

FP fpLoad = nullptr, fpInitialize = nullptr,
fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr,
fpUnload = nullptr;

// See if want to implement the managers into a class instead.

// With a defined constructor that has member initialisation list for current, etc..

void GSM_Initialize(int starting_state)
{
    current = starting_state;
    previous = starting_state;
    next = starting_state;
}

void GSM_Update()
{
	// Sets the function pointers to the current gamestate by the switch statement.
	switch (current)
	{
	case GS_CREDITS:
		fpLoad = GameStateCreditsLoad;
		fpInitialize = GameStateCreditsInit;
		fpUpdate = GameStateCreditsUpdate;
		fpDraw = GameStateCreditsDraw;
		fpFree = GameStateCreditsFree;
		fpUnload = GameStateCreditsUnload;
		break;

	case GS_SPLASHSCREEN:
		fpLoad = GameStateSplashScreenLoad;
		fpInitialize = GameStateSplashScreenInit;
		fpUpdate = GameStateSplashScreenUpdate;
		fpDraw = GameStateSplashScreenDraw;
		fpFree = GameStateSplashScreenFree;
		fpUnload = GameStateSplashScreenUnload;
		break;
	case GS_MAINMENU:
		fpLoad = GameStateMenuLoad;
		fpInitialize = GameStateMenuInit;
		fpUpdate = GameStateMenuUpdate;
		fpDraw = GameStateMenuDraw;
		fpFree = GameStateMenuFree;
		fpUnload = GameStateMenuUnload;
		break;
	case GS_TESTLEVEL:
		fpLoad = TestLevel_Load;
		fpInitialize = TestLevel_Initialize;
		fpUpdate = TestLevel_Update;
		fpDraw = TestLevel_Draw;
		fpFree = TestLevel_Free;
		fpUnload = TestLevel_Unload;
		break;
	case GS_LEVEL1:
		fpLoad = GameStateLevel1Load;
		fpInitialize = GameStateLevel1Init;
		fpUpdate = GameStateLevel1Update;
		fpDraw = GameStateLevel1Draw;
		fpFree = GameStateLevel1Free;
		fpUnload = GameStateLevel1Unload;
		break;
	case GS_LEVEL2:
		fpLoad = GameStateLevel2Load;
		fpInitialize = GameStateLevel2Init;
		fpUpdate = GameStateLevel2Update;
		fpDraw = GameStateLevel2Draw;
		fpFree = GameStateLevel2Free;
		fpUnload = GameStateLevel2Unload;
		break;
	case GS_LEVEL3:
		fpLoad = GameStateLevel3Load;
		fpInitialize = GameStateLevel3Init;
		fpUpdate = GameStateLevel3Update;
		fpDraw = GameStateLevel3Draw;
		fpFree = GameStateLevel3Free;
		fpUnload = GameStateLevel3Unload;
		break;
	case GS_LEVEL4:
		fpLoad = GameStateLevel4Load;
		fpInitialize = GameStateLevel4Init;
		fpUpdate = GameStateLevel4Update;
		fpDraw = GameStateLevel4Draw;
		fpFree = GameStateLevel4Free;
		fpUnload = GameStateLevel4Unload;
		break;
	case GS_LEVEL5:
		fpLoad = GameStateLevel5Load;
		fpInitialize = GameStateLevel5Init;
		fpUpdate = GameStateLevel5Update;
		fpDraw = GameStateLevel5Draw;
		fpFree = GameStateLevel5Free;
		fpUnload = GameStateLevel5Unload;
		break;
	case GS_LEVEL6:
		fpLoad = GameStateLevel6Load;
		fpInitialize = GameStateLevel6Init;
		fpUpdate = GameStateLevel6Update;
		fpDraw = GameStateLevel6Draw;
		fpFree = GameStateLevel6Free;
		fpUnload = GameStateLevel6Unload;
		break;
	case GS_LEVEL7:
		fpLoad = GameStateLevel7Load;
		fpInitialize = GameStateLevel7Init;
		fpUpdate = GameStateLevel7Update;
		fpDraw = GameStateLevel7Draw;
		fpFree = GameStateLevel7Free;
		fpUnload = GameStateLevel7Unload;
		break;
	case GS_LEVEL8:
		fpLoad = GameStateLevel8Load;
		fpInitialize = GameStateLevel8Init;
		fpUpdate = GameStateLevel8Update;
		fpDraw = GameStateLevel8Draw;
		fpFree = GameStateLevel8Free;
		fpUnload = GameStateLevel8Unload;
		break;
	case GS_LS:
		fpLoad = GameStateLSLoad;
		fpInitialize = GameStateLSInit;
		fpUpdate = GameStateLSUpdate;
		fpDraw = GameStateLSDraw;
		fpFree = GameStateLSFree;
		fpUnload = GameStateLSUnload;
		break;
	case GS_CONNECTION:
		fpLoad = GameStateLevelconnectLoad;
		fpInitialize = GameStateLevelconnectInit;
		fpUpdate = GameStateLevelconnectUpdate;
		fpDraw = GameStateLevelconnectDraw;
		fpFree = GameStateLevelconnectFree;
		fpUnload = GameStateLevelconnectUnload;
		break;
		/*
	case GS_MLEVEL1:
		fpLoad = GameStateMLevel1Load;
		fpInitialize = GameStateMLevel1Init;
		fpUpdate = GameStateMLevel1Update;
		fpDraw = GameStateMLevel1Draw;
		fpFree = GameStateMLevel1Free;
		fpUnload = GameStateMLevel1unload;
		break;
	case GS_MLEVEL2:
		fpLoad = GameStateMLevel2Load;
		fpInitialize = GameStateMLevel2Init;
		fpUpdate = GameStateMLevel2Update;
		fpDraw = GameStateMLevel2Draw;
		fpFree = GameStateMLevel12Free;
		fpUnload = GameStateMLevel2unload;
		break;
	case GS_MLEVEL3:
		fpLoad = GameStateMLevel3Load;
		fpInitialize = GameStateMLevel3Init;
		fpUpdate = GameStateMLevel3Update;
		fpDraw = GameStateMLevel3Draw;
		fpFree = GameStateMLevel3Free;
		fpUnload = GameStateMLevel3unload;
		break;
	case GS_MLEVEL4:
		fpLoad = GameStateMLevel4Load;
		fpInitialize = GameStateMLevel4Init;
		fpUpdate = GameStateMLevel4Update;
		fpDraw = GameStateMLevel4Draw;
		fpFree = GameStateMLevel4Free;
		fpUnload = GameStateMLevel4unload;
		break;
		*/
	case GS_EXTRA:
		fpLoad = GameStateExtraLoad;
		fpInitialize = GameStateExtraInit;
		fpUpdate = GameStateExtraUpdate;
		fpDraw = GameStateExtraDraw;
		fpFree = GameStateExtraFree;
		fpUnload = GameStateExtraUnload;
		break;
	case GS_END:
		fpLoad = GameStateEndLoad;
		fpInitialize = GameStateEndInit;
		fpUpdate = GameStateEndUpdate;
		fpDraw = GameStateEndDraw;
		fpFree = GameStateEndFree;
		fpUnload = GameStateEndUnload;
		break;
	case GS_RESTART:
		break;
	case GS_QUIT:
		break;
	}

	// Prints out to the system to simulate gamestatemanager update.
}
