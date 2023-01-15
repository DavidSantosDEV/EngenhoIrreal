#pragma once
#include "SDL.h"
#include <map>
#include <vector>
#include <string>

struct TextureData
{
	/* Texture ID bound in OpenGL */
	unsigned int TextureID;
	int SheetWidth = 1;
	int SheetHeight = 1;
	TextureData() = default;
	TextureData(unsigned int textureID, int sheetWidth, int sheetHeight) : TextureID{ textureID }, SheetWidth{ sheetWidth }, SheetHeight{ sheetHeight } {};
};

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
	static TextureData LoadTextureOpenGL(const char* path);
	static SDL_Texture* LoadTexture(const char* Filename);

	static void FreeTexture(TextureData* texture);
	/*
	static SDL_Texture* LoadTextureBind(const char* Filename, RenderComponent* comp);

	static void RemoveFromBind(SDL_Texture* text,RenderComponent* comp);
	*/
	static SDL_Texture* LoadTextureBMP(const char* Filename);

	static SDL_Surface* LoadSurface(const char* Filename);
};