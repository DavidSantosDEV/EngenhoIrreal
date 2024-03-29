#pragma once
#include "RenderComponent.h"
#include <string>
#include "Transform.h"
#include <vector>

class TextRendererComponent : public RenderComponent
{
protected:
	std::string m_Text;
	float m_TextScale = 1;
	Vector2D m_TextPosition;
	class FontText* m_Font;
	std::vector<Vector2D> m_textCoords;
public:	
	TextRendererComponent(std::string TextToRender, float scale, Vector2D pos, std::string font);
	~TextRendererComponent();

	virtual void OnDestroyed() override;

	virtual void Render() override;

	//virtual void Start() override;

	void SetText(std::string newText);
	void SetScale(float textScale) { m_TextScale = textScale; }
	void SetPosition(Vector2D newPosition) { m_TextPosition = newPosition; }

	std::string GetTextString() { return m_Text; }
	float GetTextScale() { return m_TextScale; }
	Vector2D GetTextPosition() { return m_TextPosition; }
};

