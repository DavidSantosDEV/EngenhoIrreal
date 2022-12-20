#pragma once
#include "Enemy.h"

enum class AsteroidType
{
	Small,
	Medium,
	Large
};

class StoneAsteroid : public Enemy
{
public:
	StoneAsteroid();
	StoneAsteroid(AsteroidType asteroidType);
	virtual void Update(float deltaTime) override;
	virtual void OnDestroyed() override;

	Vector2D m_MovementDirection = Vector2D::Down();

private:
	void SetupAsteroidData();
	AsteroidType m_AsteroidType;

public:
	void SetAsteroidType(AsteroidType type) { m_AsteroidType = type; Setup(); }
	AsteroidType GetAsteroidType() const { return m_AsteroidType; }
	const char* GetAsteroidTypeString()
	{
		switch (m_AsteroidType)
		{
		case AsteroidType::Small:
			return "Small";
			break;
		case AsteroidType::Medium:
			return "Medium";
			break;
		case AsteroidType::Large:
			return "Large";
			break;
		default:
			break;
		}
	}
};

