#include "RenderComponent.h"
#include "GameEngine.h"
RenderComponent::RenderComponent()
{
	GameEngine::AddRenderComponentToStack(this);
}
RenderComponent::~RenderComponent() {
	GameEngine::RemoveRenderComponentFromStack(this);
}