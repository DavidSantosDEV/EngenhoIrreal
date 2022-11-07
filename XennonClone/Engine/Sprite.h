#pragma once
#include "RenderComponent.h"
#include "Transform.h"

struct SDL_Texture;
struct SDL_Rect;

class Sprite : public RenderComponent
{
	friend class AnimationComponent;
protected:
	Transform* m_ParentTransform{ nullptr };

	//Display
	SDL_Texture* m_Texture;

	/* The pixels (width and height) of the texture that should be loaded */
	int m_TextureWidth = 0;
	int m_TextureHeight = 0;
	/* The pixels (width and height) of each sprite in the spritesheet */
	int m_FrameWidth = 1;
	int m_FrameHeight = 1;
	//SDL_FRect& m_destRect; Not needed its basically a copy of transform

public:
	Sprite() = default;
	/* Used for non-animated sprites */
	Sprite(const char* texturePath);
	/* Used for animated sprites */
	Sprite(const char* texturePath, int spriteSheetRows, int spriteSheetColumns, float scale);
	~Sprite();

	virtual void Start() override;

	void SetSpriteTexture(SDL_Texture* Texture);
	void SetSpriteTexture(const char* TexturePath);

	inline SDL_Texture* GetTexture() const { return m_Texture; }
	SDL_Rect& GetSourceRect() const;

	// Inherited via RenderComponent
	virtual void Render() override;
};