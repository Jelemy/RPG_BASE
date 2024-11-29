#pragma once

#include "components.h"
#include <SDL.h>
#include "textureManager.h"

class spriteComponent : public Component
{
private:
    transformComponent *transform;
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
        transform = &entity->getComponent<transformComponent>();
        int frameW, frameH;
        int texW, texH;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        frameW = texW/4;
        frameH = texH/4;
        srcRect.x = srcRect.y = 0;
        srcRect.w = frameW;
        srcRect.h = frameH;
        dstRect.w = 36;
        dstRect.h = 52;

    }

    void update() override
    {
        dstRect.x = (int)transform->position.x;
        dstRect.y = (int)transform->position.y;

    }

    void draw() override
    {
        textureManager::draw(texture, srcRect, dstRect);
        
    }
};