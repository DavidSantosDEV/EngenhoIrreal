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
#include "GameRenderer.h"
#include "Log.h"

// Initialize static variables
GameWorld* GameEngine::m_World = nullptr;
float GameEngine::m_ElapsedMS = 0.f;

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
}

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World)
{
	m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	m_Window = new Window(windowTitle, windowWidth, windowHeight);

	m_Renderer = new GameRenderer(m_Window->GetWindow(), -1, true);

	m_World = World;
}

void GameEngine::StartAndRun()
{
	Start();

	bool isRunning = true;
	SDL_Event ev;

	LOG("Engine start")
	while (isRunning)
	{
		Uint64 start = SDL_GetPerformanceCounter();
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
		
		Uint64 end = SDL_GetPerformanceCounter();
		m_ElapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		const long double CalcedTime = (double)(1000.f / m_MaxFPS);
		SDL_Delay(floor(abs(CalcedTime - m_ElapsedMS)));

		LOG("Calced: "<<CalcedTime)
		LOG("DeltaTime:" << m_ElapsedMS)
	}
}

void GameEngine::Start()
{
	LOG("Engine Start");

	m_World->Init(this);
	m_World->Start();

	for (int i = 0; i < m_GameObjectStack.size(); ++i) 
	{
		// If gameobject hasn't been initialized yet
		// GO created on world on compile time will have already been initialized
		if (m_GameObjectStack[i]->GetWasInitialized() == false)
		{
			m_GameObjectStack[i]->Start();
		}
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
	m_Renderer->CleanRender();
	for (int i = 0; i < m_RenderComponents.size(); ++i) 
	{
		m_RenderComponents[i]->Render(m_Renderer->GetRenderer());
	}
	m_Renderer->RenderPresent();
}

void GameEngine::AddGameObjectToStack(GameObject* gameObject)
{
	if (gameObject == nullptr) { return; }
	m_GameObjectStack.push_back(gameObject);
	//gameObject->Start();
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

