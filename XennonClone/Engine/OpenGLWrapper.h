#pragma once

#include <SDL.h>

class OpenGLWrapper
{
public:
	static void Init();
	static SDL_GLContext InitializeGLAD(struct SDL_Window* window);
};

