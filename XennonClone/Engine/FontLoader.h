#pragma once
#include <string>
#include <vector>
#include "TextureManager.h"
#include "Transform.h"

class FontText {
protected:
	TextureData m_data;
	std::string m_OriginalPath;
	int m_rows = 12;	
	int m_columns = 8;
	std::vector<char> m_Format = {' ','!','"','#','$','%','&',39,
								'(',')','*','+',',','-','.','/',
								'0','1','2','3','4','5','6','7',
								'8','9',':',';','<','=','>','?',
								'€','A','B','C','D','E','F','G',
								'H','I','J','K','L','M','N','O',
								'P','Q','R','S','T','U','V','W',
								'X','Y','Z','[',92,']','^','_',
								'`','a','b','c','d','e','f','g',
								'h','i','j','k','l','m','n','o',
								'p','q','r','s','t','u','v','w',
								'x','y','z','{',':','}','»','«'};
public:
	~FontText();
	void SetNewData(TextureData newData);
	TextureData* GetData() { return &m_data; }
	std::string GetOriginalPath() { return m_OriginalPath; }

	//Get the Sprite location
	Vector2D GetPositionIndexForChar(char c);

	int GetRows() { return m_rows; }
	int GetColumns() { return m_columns; }

	void SetFormat(std::vector<char> newFormat) { m_Format = newFormat; }
	void SetRowsAndColumns(int rows, int columns) { m_rows = rows; m_columns = columns; }
};

class FontLoader
{
private:
	std::vector<FontText*> m_LoadedFonts;
public:

	~FontLoader();

	void Init(std::string DefaultFontPath);

	void LoadFont(std::string newFont);
	void UnloadFont(std::string font);

	FontText* GetFont(std::string font);

	std::vector<FontText*> GetLoadedFonts() {
		return m_LoadedFonts;
	}
};

