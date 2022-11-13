#pragma once
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	Pawn();
	~Pawn();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void HandleEvents();

protected:
	int m_InputRightAxis = 0;
	int m_InputUpAxis = 0;
	int m_MoveSpeed = 130;

};

