/*
* - Helper class for loading BMP or PNG textures.
************************************************************/

#include "TextureManager.h"
#include "GameEngine.h"
#include "SDL_image.h"
//#include "RenderComponent.h"
#include <iostream>
#include "Log.h"

const char* TextureManager::m_BasePath = "../Assets/";

std::string TextureManager::GetPathTranslated(const char* path)
{
    std::string fullPath = m_BasePath;
    fullPath += path;
    return fullPath;
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