/******************************************************************************
* \file          Audiomanager.h
* \brief         This file declares Audio class
* \author        Tan Jian Jie, 100% Code Contribution

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
******************************************************************************/

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H


#include "fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>


class AudioManager {
private:
	/*===================================*
			Private - Data Members
	*====================================*/



public:

	 bool audio_on = true;
	 bool fmod_bool = true;
	 bool sfx_paused = false;
	 bool bgm_paused = false;
	 float bgvol = 1.0f;
	 float sevol = 1.0f;


	FMOD_RESULT* result = nullptr;
	//std::vector <FMOD_SOUND> soundList;

	 FMOD::System* system = NULL;
	 FMOD::Sound* sound = NULL;
	 FMOD::ChannelGroup* backgroundmusic = NULL;
	 FMOD::ChannelGroup* soundeffect = NULL;
	 FMOD::Channel* test = NULL;


	/*===================================*
				Constructors
	*====================================*/
	AudioManager() = default;
	~AudioManager() = default;

	/*===================================*
				Member Functions
	*====================================*/
	void AudioManagerLoad();
	void AudioManagerInitialize();
	void AudioManagerUpdate();
	void AudioManagerUnload();

	void playeffect(const char* filepath,FMOD::Sound* sound, FMOD::ChannelGroup* channelgroup, bool paused, FMOD::Channel** channel);




	/*===================================*
					Singleton
	*====================================*/
	// Singleton for using the same instance.
	// Since we are only making a single thread game, safe to use Singleton
	static AudioManager& GetInstance()
	{
		static AudioManager _instance;
		return _instance;
	}
	//static EntityManager& GetInstance();

	/*===================================*
			Deleted Cons and Ops
	*====================================*/
	// Delete Constructors and Operators below to make manager into Singleton.
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager& operator=(AudioManager&&) = delete;

};

#endif