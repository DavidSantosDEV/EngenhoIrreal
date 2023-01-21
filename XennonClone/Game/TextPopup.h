#pragma once
#include "GameObject.h"
#include <string>
class TextPopup : public GameObject
{

protected:
	class TextRendererComponent* m_text;
	float waitTime = 3.f;
	std::string m_renderText;
public:

	TextPopup(std::string text, float time, Vector2D pos);


	virtual void Start() override;


	virtual void Update(float delta) override;
};

