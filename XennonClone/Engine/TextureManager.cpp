/*
* - Helper class for loading BMP or PNG textures.
************************************************************/

#include "TextureManager.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <iostream>
#include "Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

const char* TextureManager::m_BasePath = "../Assets/";

std::string TextureManager::GetPathTranslated(const char* path)
{
    std::string fullPath = m_BasePath;
    fullPath += path;
    return fullPath;
}

TextureData TextureManager::LoadTextureOpenGL(const char* path)
{
    int sheetWidth = 0, sheetHeight = 0;
    unsigned int internalFormat = 0, dataFormat = 0;

	int numberChannels;

	stbi_set_flip_vertically_on_load(0);
	// Load texture data
	unsigned char* textureData = stbi_load(GetPathTranslated(path).c_str(), 
        &sheetWidth, &sheetHeight, &numberChannels, 0);

    if (numberChannels == 3)
    {
        LOG_WARNING("Texture is still .bmp at: " << path);
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }
    else
    {
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
    }

	if (textureData == nullptr)
	{
		LOG_ERROR("Failed to load texture data from path: " << GetPathTranslated(path));
	}

	unsigned int textureID;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, sheetWidth, sheetHeight, 0, dataFormat, GL_UNSIGNED_BYTE, textureData);

	stbi_image_free(textureData);

	return TextureData(textureID, sheetWidth, sheetHeight);
}

SDL_Texture* TextureManager::LoadTexture(const char* Filename) //Generic Loader
{
    SDL_Renderer* const ren = GameEngine::GetInstance()->GetRenderer();
    if (!ren) { return nullptr; }

    SDL_Surface* tmpSurf{ LoadSurface(Filename) };
    SDL_Texture* finaltexture{ nullptr };

    if (tmpSurf) 
    {
		SDL_SetColorKey(tmpSurf, SDL_TRUE, SDL_MapRGB(tmpSurf->format, 255, 0, 255));
        finaltexture = SDL_CreateTextureFromSurface(ren, tmpSurf);
    }

    SDL_FreeSurface(tmpSurf);
    SDL_SetTextureBlendMode(finaltexture, SDL_BLENDMODE_BLEND);

    return finaltexture;
}
void TextureManager::FreeTexture(TextureData* texture)
{
    if (texture) {
        glDeleteTextures(1, &texture->TextureID);
    }
}
/*
SDL_Texture* TextureManager::LoadTextureBind(const char* Filename, RenderComponent* comp)
{
    if (!comp)return nullptr;
    TextureAndComps* RefText = &m_textureMap[std::string(Filename)];
    if (RefText) {
        for (int i = 0; i < RefText->components.size();++i) {
            if (comp == RefText->components[i]) {
                return nullptr;
            }
        }

        RefText->components.push_back(comp);
        return RefText->texture;
    }
    else {
        SDL_Texture* text = LoadTexture(Filename);

        //std::vector<RenderComponent*> r = { comp };
        m_textureMap[std::string(Filename)] = TextureAndComps{ text,{ comp } };

        return text;
    }
    return nullptr;
}

void TextureManager::RemoveFromBind(SDL_Texture* text, RenderComponent* comp)
{
    if (!comp) {
        return;
    }
    
    TextureAndComps* RefText = &m_textureMap[std::string(Filename)];
    if (RefText) {
        for (int i = 0; i < RefText->components.size(); ++i) {
            if (comp == RefText->components[i]) {
                return nullptr;
            }
        }

        RefText->components.push_back(comp);
        return RefText->texture;
    }
}
*/

SDL_Texture* TextureManager::LoadTextureBMP(const char* fileName) //BMP Loader
{
    SDL_Renderer* const ren = GameEngine::GetInstance()->GetRenderer();

    if (!ren)return nullptr;

    SDL_Surface* surf = SDL_LoadBMP(fileName);

    if (!surf) {
        const char* error = SDL_GetError();
        LOG_ERROR("tempSurf=" << surf << " Reason: " << SDL_GetError());
        return nullptr;
    }

    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    if (!text) {
        const char* error = SDL_GetError();
        LOG_ERROR("tempSurf=" << surf << " Reason: " << SDL_GetError() << std::endl);
        return nullptr;
    }

    SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);

    return text;
}

SDL_Surface* TextureManager::LoadSurface(const char* Filename) //Generic Surface Loader
{
    std::string path = GetPathTranslated(Filename);
    SDL_Surface* tmpSurf = IMG_Load(path.c_str());
    if (!tmpSurf) {
        const char* error = SDL_GetError();
       LOG_ERROR("tempSurf=" << tmpSurf << " Reason: " << SDL_GetError());
    }
    return tmpSurf;
}