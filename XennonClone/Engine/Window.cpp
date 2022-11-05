/*
* Window class- Responsible for everything related to SDL_Window()
************************************************************/

#include <SDL.h>
#include "Window.h"
#include "InitError.h"

Window::Window(const char* title, int windowWidth, int windowHeight, bool bUseVSYNC)
{
	m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (m_Window == nullptr)
	{
		throw InitError();
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, bUseVSYNC ? SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC : 0);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
	if (!m_Renderer) {
		throw InitError();
	}
}

SDL_Surface* Window::GetSurface() const
{
	return SDL_GetWindowSurface(m_Window);
}

void Window::UpdateRender()
{
	SDL_RenderPresent(m_Renderer);
}

void Window::Clean() {
	SDL_RenderClear(m_Renderer);
}

Window::~Window()
{
	SDL_DestroyWindow(m_Window);
}
