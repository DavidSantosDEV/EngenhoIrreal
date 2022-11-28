#pragma once
class AudioClip
{
protected:
	unsigned int m_channel = -1;
	float m_volume;
	struct Mix_Chunk* m_chunk;

public:
	AudioClip();
	AudioClip(Mix_Chunk* chunk);
	~AudioClip();

	void SetChannel(unsigned int channel) { m_channel = channel; }
	void SetVolume(float val) { m_volume = val; }

	float GetVolume() { return m_volume; }
	unsigned int GetChannel() { return m_channel; }
	Mix_Chunk* GetChunk() const { return m_chunk; }
};

