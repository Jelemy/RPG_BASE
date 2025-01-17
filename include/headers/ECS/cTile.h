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
    
    // srcX and srcY: x and y position on tile atlas
    // xpos ad ypos: x and y position to place tile on window
    // tsize: tile pixel size
    // tscale: for scaling tile up or down
    // path: tile atlas/ tile png path
    tileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
    {
        texture = textureManager::loadTexture(path);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    void draw() override
    {
        textureManager::draw(texture, srcRect, destRect);
    }

};