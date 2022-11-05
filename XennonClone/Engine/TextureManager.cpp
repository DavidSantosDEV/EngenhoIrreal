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

SDL_Surface* TextureManager::LoadSurface(const char* Filename)
{
    std::string path = GetPathTranslated(Filename);
    const char* pathC = path.c_str();
    SDL_Surface* tmpSurf = IMG_Load(pathC);
    const char* error = SDL_GetError();
    std::cout << "tempSurf=" << tmpSurf << " Reason: " << SDL_GetError() << std::endl;
    return tmpSurf;
}