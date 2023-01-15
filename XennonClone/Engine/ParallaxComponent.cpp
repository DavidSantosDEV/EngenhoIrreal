/*
* - Generic ParallaxComponent with configurable parameters.
* -  - GameObject MUST have SpriteComponent for this component to work
************************************************************/

#include "ParallaxComponent.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Log.h"

void ParallaxComponent::Start()
{
	m_SpriteComponent = m_OwnerGameObject->GetComponent<Sprite>();

	if (m_SpriteComponent == nullptr)
	{
		LOG_ERROR("ParallaxComponent only works if GO also has a SpriteComponent");
	}

	m_OwnerGameObject->_Transform.SetPosition(0.f, -300);
}

void ParallaxComponent::Update(float deltaTime)
{	
	if (m_OwnerGameObject->_Transform.GetPosition().y >= m_SpriteComponent->m_SheetHeight + 475)
	{
		m_OwnerGameObject->_Transform.SetPosition(0.f, -300);
	}
	else
	{
		m_OwnerGameObject->_Transform.AddPosition(Vector2D(0, m_Speed * deltaTime));
	}
}

void ParallaxComponent::OnDestroyed()
{
}
