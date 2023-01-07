#pragma once

#include <glm/glm.hpp>

class Renderer
{
public:

	static void Init();
	static void ShutDown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureID);
};

