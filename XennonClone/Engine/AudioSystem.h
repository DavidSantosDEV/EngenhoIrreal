#pragma once

#include <string>
#include "AudioClip.h"
/*

This is just to add, not gonna make anything fancy yet.
REDO LATER

*/


class AudioSystem
{
private:

	const unsigned int m_frequency = 44100;
	const unsigned int m_chunkSize = 2048;
	const unsigned short m_channels = 2;

	static std::string GetPathTranslated(const char* path);

public:

	void Init();
	void Clean();
	static AudioClip& CreateClip(std::string path);
	static void PlayClip(AudioClip* clip, bool bLoop);
};

