#pragma once
#include "Transform.h"


class Window
{
public:
	Window(const char* title, int windowWidth, int windowHeight, bool bUseVSYNC);
	~Window();

	void UpdateRender();
	void Clean();

private:
	Vector2D m_StoredWindowSize;

	struct SDL_Window* m_Window = nullptr;
	struct SDL_Renderer* m_Renderer = nullptr;
public:
	struct SDL_Surface* GetSurface() const;
	SDL_Renderer* GetRenderer() const { return m_Renderer; }
	struct SDL_Window* GetWindow() const { return m_Window; }

	Vector2D GetWindowSize() { return m_StoredWindowSize; }
};

