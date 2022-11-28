#include "AudioSystem.h"
#include "SDL_mixer.h"
//#include "AudioClip.h"


#define BASEPATH "../Assets/";

std::string AudioSystem::GetPathTranslated(const char* path)
{
	std::string fullPath = BASEPATH;
	fullPath += path;
	return fullPath;
}

void AudioSystem::Init()
{
	Mix_OpenAudio(m_frequency, MIX_DEFAULT_FORMAT, m_channels, m_chunkSize);
}

void AudioSystem::Clean()
{
	Mix_CloseAudio();
}

AudioClip& AudioSystem::CreateClip(std::string path)
{
	std::string ba = GetPathTranslated(path.c_str());
	Mix_Chunk* chunk = Mix_LoadWAV(ba.c_str());
	if (chunk) {
		AudioClip clip = AudioClip(chunk);
		return clip;
	}
}

void AudioSystem::PlayClip(AudioClip* clip, bool bLoop)
{
	if(clip)
	Mix_PlayChannel(clip->GetChannel(), clip->GetChunk(), bLoop ? -1 : 0);
}
