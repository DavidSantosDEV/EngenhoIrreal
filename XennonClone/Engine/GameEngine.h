#pragma once
#include <vector>
#include <memory>
#include "Transform.h"


class RenderComponent;
class GameObject;
class GameWorld;
class Pawn;
class PhysicsWorld;

class GameEngine
{
public:
	~GameEngine();
	void Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World);
	void StartAndRun();

	/* Engine Events */
	void Start();
	void HandleInput(union SDL_Event& ev);
	void Update();
	void Render(unsigned int shaderProgramID);

	void DestroyPending();
	void AddPendingDestroy(GameObject* obj);
	void DestroyAll();


	/* Object manipulation */
	static void AddGameObjectToStack(GameObject* gameObject);
	static void RemoveGameObjectFromStack(GameObject* gameObject);
	static void AddRenderComponentToStack(RenderComponent* renderComponent);
	static void RemoveRenderComponentFromStack(RenderComponent* renderComponent);
	static void AddPawnToStack(Pawn* pawn);
	static void RemovePawnFromStack(Pawn* pawn);

	static std::vector<GameObject*> GetAllGameObjects() { return m_GameObjectStack; }
	static bool s_IsUsingOpenGLRendering;

private:

	void SplashScreen();

	/* Sort render components in order to support a layering/priority system*/
	static void SwapRenderComponents(RenderComponent* r1, RenderComponent* r2);

	static GameEngine* m_Instance;

	PhysicsWorld* m_PhysicsWorld;

	std::vector<GameObject*> m_PendingDestroy;

	static std::vector<GameObject*> m_GameObjectStack;
	static std::vector<RenderComponent*> m_RenderComponentsStack;
	static std::vector<RenderComponent*> m_UIRenderStack;
	static std::vector<Pawn*> m_PawnsStack;

	static GameWorld* m_World;
	class SDLWrapper* m_Sdl;
	class AudioSystem* m_audioSystem;
	class Window* m_Window;
	class Input* m_Input;
	class FontLoader* m_FontLoader;

	const int m_MaxFPS = 120;
	static float m_ElapsedMS;

public:
	static void SortRenderComponents();

	static float GetDeltaTime() { return m_ElapsedMS; }

	static GameEngine* GetInstance() { return m_Instance; }

	struct SDL_Renderer* GetRenderer();

	class Window* GetWindow() { return m_Window; }

	Vector2D GetWindowSize();
	
	FontLoader* GetFontLoader() { return m_FontLoader; }

	PhysicsWorld* GetPhysicsWorld() { return m_PhysicsWorld; }
};

