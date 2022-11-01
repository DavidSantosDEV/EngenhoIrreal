/*
* Generic Component
************************************************************/

#include "Pawn.h"
#include "SDL.h"
#include "Log.h"

void Pawn::HandleEvents(SDL_Event& ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		LOG_WARNING("Key down");
	}
}
