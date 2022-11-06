#include "Sprite.h"
#include "GameObject.h"
#include "SDL.h"
#include "Transform.h"
#include "GameEngine.h"
#include "TextureManager.h"
#include "Log.h"


Sprite::Sprite(const char* texturePath, float h, float w) : RenderComponent()
{
	m_SpriteScale = Vector2D(32, 32);
	m_Texture = TextureManager::LoadTexture(texturePath);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_Texture);
	delete m_Texture;
	delete m_ParentTransform;
}

void Sprite::Start()
{
	Component::Start();

	if (m_OwnerGameObject) m_ParentTransform = m_OwnerGameObject->GetTransform();
}

void Sprite::Render()
{
	if (m_Texture) {
		if (m_ParentTransform) {
			SDL_FRect dest;
			dest.x = m_ParentTransform->GetPosition().x;
			dest.y = m_ParentTransform->GetPosition().y;
			dest.w = m_ParentTransform->GetScale().x * m_SpriteScale.x;
			dest.h = m_ParentTransform->GetScale().y * m_SpriteScale.y;
			//Game Engine Renderer
			// TODO: optimize get get renderer on tick
			SDL_RenderCopyF(GameEngine::GetInstance()->GetRenderer(), m_Texture, nullptr, &dest);
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
