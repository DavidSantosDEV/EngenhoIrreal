/*
* Generic Sprite class. Render() is called automatically since
* this functions inherits from RenderComponent.
* m_SpriteScale = the scale for this particular sprite (independent from parent GO scale)
* m_TextureWidth = the full size of this texturesheet
* m_SpriteWidth = the width of each sprite in the spritesheet (eg: 32x32, 64x64)
************************************************************/

#include "Sprite.h"
#include "GameObject.h"
#include "SDL.h"
#include "Transform.h"
#include "GameEngine.h"
#include "TextureManager.h"
#include "Log.h"

Sprite::Sprite(const char* texturePath, int renderPriority) : RenderComponent(renderPriority)
{
	SetTextureData(texturePath, 1, 1, 1.f);
}

Sprite::Sprite(const char* texturePath, int renderPriority, float scale) : RenderComponent(renderPriority)
{
	SetTextureData(texturePath, 1, 1, scale);
}

Sprite::Sprite(const char* texturePath, int spriteSheetRows, int spriteSheetColumns, 
	float scale, int renderPriority) : RenderComponent(renderPriority)
{
	SetTextureData(texturePath, spriteSheetRows, spriteSheetColumns, scale);
}

Sprite::~Sprite()
{/*
	GameEngine::RemoveRenderComponentFromStack(this);
	SDL_DestroyTexture(m_Texture);
	delete m_Texture;
	delete m_ParentTransform;*/
}

void Sprite::Start()
{
	Component::Start();

	if (m_OwnerGameObject)
	{
		m_ParentTransform = m_OwnerGameObject->GetTransform();
	}

}

void Sprite::Render()
{
	if (m_Texture) {
		if (m_ParentTransform) 
		{
			m_DestRect.x = m_ParentTransform->GetPosition().x;
			m_DestRect.y = m_ParentTransform->GetPosition().y;
			// TODO: optimize get renderer on tick
			SDL_RenderCopyF(GameEngine::GetInstance()->GetRenderer(), m_Texture, &m_SourceRect, &m_DestRect);
		}
	}
}

void Sprite::Destroy()
{
	GameEngine::RemoveRenderComponentFromStack(this);
	SDL_DestroyTexture(m_Texture);
	//delete m_Texture;
	//delete m_ParentTransform;
	//delete this;
}

void Sprite::SetSpriteTexture(SDL_Texture* texture)
{
	m_Texture = texture;
}

void Sprite::SetTextureData(const char* texturePath, int spriteSheetRows, int spriteSheetColumns, float scale)
{
	m_Texture = TextureManager::LoadTexture(texturePath);
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);

	m_FrameWidth = m_TextureWidth / spriteSheetRows;
	m_FrameHeight = m_TextureHeight / spriteSheetColumns;

	m_SourceRect.x = m_SourceRect.y = 0;
	m_SourceRect.w = m_FrameWidth;
	m_SourceRect.h = m_FrameHeight;
	m_DestRect.w = m_FrameWidth * scale;
	m_DestRect.h = m_FrameHeight * scale;
}

SDL_Rect& Sprite::GetSourceRect()
{
	return m_SourceRect;
}

SDL_FRect& Sprite::GetDestRect()
{
	return m_DestRect;
}
