#pragma once

#include <stdint.h>

struct SDL_Renderer;
struct SDL_Window;

class GameRenderer
{
	SDL_Renderer* m_Renderer;
public:
	GameRenderer(SDL_Window* window, int index, bool bUseVSYNC);
	~GameRenderer();

	void CleanRender();
	void RenderPresent();

	SDL_Renderer* GetRenderer() const { return m_Renderer; }
};

