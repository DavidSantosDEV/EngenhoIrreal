/*
* Game Engine Core. Responsible for main execution loop and calling 
* Start(), Update(), HandleEvents() and Renderer() functions from GameObjects.
************************************************************/

#include "GameEngine.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "Window.h"

#include "GameWorld.h"
#include "GameObject.h"
#include "RenderComponent.h"

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World)
{
	m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	m_Window = new Window(windowTitle, windowWidth, windowHeight);
	m_World = World;
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
	m_World->Init(this);
	m_World->Start();
	for (int i = 0; i < m_GameObjectStack.size(); ++i) {
		m_GameObjectStack[i]->Start();
	}
}

void GameEngine::HandleInput(union SDL_Event& ev)
{

}

void GameEngine::AddGameObjectToStack(GameObject* newObject)
{
	if (!newObject) {
		return;
	}
	for (int i = 0; i < m_GameObjectStack.size(); ++i) {
		if (m_GameObjectStack[i] == newObject) {
			return;
		}
	}
	m_GameObjectStack.push_back(newObject);
	//newObject->Start();
}

void GameEngine::Update()
{
	m_World->Update();
	for (int i = 0; i < m_GameObjectStack.size();++i) {
		m_GameObjectStack[i]->Update();
	}
}

void GameEngine::Render()
{
	for (int i = 0; i < m_RenderComponents.size(); ++i) {
		m_RenderComponents[i]->Render();
	}
}

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
}

