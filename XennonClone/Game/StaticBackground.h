#include "GameObject.h"

class StaticBackground : public GameObject
{
protected:
	class Sprite* m_SpriteComponent;
public:
	virtual void Start() override;
	StaticBackground();
	~StaticBackground();
};