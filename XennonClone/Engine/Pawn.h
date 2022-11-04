#pragma once
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	Pawn();
	~Pawn();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void HandleEvents(union SDL_Event& ev);
};

