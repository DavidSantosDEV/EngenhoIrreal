#include "AudioClip.h"
#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"

AudioClip::AudioClip()
{
	m_channel = -1;
	m_volume = 1;
	m_chunk = nullptr;
}

AudioClip::AudioClip(Mix_Chunk* chunk)
{
	m_chunk = chunk;
	m_channel = -1;
	m_volume = 1;
}

AudioClip::~AudioClip()
{
	if (m_chunk) {
		Mix_FreeChunk(m_chunk);
	}
}
