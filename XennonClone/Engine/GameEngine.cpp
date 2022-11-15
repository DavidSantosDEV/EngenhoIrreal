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
#include "PhysicsWorld.h"
#include "Pawn.h"
#include "Log.h"
#include "Input.h"
#include <iostream>
#include <memory>

// Initialize static variables
GameWorld* GameEngine::m_World = nullptr;
float GameEngine::m_ElapsedMS = 0.f;

std::vector<GameObject*> GameEngine::m_GameObjectStack;
std::vector<RenderComponent*> GameEngine::m_RenderComponentsStack;
std::vector<Pawn*> GameEngine::m_PawnsStack;

GameEngine* GameEngine::m_Instance{ nullptr };

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
	delete m_Input;
	delete m_PhysicsWorld;
}	

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World)
{
	if (m_Instance) {
		delete this;
	}
	else {
		m_Instance = this;
		m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		m_Window = new Window(windowTitle, windowWidth, windowHeight, true);
		m_World = World;
		m_Input = new Input();
		m_PhysicsWorld = new PhysicsWorld();
		m_PhysicsWorld->Init();

	}
}

void GameEngine::StartAndRun()
{
	LOG("Engine start");

	Start();

	bool isRunning = true;
	SDL_Event ev;
	const int lock = 1000 / m_MaxFPS;
	Uint32 mTicksCount = SDL_GetTicks();
	while (isRunning)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + lock)); //Wait until ms passed

		m_ElapsedMS = (SDL_GetTicks() - mTicksCount) / 1000.0f;	

		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
		{
			isRunning = false;
		}
		else
		{
			HandleInput(ev);
		}
		m_PhysicsWorld->UpdatePhysics();
		Update();
		Render();

		mTicksCount = SDL_GetTicks();
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
	m_Input->ReceiveEvent(ev);

	for (int i = 0; i < m_PawnsStack.size();++i)
	{
		if (m_PawnsStack[i] != nullptr)
		{
			m_PawnsStack[i]->HandleEvents();
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
			const std::vector<std::shared_ptr<Component>> comps = m_GameObjectStack[i]->GetAllComponents();
			for (auto cpt : comps) {
				cpt->Update(m_ElapsedMS);
			}
		}
	}
}

void GameEngine::Render()
{
	m_Window->Clean();
	for (int i = 0; i < m_RenderComponentsStack.size(); ++i) 
	{
		m_RenderComponentsStack[i]->Render();
	}
	m_Window->UpdateRender();
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
	SortRenderComponents();
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
	SortRenderComponents();
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

SDL_Renderer* GameEngine::GetRenderer() 
{
	if (m_Window) {
		return m_Window->GetRenderer();
	}
	return nullptr;
}

Vector2D GameEngine::GetWindowSize() 
{
	return m_Window->GetWindowSize();
}


void GameEngine::SortRenderComponents()
{
	LOG_WARNING("Before sort first index: " << m_RenderComponentsStack[0]);

	for (unsigned int i = 0; i < m_RenderComponentsStack.size() - 1; ++i)
	{
		int lowestIndex = i;
		for (unsigned int j = i + 1; j < m_RenderComponentsStack.size(); ++j)
		{
			if (m_RenderComponentsStack[j]->GetRenderPriority() < 
				m_RenderComponentsStack[lowestIndex]->GetRenderPriority())
			{
				lowestIndex = j;
			}
		}

		if (i != lowestIndex)
		{
			std::swap(m_RenderComponentsStack[i], m_RenderComponentsStack[lowestIndex]);
		}
	}
	LOG_WARNING("After sort first index: " << m_RenderComponentsStack[0]);
}




