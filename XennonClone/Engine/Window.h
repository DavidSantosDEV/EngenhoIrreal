#pragma once
class Window
{
public:
	Window(const char* title, int windowWidth, int windowHeight, bool bUseVSYNC);
	~Window();

	void UpdateRender();
	void Clean();

private:
	struct SDL_Window* m_Window = nullptr;
	struct SDL_Renderer* m_Renderer = nullptr;
public:
	struct SDL_Surface* GetSurface() const;
	SDL_Renderer* GetRenderer() const { return m_Renderer; }
};

