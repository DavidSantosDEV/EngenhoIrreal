/*
* - Game Engine Core. Responsible for main execution loop and calling 
* - Update(), HandleEvents() and Renderer() functions from GameObjects and Components.
* - m_World is an exception which Start() and Upate() are called before any other GO
* - MUST be implemented by client
************************************************************/

#include <memory>
#include "GameEngine.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "Pawn.h"
#include "Log.h"
#include "TimerManager.h"
#include "Input.h"
#include "InstanceCounter.h"
#include "MathHelper.h"
#include "TextureManager.h"
#include "AudioSystem.h"
#include "SDL_audio.h"
#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "OpenGLWrapper.h"
#include "Sprite.h"
#include "FontLoader.h"

float triangleArea(Vector2D A, Vector2D B, Vector2D C);
bool isInsideSquare(Vector2D A, Vector2D B, Vector2D C, Vector2D D, Vector2D P);

// Initialize static variables
GameWorld* GameEngine::m_World = nullptr;
float GameEngine::m_ElapsedMS = 0.f;

bool GameEngine::s_IsUsingOpenGLRendering = false;  //NOT USED

std::vector<GameObject*> GameEngine::m_GameObjectStack;
std::vector<RenderComponent*> GameEngine::m_RenderComponentsStack;
std::vector<RenderComponent*> GameEngine::m_UIRenderStack;
std::vector<Pawn*> GameEngine::m_PawnsStack;

GameEngine* GameEngine::m_Instance{ nullptr };

GameEngine::~GameEngine()
{
	delete m_Window;
	delete m_Sdl;
	delete m_Input;
	delete m_PhysicsWorld;
	delete m_audioSystem;
}	

void GameEngine::Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World)
{
	if (m_Instance) {
		delete this;
	}
	else {
		m_Instance = this;
		m_Sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
		Renderer::s_ScreenWidth = windowWidth;
		Renderer::s_ScreenHeight = windowHeight;
		OpenGLWrapper::Init();
		m_Window = new Window(windowTitle, windowWidth, windowHeight, true);
		m_World = World;
		m_Input = new Input();
		m_PhysicsWorld = new PhysicsWorld();
		m_PhysicsWorld->Init();
		//m_audioSystem = new AudioSystem();
		//m_audioSystem->Init();
		m_FontLoader = new FontLoader();
		m_FontLoader->Init("font16x16.bmp");
	}
}

void GameEngine::StartAndRun()
{
	LOG("Engine start");

	bool isRunning = true;
	SDL_Event ev;
	const int lock = 1000 / m_MaxFPS;
	Uint32 mTicksCount = SDL_GetTicks();


	SDL_GLContext context = OpenGLWrapper::InitializeGLAD(m_Window->GetWindow());

	/* Assign the 32 texture channels with empty samplers */
	unsigned int shaderProgram = Shader::CreateProgramFromShaderPath("../Engine/shaders/Main.shader");
	auto textureUniformLocation = glGetUniformLocation(shaderProgram, "Textures");
	int samplers[32];
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}
	glUniform1iv(textureUniformLocation, 32, samplers);

	Renderer::Init();

	//SplashScreen();
	Start();

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
		
		PhysicsWorld::GetInstance()->ExecuteStashedEvents();

		m_PhysicsWorld->UpdatePhysics(m_ElapsedMS);

		Update();

		Render(shaderProgram);

		DestroyPending();

		//InstanceCounter::PrintCounts();
		//LOG("Elapsed : " << m_ElapsedMS);
		mTicksCount = SDL_GetTicks();
	}
	m_audioSystem->Clean();

	/*End game cleaning (memory leaks check) */
	InstanceCounter::PrintCounts();
	DestroyAll();
	InstanceCounter::PrintCounts();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(m_Window->GetWindow());

	Renderer::ShutDown();
	SDL_Quit();
}


//static std::mutex m_ObjMutex;
void GameEngine::DestroyPending()
{
	//std::lock_guard<std::mutex> lock(m_ObjMutex);
	if (m_PendingDestroy.size() > 0) {
		for (auto obj : m_PendingDestroy) {
			std::vector<std::shared_ptr<Component>> comps = obj->GetAllComponents();
			for (int i = 0; i < comps.size();++i) {
				//comps[i]->OnDestroyed();
				if (comps[i]) {
					comps[i]->OnDestroyed();
				}
				InstanceCounter::RemoveComponentCount(comps[i].get());
				InstanceCounter::PrintCounts();
			}
			obj->OnDestroyed();
			RemoveGameObjectFromStack(obj);
		}
		m_PendingDestroy.clear();
	}
}

