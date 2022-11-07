#include "AnimationComponent.h"
#include "Sprite.h"
#include "SDL.h"
#include "Log.h"

float frameTime = 0;

void AnimationComponent::Start()
{
	// If user chose to auto play animation on start
	if (m_IsPlayingAnimation)
	{
		m_StartingAnimationFrameX = 0;
		m_StartingAnimationFrameY = 0;
		m_EndingAnimationFrameX = m_ParentSpriteComponent.m_TextureWidth;
		m_EndingAnimationFrameY = m_ParentSpriteComponent.m_TextureHeight;
	}
}

void AnimationComponent::Update(float deltatime)
{
	if (m_IsPlayingAnimation == false) 
	{
		frameTime = 0;
		return; 
	}

	//TODO don't get it every frame, get once and store it
	SDL_Rect& spriteSourceRect = m_ParentSpriteComponent.GetSourceRect();

	frameTime += deltatime;

	if (frameTime >= (1.f / m_AnimationSpeed))
	{
		spriteSourceRect.x += m_ParentSpriteComponent.m_FrameWidth;

		if (spriteSourceRect.x >= m_EndingAnimationFrameX)
		{
			spriteSourceRect.x = m_StartingAnimationFrameX;
			spriteSourceRect.y += m_ParentSpriteComponent.m_FrameHeight;

			if (spriteSourceRect.y >= m_EndingAnimationFrameY)
			{
				spriteSourceRect.y = m_StartingAnimationFrameY;
			}
		}

		frameTime = 0.f;
	}
}

void AnimationComponent::PlayAnimation(int startingFrameRow, int startingFrameColumn, int endingFrameRow, int endingFrameColumn)
{
	// Update animation values
	m_StartingAnimationFrameX = startingFrameColumn * m_ParentSpriteComponent.m_FrameWidth;
	m_StartingAnimationFrameY = startingFrameRow * m_ParentSpriteComponent.m_FrameHeight;
	m_EndingAnimationFrameX = (endingFrameColumn * m_ParentSpriteComponent.m_FrameWidth) + m_ParentSpriteComponent.m_FrameWidth;
	m_EndingAnimationFrameY = (endingFrameRow * m_ParentSpriteComponent.m_FrameHeight) + m_ParentSpriteComponent.m_FrameHeight;

	// Change whatever sprite it is currently to the first of the new animation.
	SDL_Rect& spriteSourceRect = m_ParentSpriteComponent.GetSourceRect();
	spriteSourceRect.x = m_StartingAnimationFrameX;
	spriteSourceRect.y = m_StartingAnimationFrameY;

	m_IsPlayingAnimation = true;
}
