#pragma once
#include "RenderComponent.h"
#include <string>
#include "Transform.h"

class TextRendererComponent : public RenderComponent
{
protected:
	std::string m_Text;
	float m_TextScale = 1;
	Vector2D m_TextPosition;
	class FontText* m_Font;
public:
	TextRendererComponent(std::string TextToRender, float scale, Vector2D pos, std::string font);

	virtual void Render() override;

	void SetText(std::string newText) { m_Text = newText; }
	void SetScale(float textScale) { m_TextScale = textScale; }
	void SetPosition(Vector2D newPosition) { m_TextPosition = newPosition; }

	std::string GetTextString() { return m_Text; }
	float GetTextScale() { return m_TextScale; }
	Vector2D GetTextPosition() { return m_TextPosition; }
};

