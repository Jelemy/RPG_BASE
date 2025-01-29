#pragma once

#include "components.h"
#include <SDL.h>
#include "textureManager.h"

class bSpriteComponent : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect srcRect, dstRect;
public:
    
    bSpriteComponent(const char* path, int x, int y)
    {
        texture = textureManager::loadTexture(path);
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = w;
        srcRect.h = h;

        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = w;
        dstRect.h = h;
    }
    int getH(){ return srcRect.h; }
    int getW() {return srcRect.w; }
    int getX() { return dstRect.x; }
    int getY() { return dstRect.y; }

    void setX(int newX) { dstRect.x = newX; }
    void setY(int newY) { dstRect.y = newY; }
    void update() override
    {

    }

    void draw() override
    {
        
        textureManager::draw(texture, srcRect, dstRect);
        
    }
};