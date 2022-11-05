#include "TextureManager.h"
#include "GameEngine.h"
#include "GameRenderer.h"
#include "SDL_image.h"
#include <string>

const char* TextureManager::m_BasePath = "Assets/"; 

const char* TextureManager::GetPathTranslated(const char* path)
{
    std::string fullPath = m_BasePath;
    fullPath += path;
    const char* foo = fullPath.c_str();
    return foo;
}

SDL_Texture* TextureManager::LoadTexture(const char* Filename)
{
    
    SDL_Surface* tmpSurf{ LoadSurface(GetPathTranslated(Filename)) };
    SDL_Texture* finaltexture{ nullptr };
    if (tmpSurf) {
        finaltexture = SDL_CreateTextureFromSurface(GameEngine::GetGameRenderer()->GetRenderer(), tmpSurf);
    }
    SDL_FreeSurface(tmpSurf);
    return finaltexture;
    return nullptr;
}

SDL_Surface* TextureManager::LoadSurface(const char* Filename)
{
    if (!GameEngine::GetGameRenderer()->GetRenderer())return nullptr;
    
    SDL_Surface* tmpSurf = IMG_Load(GetPathTranslated(Filename));
    return tmpSurf;
}