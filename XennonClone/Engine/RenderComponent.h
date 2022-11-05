
//Render Component

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	virtual void Render(struct SDL_Renderer* renderer) = 0;
};