#include "PlayerUI.h"
#include "TextRendererComponent.h"


void PlayerUI::Start()
{
	textRenderer = AddComponent<TextRendererComponent>("Player Health:", 1.f, Vector2D(200, 200), "png/font16x16.png");
	textRenderer->SetText("Player Health: 100");
}

void PlayerUI::SetLifeCount(int count)
{

}
