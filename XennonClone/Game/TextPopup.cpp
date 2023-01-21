#include "TextPopup.h"
#include "TextRendererComponent.h"
#include "GameWorld.h"

TextPopup::TextPopup(std::string text, float time, Vector2D pos)
{
	m_renderText = text;
	waitTime = time;
	GetTransform()->SetPosition(pos);
}

void TextPopup::Start()
{
	m_text = AddComponent<TextRendererComponent>(m_renderText, 1, GetTransform()->GetPosition(), "png/font8x8.png");
}

void TextPopup::Update(float delta)
{
	waitTime -= delta;
	if (waitTime<=0) {
		GameWorld::DestroyObject(this);
	}
}
