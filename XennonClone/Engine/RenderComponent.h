#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(int renderPriority);
	~RenderComponent();
	virtual void Render() {};

	int GetRenderPriority() const { return m_RenderPriority; }
	void SetRenderPriority(int renderPriority);

	void SetIsVisible(bool val) { m_IsVisible = val; }
	bool GetIsVisible() { return m_IsVisible; }

	bool GetIsUI() {
		return m_IsUI;
	}

protected:
	/* Higher numbers will be rendered in front of smaller ones. */
	int m_RenderPriority = 0;

	bool m_IsVisible = true;
	bool m_IsUI = false;

};