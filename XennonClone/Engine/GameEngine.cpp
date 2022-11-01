/*
* Game Engine Core. Responsible for main execution loop and calling 
* Start(), Update(), HandleEvents() and Renderer() functions from GameObjects.
************************************************************/

#include "GameEngine.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "Window.h"

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight)
{
	m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	m_Window = new Window(windowTitle, windowWidth, windowHeight);
}

void GameEngine::StartAndRun()
{
	Start();

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else
			{
				HandleInput(ev);
			}
		}
		Update();
		Render();

		m_Window->UpdateSurface();
	}
}

void GameEngine::Start()
{

}

void GameEngine::HandleInput(union SDL_Event& ev)
{

}

void GameEngine::Update()
{

}

void GameEngine::Render()
{

}

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
}

