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

protected:
	static const char* m_BasePath;

	static void RemoveColor(unsigned char* pixels, int width, int height, unsigned char red, unsigned char green, unsigned char blue);
	
public:
	static std::string GetPathTranslated(const char* path);

	static TextureData LoadTextureOpenGL(const char* path);
	static SDL_Texture* LoadTexture(const char* Filename);

	static void FreeTexture(TextureData* texture);

	static SDL_Texture* LoadTextureBMP(const char* Filename);

	static SDL_Surface* LoadSurface(const char* Filename);
};