#include "GameRenderer.h"
#include "SDL.h"

GameRenderer::GameRenderer(SDL_Window* window, int index, bool bUseVSYNC)
{
	m_Renderer = SDL_CreateRenderer(window, index, bUseVSYNC ? SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC : 0);
}

GameRenderer::~GameRenderer()
{

}

void GameRenderer::CleanRender()
{
	SDL_RenderClear(m_Renderer);
}

void GameRenderer::RenderPresent()
{
	SDL_RenderPresent(m_Renderer);
}
