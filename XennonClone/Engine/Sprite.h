#pragma once
#include "RenderComponent.h"
#include "Transform.h"

struct SDL_Texture;

class Sprite : public RenderComponent
{
protected:
	Transform* m_ParentTransform {nullptr};

	//Display
	SDL_Texture* m_Texture;

	float m_Width;
	float m_Height;
	//SDL_FRect& m_destRect; Not needed its basically a copy of transform

	//Animation
	bool m_IsAnimated = false;
	int m_Frames;
	int m_Speed;

public:

	Sprite();
	~Sprite();

	virtual void Start() override;

	void SetSpriteTexture(SDL_Texture* Texture);
	void SetSpriteTexture(const char* TexturePath);

	inline SDL_Texture* GetTexture() const { return m_Texture; }

	void SetSpriteScale(float height, float width);

	// Inherited via RenderComponent
	virtual void Render(SDL_Renderer* renderer) override;
};

