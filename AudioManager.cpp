/******************************************************************************
* \file          AudioManager.cpp
* \brief         This file Defines all the main audio functions
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/
#include "Main.h"
#include <iostream>
#include "AudioManager.h"
#include <fmod.hpp>




/*===================================*
			Audio Man Load
*====================================*/
void AudioManager::AudioManagerLoad()
{
	FMOD_RESULT res = FMOD::System_Create(&system);      // Create the main system object.
	result = &res;      // Create the main system object.
	if (*result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result);
		exit(-1);
	}
	

	res = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	result = &res;


	//create channel group
	res = system->createChannelGroup("bgsound", &backgroundmusic);
	result = &res;

	//create channel group
	res = system->createChannelGroup("soundeffect", &soundeffect);
	result = &res;



	if (current == GS_MAINMENU)
	{
		//create sound
		res = system->createSound("Resources/menu.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// LEVEL SELECT MUSIC
	if (current == GS_LS)
	{
		//create sound
		res = system->createSound("Resources/ls.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// LEVEL 1 MUSIC
	if (current == GS_LEVEL1)
	{
		//create sound
		res = system->createSound("Resources/level1.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// LEVEL 2 MUSIC
	if (current == GS_LEVEL2)
	{
		//create sound
		res = system->createSound("Resources/level2.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}


	// LEVEL 3 MUSIC
	if (current == GS_LEVEL3)
	{
		//create sound
		res = system->createSound("Resources/level3.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// LEVEL 4 MUSIC
	if (current == GS_LEVEL4)
	{
		//create sound
		res = system->createSound("Resources/level4.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// LEVEL 5 MUSIC
	if (current == GS_LEVEL5)
	{
		//create sound
		res = system->createSound("Resources/level5.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}
	// LEVEL 6 MUSIC
	if (current == GS_LEVEL6)
	{
		//create sound
		res = system->createSound("Resources/level6.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}
	// LEVEL 7 MUSIC
	if (current == GS_LEVEL7)
	{
		//create sound
		res = system->createSound("Resources/level7.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}
	// LEVEL 8 MUSIC
	if (current == GS_LEVEL8)
	{
		//create sound
		res = system->createSound("Resources/level8.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;

		sound->setMode(FMOD_LOOP_NORMAL);

		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);

	}

	// ENDGAME MUSIC
	if (current == GS_END)
	{
		//create sound
		res = system->createSound("Resources/end.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;
	
		sound->setMode(FMOD_LOOP_NORMAL);
	
		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);
	
	}
	
	// EXTRA
	if (current == GS_EXTRA)
	{
		//create sound
		res = system->createSound("Resources/extra.ogg", FMOD_CREATESAMPLE, 0, &sound);
		result = &res;
	
		sound->setMode(FMOD_LOOP_NORMAL);
	
		//play sound
		system->playSound(sound, backgroundmusic, bgm_paused, &test);
	
	}

	

}




void AudioManager::playeffect(const char* filepath ,FMOD::Sound* theSound, FMOD::ChannelGroup* channelgroup, bool paused, FMOD::Channel** theChannel)
{
	//result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	//AudioManagerLoad();
	//create sound
	if (theChannel) {}
	if (paused) {}
	FMOD_RESULT res = system->createSound(filepath, FMOD_CREATESAMPLE, 0, &theSound);
	result = &res;
	
	system->playSound(theSound, channelgroup, bgm_paused, &test);
	

}


/*===================================*
		Audio Man Initialize
*====================================*/
void AudioManager::AudioManagerInitialize()
{

	

	

}


void AudioManager::AudioManagerUpdate()
{
	

	if (AEInputCheckTriggered(AEVK_EQUAL))
	{
		if (bgvol > 1.0f)
		{
			bgvol = 1.0f;
			sevol = 1.0f;
			backgroundmusic->setVolume(bgvol);
			soundeffect->setVolume(sevol);
		}
		else
		{
			bgvol = bgvol + 0.10f;
			sevol = sevol + 0.10f;
			backgroundmusic->setVolume(bgvol);
			soundeffect->setVolume(sevol);
		}
	
	}
	if (AEInputCheckTriggered(AEVK_MINUS))
	{
		if (bgvol < 0.10f)
		{
			bgvol = 0.10f;
			sevol = 0.10f;
			backgroundmusic->setVolume(bgvol);
			soundeffect->setVolume(sevol);
		}
		else
		{
			bgvol = bgvol - 0.10f;
			backgroundmusic->setVolume(bgvol);
			soundeffect->setVolume(sevol);
		}
	}


	backgroundmusic->setVolume(bgvol);
	soundeffect->setVolume(sevol);

	system->update();

}







/*===================================*
			Audio Man Unload
*====================================*/
void AudioManager::AudioManagerUnload()
{
	system->release();
}
