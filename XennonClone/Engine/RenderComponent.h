
//Render Component

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(int renderPriority);
	~RenderComponent();
	virtual void Render();

	int GetRenderPriority() const { return m_RenderPriority; }
	void SetRenderPriority(int renderPriority) { m_RenderPriority = renderPriority; }

protected:
	/* Higher numbers will be rendered in front of smaller ones. */
	int m_RenderPriority = 0;
};