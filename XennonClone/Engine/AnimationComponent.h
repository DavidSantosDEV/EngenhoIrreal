#pragma once
#include "Component.h"
#include "Transform.h"
class AnimationComponent : public Component
{
public:
	AnimationComponent(class Sprite* spriteComponent, bool autoPlayAnimation, float animationSpeed) :
		m_ParentSpriteComponent{ spriteComponent }, m_IsPlayingAnimation{autoPlayAnimation}, 
		m_AnimationSpeed{animationSpeed} {};

	virtual void Start() override;
	virtual void Update(float deltatime) override;

	/* Play animation from specific sprite sheet sprites. Index starts at 0 for both rows and columns 
	* Row = Y and Column = X.
	*/
	void PlayAnimation(int startingFrameRow, int startingFrameColumn, int endingFrameRow, 
		int endingFrameColumn, bool canLoopAnimation);

	bool IsPlayingAnimation(int startingFrameRow, int startingFrameColumn, int endingFrameRow,
		int endingFrameColumn) const;

	/* Called by other classes to stop the current animation. Is called inside play animation automatically */
	void StopAnimation() { m_IsPlayingAnimation = false; }
private:
	class Sprite* m_ParentSpriteComponent;
	float m_AnimationSpeed = 1.f;
	bool m_IsPlayingAnimation = false;

	int m_StartingAnimationFrameX = 0;
	int m_StartingAnimationFrameY = 0;
	int m_EndingAnimationFrameX = 0;
	int m_EndingAnimationFrameY = 0;
	bool m_CanLoopAnimation = true;
};

