#include "GameObject.h"

class StaticBackground : public GameObject
{
protected:
	class Sprite* m_SpriteComponent;
public:
	StaticBackground();
	~StaticBackground();

	virtual void Start() override;
};