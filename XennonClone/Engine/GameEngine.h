#pragma once
#include <vector>
#include <memory>

class RenderComponent;
class GameObject;
class GameWorld;

class GameEngine
{
	
protected:
	std::vector<GameObject*> m_GameObjectStack;
	std::vector<std::shared_ptr<RenderComponent>> m_RenderComponents = {};
public:
	void Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World);
	void StartAndRun();

	void Start();
	void HandleInput(union SDL_Event& ev);
	void Update();
	void Render();

	void AddGameObjectToStack(GameObject* newObject);
	void DeleteObject(GameObject* Object);
	
	static GameWorld* GetGameWorld() { return m_World; }

	~GameEngine();
private:

	static GameWorld* m_World;
	class SDLWrapper* m_Sdl;
	class Window* m_Window;
};

