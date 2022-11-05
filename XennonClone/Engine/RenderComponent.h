
//Render Component

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();
	virtual void Render() = 0;
};