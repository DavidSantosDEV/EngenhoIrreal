#pragma once
#include "RenderComponent.h"
#include "TextureManager.h"
#include "Transform.h"


class UISprite :public RenderComponent
{
protected:

	Vector2D m_drawPosition = Vector2D::Zero();
	Vector2D m_wh;
	Vector2D m_xy;
	Vector2D m_SheetCoord;

	TextureData m_currentTextureData;
	float m_scale = 1.f;

	float m_xFill = 1.f;
	float m_yFill = 1.f;

public:

	UISprite(const char* spritePath, int columns, int rows, Vector2D drawPosition, float scale, Vector2D sheetCoord);

	~UISprite();

	virtual void Render() override;

	void SetRenderScale(float scale);

	void SetXFill(float ammount);
	void SetYFill(float ammount);

	void SetSheetCoord(Vector2D coord);


};