void GameEngine::AddPendingDestroy(GameObject* obj)
{
	m_PendingDestroy.push_back(obj);
}

void GameEngine::DestroyAll()
{
	for (auto obj : m_GameObjectStack) {
		std::vector<std::shared_ptr<Component>> comps = obj->GetAllComponents();
		for (int i = 0; i < comps.size(); ++i) {
			if (comps[i]) {
				//comps[i]->OnDestroyed();
			}
			InstanceCounter::RemoveComponentCount(comps[i].get());
			InstanceCounter::PrintCounts();
		}
		//obj->OnDestroyed();
		RemoveGameObjectFromStack(obj);
	}
	m_GameObjectStack.clear();
}

void GameEngine::Start()
{
	m_World->Init(this);
	m_World->Start();
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

	/*
	Execute events here
	*/
	TimerManager::ExecuteHandles();
	m_World->Update(m_ElapsedMS);
	for (int i = 0; i < m_GameObjectStack.size();++i) 
	{
		if (m_GameObjectStack[i] != nullptr)
		{
			if (m_GameObjectStack[i]->GetIsEnabled()) {
				m_GameObjectStack[i]->Update(m_ElapsedMS);
				const std::vector<std::shared_ptr<Component>> comps = m_GameObjectStack[i]->GetAllComponents();
				for (auto cpt : comps) {
					cpt->Update(m_ElapsedMS);
				}
			}
		}
	}
}

void GameEngine::Render(unsigned int shaderProgramID)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	Renderer::BeginBatch();
	/**/
	for (auto mR : m_RenderComponentsStack)
	{
		Vector2D pos = mR->GetOwnerGameObject()->GetTransform()->GetPosition();
		Vector2D win = m_Window->GetWindowSize();
		if (isInsideSquare(Vector2D(-20, -20), Vector2D(win.x, -20), win, Vector2D(-20, win.y), pos)) {
			if (!mR->GetIsVisible()) {
				mR->SetIsVisible(true);
				mR->GetOwnerGameObject()->OnBecameVisible();
			}
		}
		else {
			if (mR->GetIsVisible()) {
				mR->SetIsVisible(false);
				mR->GetOwnerGameObject()->OnBecameHidden();
			}
		}
		if(mR->GetIsActive())
		mR->Render();
	}

	for (auto UIR : m_UIRenderStack) {
		Vector2D pos = UIR->GetOwnerGameObject()->GetTransform()->GetPosition();
		Vector2D win = m_Window->GetWindowSize();
		if (isInsideSquare(Vector2D(-20, -20), Vector2D(win.x, -20), win, Vector2D(-20, win.y), pos)) {
			if (!UIR->GetIsVisible()) {
				UIR->SetIsVisible(true);
				UIR->GetOwnerGameObject()->OnBecameVisible();
			}
		}
		else {
			if (UIR->GetIsVisible()) {
				UIR->SetIsVisible(false);
				UIR->GetOwnerGameObject()->OnBecameHidden();
			}
		}
		if (UIR->GetIsActive())
			UIR->Render();
	}

	Renderer::EndBatch();
	Renderer::Flush();
	SDL_GL_SwapWindow(m_Window->GetWindow());
	m_Window->Clean();
}

float triangleArea(Vector2D A,Vector2D B ,Vector2D C ){
	return (C.x * B.y - B.x * C.y) - (C.x * A.y - A.x * C.y) + (B.x * A.y - A.x * B.y);
}

 bool isInsideSquare(Vector2D A ,Vector2D B ,Vector2D C ,Vector2D D ,Vector2D P)
{
	if (triangleArea(A,B,P) > 0 || triangleArea(B,C,P) > 0 || triangleArea(C,D,P) > 0 || triangleArea(D,A,P) > 0) {
		return false;
	}
	return true;
}

bool IsInside(Vector2D windowConfines, Vector2D pos, float Leeway) {

	if (pos < windowConfines) {
		return true;
	}
	//lets try for now
	return false;
}


