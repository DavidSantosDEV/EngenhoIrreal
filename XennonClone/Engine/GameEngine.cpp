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
#include "Pawn.h"
#include "Log.h"

// Initialize static variables
GameWorld* GameEngine::m_World = nullptr;
float GameEngine::m_ElapsedMS = 0.f;
std::vector<GameObject*> GameEngine::m_GameObjectStack;
std::vector<RenderComponent*> GameEngine::m_RenderComponentsStack;
std::vector<Pawn*> GameEngine::m_PawnsStack;

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
}

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World)
{
	m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	m_Window = new Window(windowTitle, windowWidth, windowHeight);
	m_World = World;
}

void GameEngine::StartAndRun()
{
	LOG("Engine start");

	Start();

	bool isRunning = true;
	SDL_Event ev;

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
	}
}

void GameEngine::Start()
{
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

void GameEngine::HandleInput(SDL_Event& ev)
{
	for (int i = 0; i < m_PawnsStack.size();++i)
	{
		if (m_PawnsStack[i] != nullptr)
		{
			m_PawnsStack[i]->HandleEvents(ev);
		}
	}
}

void GameEngine::Update()
{
	m_World->Update(m_ElapsedMS);
	for (int i = 0; i < m_GameObjectStack.size();++i) 
	{
		if (m_GameObjectStack[i] != nullptr)
		{
			m_GameObjectStack[i]->Update(m_ElapsedMS);
		}
	}
}

void GameEngine::Render()
{
	for (int i = 0; i < m_RenderComponentsStack.size(); ++i) 
	{
		m_RenderComponentsStack[i]->Render();
	}
}

void GameEngine::AddGameObjectToStack(GameObject* gameObject)
{
	if (gameObject == nullptr) { return; }
	m_GameObjectStack.push_back(gameObject);
}

void GameEngine::RemoveGameObjectFromStack(GameObject* gameObject)
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

void GameEngine::AddRenderComponentToStack(RenderComponent* renderComponent)
{
	if (renderComponent == nullptr) { return; }
	m_RenderComponentsStack.push_back(renderComponent);
}

void GameEngine::RemoveRenderComponentFromStack(RenderComponent* renderComponent)
{
	for (int i = 0; i < m_RenderComponentsStack.size(); ++i)
	{
		if (m_RenderComponentsStack[i] == renderComponent)
		{
			m_RenderComponentsStack.erase(m_RenderComponentsStack.begin() + i);
			return;
		}
	}
}

void GameEngine::AddPawnToStack(Pawn* pawn)
{
	if (pawn == nullptr) { return; }
	m_PawnsStack.push_back(pawn);
}

void GameEngine::RemovePawnFromStack(Pawn* pawn)
{
	for (int i = 0; i < m_PawnsStack.size(); ++i)
	{
		if (m_PawnsStack[i] == pawn)
		{
			m_PawnsStack.erase(m_PawnsStack.begin() + i);
			return;
		}
	}
}

