#pragma once
#include "RenderComponent.h"
#include "Transform.h"

struct SDL_Texture;

class Sprite : public RenderComponent
{
protected:
	Transform* m_ParentTransform{ nullptr };

	//Display
	SDL_Texture* m_Texture;

	Vector2D m_SpriteScale;
	//SDL_FRect& m_destRect; Not needed its basically a copy of transform

public:
	Sprite() = default;
	Sprite(const char* texturePath, float h, float w);
	~Sprite();

	virtual void Start() override;

	void SetSpriteTexture(SDL_Texture* Texture);
	void SetSpriteTexture(const char* TexturePath);

	inline SDL_Texture* GetTexture() const { return m_Texture; }

	void SetSpriteScale(Vector2D scale) { m_SpriteScale = scale; }
	void SetSpriteScale(float width,float height) { m_SpriteScale = Vector2D(width, height); }

	// Inherited via RenderComponent
	virtual void Render() override;
};