#include "Renderer.h"
#include <iostream>
#include <SDL.h>
#include <array>
#include <glad/glad.h>
#include "MathHelper.h"
#include "Transform.h"


float Renderer::s_ScreenWidth = 0.f;
float Renderer::s_ScreenHeight = 0.f;

/* The maximum number of quads that can be drawn in a single draw call*/
static const size_t MaxQuadCount = 5000;
static const size_t MaxVertexCount = MaxQuadCount * 4;
static const size_t MaxIndexCount = MaxQuadCount * 6;
static const size_t MaxTextures = 32;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoords;
	float TexID;
};

struct RendererData
{
	GLuint Vao = 0;
	GLuint Vbo = 0;
	GLuint Ib = 0;

	/* The current number of indices (for every quad += 6) */
	uint32_t CurrentIndexCount = 0;

	/* The buffer that holds the memory for the quads that will be drawn */
	Vertex* QuadBuffer = nullptr;
	Vertex* QuadBufferPtr = nullptr;

	/* array with texture ID*/
	std::array<uint32_t, MaxTextures> TextureSlots;
	// Start at 1 because 0 is reserved for no texture
	uint32_t CurrentTextureSlotIndex = 1;
};

static RendererData s_Data;

void Renderer::Init()
{
	s_Data.QuadBuffer = new Vertex[MaxVertexCount];

	glCreateVertexArrays(1, &s_Data.Vao);
	glBindVertexArray(s_Data.Vao);

	/* Create empty dynamic vbo that will be populated every frame */
	glCreateBuffers(1, &s_Data.Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.Vbo);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexArrayAttrib(s_Data.Vao, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexArrayAttrib(s_Data.Vao, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

	glEnableVertexArrayAttrib(s_Data.Vao, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

	glEnableVertexArrayAttrib(s_Data.Vao, 3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

	// CPU Index Buffer
	uint32_t indices[MaxIndexCount];
	uint32_t offset = 0;
	for (size_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	glCreateBuffers(1, &s_Data.Ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.Ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Default texture slot is 0 (meaning none)
	for (size_t i = 0; i < MaxTextures; i++)
		s_Data.TextureSlots[i] = 0;
}

void Renderer::ShutDown()
{
	glDeleteVertexArrays(1, &s_Data.Vao);
	glDeleteBuffers(1, &s_Data.Vbo);
	glDeleteBuffers(1, &s_Data.Ib);

	delete[] s_Data.QuadBuffer;
}

void Renderer::BeginBatch()
{
	s_Data.QuadBufferPtr = s_Data.QuadBuffer;
}

void Renderer::EndBatch()
{
	// Calculate the amount of things that need to be rendered. 
	GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.Vbo);
	// Send that data do the dynamic VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
}

void Renderer::Flush()
{
	for (uint32_t i = 0; i < s_Data.CurrentTextureSlotIndex; i++)
		glBindTextureUnit(i, s_Data.TextureSlots[i]);

	glBindVertexArray(s_Data.Vao);
	glDrawElements(GL_TRIANGLES, s_Data.CurrentIndexCount, GL_UNSIGNED_INT, nullptr);

	// Reset Stats
	s_Data.CurrentIndexCount = 0;
	s_Data.CurrentTextureSlotIndex = 1;
}

void Renderer::DrawQuad(const Vector2D& position, const float scaleFactor, uint32_t textureID, SDL_Rect* sourceRect, const Vector2D& sheetSize)
{
	const float sheetWidth = sheetSize.x, sheetHeight = sheetSize.y;
	float x = sourceRect->x / sourceRect->w;
	float y = sourceRect->y / sourceRect->h;

	// Convert scale factor to be sprite size * value
	float drawWidth = sourceRect->w* scaleFactor;
	float drawHeight = sourceRect->h * scaleFactor;
	drawWidth = MathHelper::MapClampRanged(drawWidth, 0.f, s_ScreenWidth, 0.f, 2.f);
	drawHeight = MathHelper::MapClampRanged(drawHeight, 0.f, s_ScreenHeight, 0.f, 2.f);

	// Convert positions to what SDL uses (top left is (0,0)
	float drawPosX = MathHelper::MapClampRanged(position.x, 0.f, s_ScreenWidth, -1, 1);
	float drawPosY = MathHelper::MapClampRanged(position.y, 0.f, s_ScreenHeight, 1, -1);

	// If the max number of quads are already being drawn, draw them and start another batch
	if (s_Data.CurrentIndexCount >= MaxIndexCount || s_Data.CurrentTextureSlotIndex > 31)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}

	// Check if this texture is already bond and used by other quad
	float textureIndex = 0.f;

	for (uint32_t i = 1; i < s_Data.CurrentTextureSlotIndex; i++)
	{
		if (s_Data.TextureSlots[i] == textureID)
		{
			textureIndex = (float)i;
			break;
		}
	}

	// If not, bound a new one
	if (textureIndex == 0.f)
	{
		textureIndex = (float)s_Data.CurrentTextureSlotIndex;
		s_Data.TextureSlots[s_Data.CurrentTextureSlotIndex] = textureID;
		s_Data.CurrentTextureSlotIndex++;
	}

	/* BL, BR, TR, TL */
	const glm::vec2 textureCoords[] = {
	{(x * sourceRect->w) / sheetWidth, (y * sourceRect->h) / sheetHeight},
	{((x + 1) * sourceRect->w) / sheetWidth, (y * sourceRect->h) / sheetHeight},
	{((x + 1) * sourceRect->w) / sheetWidth, ((y + 1) * sourceRect->h) / sheetHeight},
	{(x * sourceRect->w) / sheetWidth, ((y + 1) * sourceRect->h) / sheetHeight}
	};

	const glm::vec3 positions[] = {
		{ drawPosX, drawPosY - drawHeight, 0.f},
		{ drawPosX + drawWidth, drawPosY - drawHeight, 0.f},
		{ drawPosX + drawWidth, drawPosY, 0.f },
		{ drawPosX, drawPosY, 0.f}
	};

	for (int i = 0; i < 4; ++i)
	{
		s_Data.QuadBufferPtr->Position = positions[i];
		s_Data.QuadBufferPtr->Color = { 1.f, 1.f, 1.f };
		s_Data.QuadBufferPtr->TexCoords = textureCoords[i];
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;
	}
	s_Data.CurrentIndexCount += 6;
}

