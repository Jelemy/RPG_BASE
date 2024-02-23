#include "TextureManager.h"

SDL_Texture* textureManager::loadTexture(const char* texture)
{
    //load file for use as an image in a new surface
    //returns pointer to the image as a new SDL_Surface
    SDL_Surface* tempSurface = IMG_Load(texture);
    
    // Creates texture from existing surface and returns created texture
    SDL_Texture* tex = SDL_CreateTextureFromSurface(game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;

}

void textureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(game::renderer, tex, &src, &dest);
}
