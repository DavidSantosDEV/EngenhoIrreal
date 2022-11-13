#include "ParallaxComponent.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Log.h"

void ParallaxComponent::Start()
{
	m_SpriteComponent = &m_OwnerGameObject->GetComponent<Sprite>();

	if (m_SpriteComponent == nullptr)
	{
		LOG_ERROR("ParallaxComponent only works if GO also has a SpriteComponent");
	}

	m_OwnerGameObject->m_Transform.SetPosition(0.f, -m_SpriteComponent->m_TextureHeight);
}

void ParallaxComponent::Update(float deltaTime)
{	
	if (m_OwnerGameObject->m_Transform.GetPosition().y >= m_SpriteComponent->m_TextureHeight / 3)
	{
		m_OwnerGameObject->m_Transform.SetPosition(0.f, -m_SpriteComponent->m_TextureHeight);
	}
	else
	{
		m_OwnerGameObject->m_Transform.AddPosition(Vector2D(0, m_Speed * deltaTime));
	}

	LOG(m_OwnerGameObject->m_Transform.GetPosition().y);
}
