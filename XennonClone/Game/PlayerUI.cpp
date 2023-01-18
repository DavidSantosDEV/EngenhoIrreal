#include "PlayerUI.h"
#include "TextRendererComponent.h"


void PlayerUI::Start()
{
	textRenderer = AddComponent<TextRendererComponent>("Ready Player One?", 1.f, Vector2D(200, 200), "font16x16.bmp");
}

void PlayerUI::SetLifeCount(int count)
{

}
