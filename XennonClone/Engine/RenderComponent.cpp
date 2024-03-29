/*
* Generic Render component. Render() component called every frame 
* from GameEngine.h
* Not meant to be used directly, create child classes 
************************************************************/

#include "GameEngine.h"
#include "RenderComponent.h"
#include "Log.h"

RenderComponent::RenderComponent()
{
	m_RenderPriority = 0;
}

RenderComponent::RenderComponent(int renderPriority)
{
	m_RenderPriority = renderPriority;
	GameEngine::AddRenderComponentToStack(this);
}

RenderComponent::~RenderComponent()
{
	GameEngine::RemoveRenderComponentFromStack(this);
}

void RenderComponent::SetRenderPriority(int renderPriority)
{
	m_RenderPriority = renderPriority;
	GameEngine::SortRenderComponents();
}
