#include "FontLoader.h"
#include "TextureManager.h"
#include "MathHelper.h"
FontLoader::~FontLoader()
{
	for (auto font : m_LoadedFonts) {
		delete font;
	}
	m_LoadedFonts.clear();
}

void FontLoader::Init(std::string DefaultFontPath)
{
}

void FontLoader::LoadFont(std::string newFont)
{
}

void FontLoader::UnloadFont(std::string font)
{
}

FontText* FontLoader::GetFont(std::string fontDir)
{
	for (auto font : m_LoadedFonts) {
		if (font->GetOriginalPath() == fontDir) {
			return font;
		}
	}

	/* Load a new font */

	TextureData newData = TextureManager::LoadTextureOpenGL(fontDir.c_str());

	FontText* newFont = new FontText();
	newFont->SetNewData(newData);

	m_LoadedFonts.push_back(newFont);

	return newFont;
}

//Font text

FontText::~FontText()
{
	TextureManager::FreeTexture(&m_data);
}

void FontText::SetNewData(TextureData newData)
{
	if (newData.TextureID != m_data.TextureID) {
		TextureManager::FreeTexture(&m_data);
		m_data = newData;
	}
}

Vector2D FontText::GetPositionIndexForChar(char c)
{
	int y = 0;
	int x = 0;
	for (int i = 0; i < m_Format.size(); ++i) {
		if (c == m_Format[i]) {
			return Vector2D(x, y);
		}
		x++;
		if (x >= m_columns) {
			x = 0;
			y++;
		}
	}
	return Vector2D::Zero();

	/*
	int y = 0;
	int xcount=0;
	for (int i = 0; i < m_Format.size();++i) {
		xcount++;
		if (xcount>=m_columns) {
			xcount = 0;
			y++;
			
		}
		if (c == m_Format[i]) {
			return Vector2D(MathHelper::ClampInt(xcount - 1,0,m_columns-1), y);
		}
	}
	return Vector2D::Zero();*/
}
