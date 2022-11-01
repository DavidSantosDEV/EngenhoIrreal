#pragma once

class GameEngine
{
public:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	void Init(const char* windowTitle, int windowWidth, int windowHeight);
=======
=======
>>>>>>> Stashed changes
	~GameEngine();

	void Init(const char* windowTitle, int windowWidth, int windowHeight, GameWorld* World);
>>>>>>> Stashed changes
	void StartAndRun();

	/* Engine Loop Events */
	void Start();
	void HandleInput(union SDL_Event& ev);
	void Update();
	void Render();

<<<<<<< Updated upstream
	~GameEngine();
private:
=======
	void AddGameObjectToStack(GameObject* newObject);
	void RemoveGameObjectFromStack(GameObject* Object);

private:
	std::vector<GameObject*> m_GameObjectStack = {};
	std::vector<std::shared_ptr<RenderComponent>> m_RenderComponents = {};

	static GameWorld* m_World;
>>>>>>> Stashed changes
	class SDLWrapper* m_Sdl;
	class Window* m_Window;

public:
	static GameWorld* GetGameWorld() { return m_World; }
};

