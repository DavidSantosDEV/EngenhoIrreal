#pragma once
#include <vector>
#include <memory>

class RenderComponent;
class GameObject;
class GameWorld;


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
	void Render();

	void AddGameObjectToStack(GameObject* gameObject);
	void RemoveObjectFromStack(GameObject* gameObject);


	

private:
	std::vector<GameObject*> m_GameObjectStack = {};
	std::vector<std::shared_ptr<RenderComponent>> m_RenderComponents = {};

	static GameWorld* m_World;
	class SDLWrapper* m_Sdl;
	class Window* m_Window;

	const int m_MaxFPS = 60;
	
	static float m_ElapsedMS;

public:
	static GameWorld* GetGameWorld() { return m_World; }

	static float GetDeltaTime() { return m_ElapsedMS; }
};

