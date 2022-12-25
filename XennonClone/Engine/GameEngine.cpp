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
#include "RenderComponent.h"
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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
		m_Window = new Window(windowTitle, windowWidth, windowHeight, true);
		m_World = World;
		m_Input = new Input();
		m_PhysicsWorld = new PhysicsWorld();
		m_PhysicsWorld->Init();
		m_audioSystem = new AudioSystem();
		m_audioSystem->Init();
	}
}

void GameEngine::StartAndRun()
{

	LOG("Engine start");

	SDL_GLContext context = SDL_GL_CreateContext(m_Window->GetWindow());

	bool isRunning = true;
	SDL_Event ev;
	const int lock = 1000 / m_MaxFPS;
	Uint32 mTicksCount = SDL_GetTicks();


	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		LOG_ERROR("Failed to initialize GLAD");
		SDL_Quit();
	}

	float vertices[] = {
		0.5f, 0.5f, 1.f, 0.5f, 0.f,	// top right | R = 1, G = 0, B = 0
		0.5f, -0.5f, 0.5f, 1.f, 0.f,	// bottom right | R = 1, G = 0, B = 0
		-0.5f, -0.5f, 0.f, 1.f, 0.5f, // bottom left | R = 0, G = 1, B = 0
		-0.5f, 0.5f, 0.f, 0.5f, 1.f	// top left | R = 0, G = 1, B = 0
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma region VertexShader

	const char* vertexShaderSource = R"glsl(
	#version 330 core
	
	layout (location = 0) in vec2 position;
	layout (location = 1) in vec3 color;

	out vec3 Color;
	
	void main()
	{
		Color = color;
		gl_Position = vec4(position, 0.0, 1.0);
	}

	)glsl";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(m_Window->GetWindow());
		SDL_Quit();
	}

#pragma endregion

#pragma region FragmentShader

	const char* fragmentShaderSource = R"glsl(
	#version 330 core

	in vec3 Color;
	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.f);
	}

	)glsl";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl);
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(m_Window->GetWindow());
		SDL_Quit();
	}

#pragma endregion

#pragma region ShaderProgram
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		LOG_ERROR("ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog);
	}

	glUseProgram(shaderProgram);

#pragma endregion

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, false, 5 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));

	//SplashScreen();
	Start();

	while (true)
	{
		if (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT) break;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glClearColor(0.2f, 0.3f, 0.3f, 1.f);

		SDL_GL_SwapWindow(m_Window->GetWindow());
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(m_Window->GetWindow());

	SDL_Quit();

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

		DestroyPending();
		
		//InstanceCounter::PrintCounts();

		mTicksCount = SDL_GetTicks();
	}
	m_audioSystem->Clean();
	/*End game cleaning (memory leaks check) */
	InstanceCounter::PrintCounts();
	for (auto obj : m_GameObjectStack) {
		AddPendingDestroy(obj);
	}
	DestroyPending();
	InstanceCounter::PrintCounts();
}

void GameEngine::DestroyPending()
{
	if (m_PendingDestroy.size() > 0) {
		for (auto obj : m_PendingDestroy) {
			std::vector<std::shared_ptr<Component>> comps = obj->GetAllComponents();
			for (auto comp : comps) {
				comp->OnDestroyed();			
				delete comp.get();
				InstanceCounter::RemoveComponentCount();
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
	TimerManager::ExecuteHandles();
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

void GameEngine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	m_Window->Clean();



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
			InstanceCounter::RemoveObjectCount();
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




