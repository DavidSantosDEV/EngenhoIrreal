#include "Sprite.h"
#include "GameObject.h"
#include "SDL.h"
#include "Transform.h"
#include "GameEngine.h"
#include "TextureManager.h"

Sprite::Sprite() : RenderComponent()
{
	m_Height = 32;
	m_Width = 32;

	m_Texture = nullptr;

}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_Texture);
	delete m_Texture;
	delete m_ParentTransform;
}

void Sprite::Start()
{
	if (m_OwnerGameObject) m_ParentTransform = m_OwnerGameObject->GetTransform();
}

void Sprite::SetSpriteScale(float height, float width)
{
	m_Height = height;
	m_Width = width;
}

void Sprite::Render()
{
	if (m_Texture) {
		if (m_ParentTransform) {
			SDL_FRect dest;
			dest.x = m_ParentTransform->GetPosition().x;
			dest.y = m_ParentTransform->GetPosition().y;
			dest.w = m_ParentTransform->GetScale().x * m_Width;
			dest.h = m_ParentTransform->GetScale().y * m_Height;
			//Game Engine Renderer
			SDL_RenderCopyF(GameEngine::GetInstance()->GetRenderer(), m_Texture, NULL, &dest);
		}
	}
}

void Sprite::SetSpriteTexture(SDL_Texture* Texture)
{
	m_Texture = Texture;
}

void Sprite::SetSpriteTexture(const char* TexturePath)
{
	m_Texture = TextureManager::LoadTexture(TexturePath);
}
