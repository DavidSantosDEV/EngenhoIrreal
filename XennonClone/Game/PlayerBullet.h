#pragma once
#include "GameObject.h"
#include "Transform.h"

class PlayerBullet : public GameObject
{
public:
	PlayerBullet();
	~PlayerBullet();
	virtual void Update(float deltaTime) override;

private:
	class AnimationComponent* m_AnimationComponent;
	float m_MoveSpeed = 200.f;
};

