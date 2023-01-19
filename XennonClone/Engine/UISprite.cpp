#include "UISprite.h"
#include "GameEngine.h"
#include "Renderer.h"
#include "SDL.h"
#include "MathHelper.h"

UISprite::UISprite(const char* spritePath, int columns, int rows,Vector2D drawPosition, float scale, Vector2D sheetCoord) : RenderComponent()
{
	m_IsUI = true;
	m_drawPosition = drawPosition;
	m_currentTextureData = TextureManager::LoadTextureOpenGL(spritePath);
	m_scale= scale;

	m_SheetCoord = sheetCoord;

	m_xy.x = m_xy.y = 0;
	m_wh.x = m_currentTextureData.SheetWidth / columns;
	m_wh.y = m_currentTextureData.SheetHeight / rows;

	GameEngine::AddRenderComponentToStack(this);
}

UISprite::~UISprite()
{
	TextureManager::FreeTexture(&m_currentTextureData);
}

void UISprite::Render()
{
	if (!GetIsActive())return;
	SDL_Rect SourceRect;
	SourceRect.x = m_wh.x * m_SheetCoord.x;
	SourceRect.y = m_wh.y * m_SheetCoord.y;
	SourceRect.w = m_wh.x * m_xFill;
	SourceRect.h = m_wh.y * m_yFill;
	Renderer::DrawQuad(m_drawPosition, m_scale, m_currentTextureData.TextureID, &SourceRect, Vector2D(m_currentTextureData.SheetWidth, m_currentTextureData.SheetHeight));
}

void UISprite::SetRenderScale(float scale) {
	m_scale = scale;
}

void UISprite::SetXFill(float ammount) {
	m_xFill = MathHelper::Clamp01(ammount);
}
void UISprite::SetYFill(float ammount) {
	m_yFill = MathHelper::Clamp01(ammount);
}

void UISprite::SetSheetCoord(Vector2D coord) {
	m_SheetCoord = coord;
}