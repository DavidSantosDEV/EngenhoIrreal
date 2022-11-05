#include "TextureManager.h"
#include "GameEngine.h"
#include "GameRenderer.h"
#include "SDL_image.h"
#include <iostream>

const char* TextureManager::m_BasePath = "../Assets/"; 

std::string TextureManager::GetPathTranslated(const char* path)
{
    std::string fullPath = m_BasePath;
    fullPath += path;
    return fullPath;
}

SDL_Texture* TextureManager::LoadTexture(const char* Filename)
{
    SDL_Renderer* const ren = GameEngine::GetGameRenderer()->GetRenderer();
    if (!ren)return nullptr;
    SDL_Surface* tmpSurf{ LoadSurface(Filename) };
    SDL_Texture* finaltexture{ nullptr };
    if (tmpSurf) {
        finaltexture = SDL_CreateTextureFromSurface(ren, tmpSurf);
    }
    SDL_FreeSurface(tmpSurf);
    return finaltexture;
}

SDL_Texture* TextureManager::LoadTextureBMP(const char* Filename) {
    SDL_Renderer* const ren = GameEngine::GetGameRenderer()->GetRenderer();
    
    if (!ren)return nullptr;

    SDL_Surface* surf = SDL_LoadBMP(Filename);

    if (!surf) {
        const char* error = SDL_GetError();
        std::cout << "tempSurf=" << surf << " Reason: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));

    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surf);
    if (!text) {
        const char* error = SDL_GetError();
        std::cout << "tempSurf=" << surf << " Reason: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return text;
}

SDL_Surface* TextureManager::LoadSurface(const char* Filename)
{
    std::string path = GetPathTranslated(Filename);
    SDL_Surface* tmpSurf = IMG_Load(path.c_str());
    if (!tmpSurf) {
        const char* error = SDL_GetError();
        std::cout << "tempSurf=" << tmpSurf << " Reason: " << SDL_GetError() << std::endl;
    }
    return tmpSurf;
}