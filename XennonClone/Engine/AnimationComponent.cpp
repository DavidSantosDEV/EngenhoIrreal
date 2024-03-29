/*
* - Animation Component. Responsible for playing animations base on spritesheet
* Supports auto animations and playing animations from specific rows and columns.
* 
*  - GameObject MUST have SpriteComponent for this component to work
************************************************************/

#include "AnimationComponent.h"
#include "Sprite.h"
#include "SDL.h"
#include "Log.h"
#include "GameObject.h"

void AnimationComponent::Start()
{
	/*
	if (m_ParentSpriteComponent->GetTexture() == nullptr)
	{
		LOG_ERROR("AnimationComponent only works if GO also has a SpriteComponent");
	}*/
	// If user chose to auto play animation on start
	if (m_IsPlayingAnimation)
	{
		m_StartingAnimationFrameX = 0;
		m_StartingAnimationFrameY = 0;
		m_EndingAnimationFrameX = m_ParentSpriteComponent->m_SheetWidth;
		m_EndingAnimationFrameY = m_ParentSpriteComponent->m_SheetHeight;
	}
}

void AnimationComponent::Update(float deltatime)
{
	if (m_IsPlayingAnimation == false) 
	{
		frameTime = 0;
		return; 
	}

	// TODO don't get it every frame, get once and store it
	SDL_Rect& spriteSourceRect = m_ParentSpriteComponent->GetSourceRect();

	frameTime += deltatime;

	if (frameTime >= (1.f / m_AnimationSpeed))
	{
		spriteSourceRect.x += m_ParentSpriteComponent->m_FrameWidth;

		if (spriteSourceRect.x >= m_EndingAnimationFrameX)
		{

			float nextSourceRectY = spriteSourceRect.y + m_ParentSpriteComponent->m_FrameHeight;

			if (m_CanLoopAnimation)
			{
				spriteSourceRect.x = m_StartingAnimationFrameX;
			}
			else
			{
				if (nextSourceRectY < m_EndingAnimationFrameY)
				{
					spriteSourceRect.x = m_StartingAnimationFrameX;
				}
				// If animation is not loopable, when it reaches the end, stay in the beginning of the last frame.
				else
				{
					spriteSourceRect.x = m_EndingAnimationFrameX - m_ParentSpriteComponent->m_FrameWidth;
					OnAnimationEnded.Broadcast();
					//m_OwnerGameObject->OnAnimationEnd();
				}
			}

			spriteSourceRect.y = nextSourceRectY;
			
			if (spriteSourceRect.y >= m_EndingAnimationFrameY)
			{
				spriteSourceRect.y = m_CanLoopAnimation ? m_StartingAnimationFrameY : m_EndingAnimationFrameY - m_ParentSpriteComponent->m_FrameHeight;
			}
		}

		frameTime = 0.f;
	}
}

void AnimationComponent::PlayAnimation(int startingFrameRow, int startingFrameColumn, int endingFrameRow, int endingFrameColumn, bool canLoopAnimation)
{
	StopAnimation();

	// Update animation values
	m_StartingAnimationFrameX = startingFrameColumn * m_ParentSpriteComponent->m_FrameWidth;
	m_StartingAnimationFrameY = startingFrameRow * m_ParentSpriteComponent->m_FrameHeight;
	// + m_ParentSpriteComponent.m_FrameWidth since the end of the frame it's its column + frame width.
	m_EndingAnimationFrameX = (endingFrameColumn * m_ParentSpriteComponent->m_FrameWidth) + m_ParentSpriteComponent->m_FrameWidth;
	// + m_ParentSpriteComponent.m_FrameHeight since the end of the frame it's its row + frame height.
	m_EndingAnimationFrameY = (endingFrameRow * m_ParentSpriteComponent->m_FrameHeight) + m_ParentSpriteComponent->m_FrameHeight;

	// Change whatever sprite it is currently to the first of the new animation.
	SDL_Rect& spriteSourceRect = m_ParentSpriteComponent->GetSourceRect();
	spriteSourceRect.x = m_StartingAnimationFrameX;
	spriteSourceRect.y = m_StartingAnimationFrameY;

	m_IsPlayingAnimation = true;
	m_CanLoopAnimation = canLoopAnimation;
}

bool AnimationComponent::IsPlayingAnimation(int startingFrameRow, int startingFrameColumn, int endingFrameRow, int endingFrameColumn) const
{
	return m_StartingAnimationFrameX == startingFrameColumn * m_ParentSpriteComponent->m_FrameWidth &&
		m_StartingAnimationFrameY == startingFrameRow * m_ParentSpriteComponent->m_FrameHeight &&
		m_EndingAnimationFrameX == (endingFrameColumn * m_ParentSpriteComponent->m_FrameWidth) + m_ParentSpriteComponent->m_FrameWidth &&
		m_EndingAnimationFrameY == (endingFrameRow * m_ParentSpriteComponent->m_FrameHeight) + m_ParentSpriteComponent->m_FrameHeight;
}
