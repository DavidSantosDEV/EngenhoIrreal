#include "TextRendererComponent.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "SDL.h"
#include "FontLoader.h"

TextRendererComponent::TextRendererComponent(std::string TextToRender, float scale, Vector2D pos, std::string font) : RenderComponent(0)
{
	m_Text = TextToRender;
	m_TextPosition = pos;
	m_TextScale = scale;
	m_Font = GameEngine::GetInstance()->GetFontLoader()->GetFont(font);
	SetRenderPriority(-1);
}

void TextRendererComponent::Render()
{
	return;
	Vector2D posWorld = m_TextPosition;
	for (char& c : m_Text) {
		//Find sprite for char

		Vector2D IndexPos = m_Font->GetPositionIndexForChar(c);

		SDL_Rect SourceRect;
		//SDL_Rect DestRect;

		int m_FrameWidth = m_Font->GetData()->SheetWidth / m_Font->GetColumns();
		int m_FrameHeight = m_Font->GetData()->SheetHeight / m_Font->GetRows();

		SourceRect.x = m_FrameWidth * IndexPos.x;
		SourceRect.y = m_FrameHeight * IndexPos.y;


		SourceRect.w = m_FrameWidth;
		SourceRect.h = m_FrameHeight;

		//DestRect.w = m_FrameWidth * m_TextScale;
		//DestRect.h = m_FrameHeight * m_TextScale;

		Renderer::DrawQuad(posWorld, m_TextScale, m_Font->GetData()->TextureID, &SourceRect, Vector2D(m_Font->GetData()->SheetWidth, m_Font->GetData()->SheetHeight));
		posWorld = Vector2D(posWorld.x + m_FrameWidth, posWorld.y);
	}
}