/*
void GameEngine::Render()
{
	m_Window->Clean();
	Vector2D win = m_Window->GetWindowSize();
	for (int i = 0; i < m_RenderComponentsStack.size();++i) {
		Vector2D pos = m_RenderComponentsStack[i]->GetOwnerGameObject()->GetTransform()->GetPosition();		
		if (isInsideSquare(Vector2D(-20, -20), Vector2D(win.x, -20), win, Vector2D(-20, win.y), pos)) {
			if (!m_RenderComponentsStack[i]->GetIsVisible()) {
				m_RenderComponentsStack[i]->SetIsVisible(true);
				m_RenderComponentsStack[i]->GetOwnerGameObject()->OnBecameVisible();
			}
		}
		else {
			if (m_RenderComponentsStack[i]->GetIsVisible()) {
				m_RenderComponentsStack[i]->SetIsVisible(false);
				m_RenderComponentsStack[i]->GetOwnerGameObject()->OnBecameHidden();
			}
		}
		m_RenderComponentsStack[i]->Render();
	}
	/*
	for (auto mR : m_RenderComponentsStack) 
	{
		Vector2D pos = mR->GetOwnerGameObject()->GetTransform()->GetPosition();
		Vector2D win = m_Window->GetWindowSize();
		if (isInsideSquare(Vector2D(-20,-20),Vector2D(win.x,-20),win,Vector2D(-20,win.y),pos)) {
			if (!mR->GetIsVisible()) {
				mR->SetIsVisible(true);
				mR->GetOwnerGameObject()->OnBecameVisible();
			}
		}
		else {
			if (mR->GetIsVisible()) {
				mR->SetIsVisible(false);
				mR->GetOwnerGameObject()->OnBecameHidden();
			}
		}
		mR->Render();
	}
	m_Window->UpdateRender();
}*/

void GameEngine::AddGameObjectToStack(GameObject* gameObject)
{
	if (gameObject == nullptr) { return; }
	m_GameObjectStack.push_back(gameObject);
	InstanceCounter::AddObjectCount(gameObject);
}

void GameEngine::RemoveGameObjectFromStack(GameObject* gameObject)
{
	for (int i = 0; i < m_GameObjectStack.size(); ++i) 
	{
		if (m_GameObjectStack[i] == gameObject)
		{
			InstanceCounter::RemoveObjectCount(gameObject);
			m_GameObjectStack.erase(m_GameObjectStack.begin()+i);
			
			return;
		}
	}
}

void GameEngine::AddRenderComponentToStack(RenderComponent* renderComponent)
{
	if (renderComponent == nullptr) { return; }
	if (renderComponent->GetIsUI()) {
		m_UIRenderStack.push_back(renderComponent);
	}
	else {
		m_RenderComponentsStack.push_back(renderComponent);
	}

	SortRenderComponents();
}

void GameEngine::RemoveRenderComponentFromStack(RenderComponent* renderComponent)
{
	if (renderComponent!=nullptr) {
		if (renderComponent->GetIsUI()) {
			for (int i = 0; i < m_UIRenderStack.size(); ++i)
			{
				if (m_UIRenderStack[i] == renderComponent)
				{
					m_UIRenderStack.erase(m_UIRenderStack.begin() + i);
					return;
				}
			}
		}
		else {
			for (int i = 0; i < m_RenderComponentsStack.size(); ++i)
			{
				if (m_RenderComponentsStack[i] == renderComponent)
				{
					m_RenderComponentsStack.erase(m_RenderComponentsStack.begin() + i);
					return;
				}
			}
		}
		SortRenderComponents();
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

void GameEngine::SplashScreen()
{
	SDL_Texture* text = TextureManager::LoadTexture("engenho.png");
	if (!text) {
		return;
	}

	SDL_Rect dest;
	dest.x = 10;
	dest.y = -50;
	dest.w = 600;
	dest.h = 500;
	Uint32 mTicksCount = SDL_GetTicks();

	//PlaySound
	//AudioClip audio = AudioSystem::CreateClip("engenho.wav");
	//AudioSystem::PlayClip(&audio, false);
	//
	float seconds = 0;
	const float wait = 2 * 1000;


	float alpha = 0;

	bool bCanContinue = false;

	float ms;

	bool bIsFinished = false;

	const int lock = 1000 / 20;

	while (!bIsFinished ) {
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + lock));
		ms = (SDL_GetTicks() - mTicksCount) / 1000.0f;

		alpha += (!bCanContinue ? 0.01f : -0.01f)*ms;
		alpha = MathHelper::Clamp01(alpha);
		if (alpha == 1 && !bCanContinue) {
			seconds += ms;
			if (seconds>=wait) {
				bCanContinue = true;
			}
		}
			
		bIsFinished = alpha == 0 && bCanContinue;
			

		SDL_SetTextureAlphaMod(text, 255*alpha);	
		SDL_RenderCopy(m_Window->GetRenderer(), text, NULL, &dest);
		m_Window->UpdateRender();
		m_Window->Clean();
	}
	SDL_DestroyTexture(text);
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




