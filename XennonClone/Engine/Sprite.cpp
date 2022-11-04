#include "Sprite.h"
#include "GameObject.h"
#include "SDL.h"
#include "Transform.h"

Sprite::Sprite() : RenderComponent()
{
	m_Height = 1;
	m_Width = 1;

	m_Texture = nullptr;
	if(m_OwnerGameObject) m_ParentTransform = m_OwnerGameObject->GetTransform();
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_Texture);
	delete m_Texture;
	delete m_ParentTransform;
}

void Sprite::SetSpriteScale(float height, float width)
{
}

void Sprite::Render(SDL_Renderer* renderer)
{
	SDL_FRect dest;
	dest.x = m_ParentTransform->GetPosition().x;
	dest.y = m_ParentTransform->GetPosition().y;

	//Game Engine Renderer
	SDL_RenderCopyF(, m_Texture, NULL, &dest);
}

void Sprite::SetSpriteTexture(SDL_Texture* Texture)
{
	m_Texture = Texture;
}

void Sprite::SetSpriteTexture(const char* TexturePath) 
{

}
