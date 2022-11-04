#pragma once
#include "SDL.h"

class TextureManager {

protected:
	const char* m_BasePath = "Assets/";
public:
	static SDL_Texture* LoadTexture(const char* Filename);

};