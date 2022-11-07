#include "AnimationComponent.h"
#include "Sprite.h"
#include "SDL.h"
#include "Log.h"

float frameTime = 0;

void AnimationComponent::Update(float deltatime)
{
	//TODO don't get it every frame, get once and store it
	SDL_Rect& spriteSourceRect = m_ParentSpriteComponent.GetSourceRect();

	frameTime += deltatime;

	if (frameTime >= (1.f / m_AnimationSpeed))
	{
		spriteSourceRect.x += m_ParentSpriteComponent.m_FrameWidth;

		if (spriteSourceRect.x >= m_ParentSpriteComponent.m_TextureWidth)
		{
			spriteSourceRect.x = 0;
			spriteSourceRect.y += m_ParentSpriteComponent.m_FrameHeight;

			if (spriteSourceRect.y >= m_ParentSpriteComponent.m_TextureHeight)
			{
				spriteSourceRect.y = 0;
			}
		}

		frameTime = 0.f;
	}
}
