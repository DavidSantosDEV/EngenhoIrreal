/*
* Generic Render component. Render() component called every frame 
* from GameEngine.h
************************************************************/

#include "GameEngine.h"
#include "RenderComponent.h"
#include "Log.h"

RenderComponent::RenderComponent()
{
	GameEngine::AddRenderComponentToStack(this);
}

RenderComponent::~RenderComponent()
{
	GameEngine::RemoveRenderComponentFromStack(this);
}

void RenderComponent::Render()
{
}
