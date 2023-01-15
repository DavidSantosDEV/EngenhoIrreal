#include "OpenGLWrapper.h"
#include <glad/glad.h>
#include "Log.h"

void OpenGLWrapper::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
}

SDL_GLContext OpenGLWrapper::InitializeGLAD(struct SDL_Window* window)
{
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		LOG_ERROR("Failed to initialize GLAD");
	}

	return context;
}
