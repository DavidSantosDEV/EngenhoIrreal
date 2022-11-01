/*
* - Game Engine Core. Responsible for main execution loop and calling 
* Start(), Update(), HandleEvents() and Renderer() functions from GameObjects.
* - m_World is an exception which Start() and Upate() are called before any other GO
*
* - MUST be implemented by client
************************************************************/

#include "GameEngine.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "RenderComponent.h"

// Initialize static variables
GameWorld* GameEngine::m_World = nullptr;

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
	delete m_World;
}

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
	for (int i = 0; i < m_GameObjectStack.size(); ++i) 
	{
		m_GameObjectStack[i]->Start();
	}
}

void GameEngine::HandleInput(union SDL_Event& ev)
{

}

void GameEngine::Update()
{
	m_World->Update();
	for (int i = 0; i < m_GameObjectStack.size();++i) 
	{
		if (m_GameObjectStack[i] != nullptr)
		{
			m_GameObjectStack[i]->Update();
		}
	}
}

void GameEngine::Render()
{
	for (int i = 0; i < m_RenderComponents.size(); ++i) 
	{
		m_RenderComponents[i]->Render();
	}
}

void GameEngine::AddGameObjectToStack(GameObject* gameObject)
{
	if (gameObject == nullptr) { return; }
	m_GameObjectStack.push_back(gameObject);
}

void GameEngine::RemoveObjectFromStack(GameObject* gameObject)
{
	for (int i = 0; i < m_GameObjectStack.size(); ++i) 
	{
		if (m_GameObjectStack[i] == gameObject)
		{
			m_GameObjectStack.erase(m_GameObjectStack.begin()+i);
			return;
		}
	}
}

