#include "PlayerUI.h"
#include "Sprite.h"

void PlayerUI::Start()
{
}

void PlayerUI::SetLifeCount(int count)
{
	int num = count;
	for (auto s : playerHealthCountSprites) {
		s.SetActive(num > 0);
		num--;
	}
}
