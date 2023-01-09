#pragma once
#include "SDL.h"
#include <map>
#include <vector>
#include <string>

class RenderComponent;
/*
struct TextureAndComps {
	TextureAndComps() { texture = nullptr; }
	TextureAndComps(SDL_Texture* t, std::vector<RenderComponent*> c) {
		texture = t;
		components = c;
	}

	SDL_Texture* texture;
	std::vector<RenderComponent*> components;
};*/

class TextureManager {
	/*Todo,

	Sprites shouldnt be loaded everytime we need an object with it, so, lets make a map with the objects that have it,
	when it becomes 0, it unloads the sprite.
	*/

	/*static std::map<std::string, TextureAndComps> m_textureMap;*/

protected:
	static const char* m_BasePath;
protected:
	static std::string GetPathTranslated(const char* path);
public:
	static unsigned int LoadTextureOpenGL(const char* path, int* width, int* height);
	static SDL_Texture* LoadTexture(const char* Filename);
	/*
	static SDL_Texture* LoadTextureBind(const char* Filename, RenderComponent* comp);

	static void RemoveFromBind(SDL_Texture* text,RenderComponent* comp);
	*/
	static SDL_Texture* LoadTextureBMP(const char* Filename);

	static SDL_Surface* LoadSurface(const char* Filename);
};