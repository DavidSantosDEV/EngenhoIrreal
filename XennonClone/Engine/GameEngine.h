#pragma once
#include <string>

class GameEngine
{
public:
	void Init(std::string windowTitle, int windowWidth, int windowHeight);
	void StartAndRun();

	void Start() {}
	void HandleInput(union SDL_Event& ev) {}
	void Update() {}
	void Render() {}

	~GameEngine();
private:
	class SDLWrapper* sdl;
	class Window* window;
};

