/*
* Window class- Responsible for everything related to SDL_Window()
************************************************************/

#include <SDL.h>
#include "Window.h"
#include "InitError.h"

Window::Window(const char* title, int windowWidth, int windowHeight)
{
	m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (m_Window == nullptr)
	{
		throw InitError();
	}
}

SDL_Surface* Window::GetSurface() const
{
	return SDL_GetWindowSurface(m_Window);
}

void Window::UpdateSurface()
{
	SDL_UpdateWindowSurface(m_Window);
}

Window::~Window()
{
	SDL_DestroyWindow(m_Window);
}
