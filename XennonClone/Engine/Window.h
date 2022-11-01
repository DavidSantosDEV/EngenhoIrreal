#pragma once
class Window
{
public:
	Window(const char* title, int windowWidth, int windowHeight);
	~Window();

	void UpdateSurface();

private:
	struct SDL_Window* m_Window = nullptr;
public:
	struct SDL_Surface* GetSurface() const;
};

