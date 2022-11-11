#pragma once
#include "GameObject.h"

class RocksBackground : public GameObject
{
private:
	class Sprite* m_SpriteComponent = nullptr;
public:
	RocksBackground();
	~RocksBackground();
};

