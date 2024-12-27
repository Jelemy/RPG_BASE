#pragma once

#include "ECS.h"
#include "cTransform.h"
#include "cSprite.h"
#include "SDL.h"

class tileComponent : public Component
{
public:

    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    tileComponent() = default;

    ~tileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    tileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
    {
        texture = textureManager::loadTexture(path);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 32;
    }

    void draw() override
    {
        textureManager::draw(texture, srcRect, destRect);
    }

};