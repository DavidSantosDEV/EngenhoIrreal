#pragma once
#include "SDL.h"

class TextureManager {

protected:
	static const char* m_BasePath;
protected:
	static const char* GetPathTranslated(const char* path);
public:
	static SDL_Texture* LoadTexture(const char* Filename);
	static SDL_Surface* LoadSurface(const char* Filename);
};