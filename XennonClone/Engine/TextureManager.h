#pragma once
#include "SDL.h"
#include <string>

class TextureManager {

protected:
	static const char* m_BasePath;
protected:
	static std::string GetPathTranslated(const char* path);
public:
	static SDL_Texture* LoadTexture(const char* Filename);
	static SDL_Texture* LoadTextureBMP(const char* Filename);

	static SDL_Surface* LoadSurface(const char* Filename);
};