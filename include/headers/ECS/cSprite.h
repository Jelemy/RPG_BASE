#pragma once

#include "components.h"
#include <SDL.h>
#include "textureManager.h"

class spriteComponent : public Component
{
private:
    positionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, dstRect;
public:
    spriteComponent() = default;
    spriteComponent(const char* path)
    {
        texture = textureManager::loadTexture(path);
    }
    void init() override
    {
        position = &entity->getComponent<positionComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = 18;
        srcRect.h = 26;
        dstRect.w = 36;
        dstRect.h = 52;

    }

    void update() override
    {
        dstRect.x = position->x();
        dstRect.y = position->y();

    }

    void draw() override
    {
        
        textureManager::draw(texture, srcRect, dstRect);
        
    }
};