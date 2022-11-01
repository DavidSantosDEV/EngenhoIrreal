#pragma once

class GameEngine
{
public:
	void Init(const char* windowTitle, int windowWidth, int windowHeight);
	void StartAndRun();

	void Start();
	void HandleInput(union SDL_Event& ev);
	void Update();
	void Render();

	~GameEngine();
private:
	class SDLWrapper* m_Sdl;
	class Window* m_Window;
};

