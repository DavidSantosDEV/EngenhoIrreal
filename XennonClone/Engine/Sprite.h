#pragma once
#include "RenderComponent.h"
#include "Transform.h"
#include "SDL.h"
#include "TextureManager.h"

struct SDL_Texture;
struct SDL_Rect;

class Sprite : public RenderComponent
{
	friend class AnimationComponent;
	friend class ParallaxComponent;
protected:
	Transform* m_ParentTransform{ nullptr };

	//Display

	//SDL_Texture* m_Texture = nullptr;
	TextureData m_TextureData;

	SDL_Rect m_SourceRect;
	SDL_FRect m_DestRect;

	/* The pixels (width and height) of the texture that should be loaded */
	int m_SheetWidth = 0;
	int m_SheetHeight = 0;
	/* The pixels (width and height) of each sprite in the spritesheet */
	int m_FrameWidth = 1;
	int m_FrameHeight = 1;
	//SDL_FRect& m_destRect; Not needed its basically a copy of transform

	float m_rotation = 0.f;

	bool m_FlipX = false;
	bool m_FlipY = false;

	float m_Opacity = 1;

	float m_Scale = 1.f;

public:
	/* Used for non-animated sprites */
	Sprite(const char* texturePath, int renderPriority);
	/* Used for non-animated sprites */
	Sprite(const char* texturePath, int renderPriority, float scale);
	/* Used for animated sprites or specific sprites in spritesheet */
	Sprite(const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale, int renderPriority);
	Sprite(const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale, int renderPriority, bool isUI);

	void SetFlipY(bool val) { m_FlipY = val; }

	virtual void Start() override;

	//void SetSpriteTexture(SDL_Texture* Texture);
	void SetTextureData(const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale);

	int GetSheetHeight() const { return m_SheetHeight; }

	//inline SDL_Texture* GetTexture() const { return m_Texture; }
	SDL_Rect& GetSourceRect();
	//SDL_FRect& GetDestRect();

	void SetRotation(float val) { m_rotation = val; }

	void SetOpacity(float opacity);
	void SetScale(float fScale);

	float GetScale() const { return m_Scale; }

	// Inherited via RenderComponent
	virtual void Render() override;

	virtual void OnDestroyed() override;
};