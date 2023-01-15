#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Renderer
{
public:

	static void Init();
	static void ShutDown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void DrawQuad(const Vector2D& position, const float scaleFactor, uint32_t textureID, struct SDL_Rect* sourceRect, const Vector2D& sheetSize);

	static float s_ScreenWidth, s_ScreenHeight;

};

