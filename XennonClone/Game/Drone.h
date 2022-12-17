#pragma once
#include "Enemy.h"

struct SineMovementData
{
	float ticksCounter = 0;
	float sineSpeed = 5.f;
	float sineAmplitude = 1.f;

	SineMovementData() = default;
	SineMovementData(float speed, float amplitude) : sineSpeed{speed}, sineAmplitude{amplitude} {};
};

class Drone : public Enemy
{
public:
	Drone();

	// Going down and a bit to the right
	Vector2D m_MoveDirection = Vector2D(0.1f, 1.f);

	SineMovementData m_SineMovementData;


	virtual void Update(float deltaTime);
};

