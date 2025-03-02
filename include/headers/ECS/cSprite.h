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
    int currentFrame;
    const char* type;

public:
    spriteComponent() = default;

    spriteComponent(const char* path)
    {
        texture = textureManager::loadTexture(path);
        currentFrame = 0;
    }

    spriteComponent(const char* path, const char* t)
    {
        texture = textureManager::loadTexture(path);
        currentFrame = 0;
        type = t;
    }

    ~spriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void init() override
    {
        transform = &entity->getComponent<transformComponent>();
        int frameW, frameH;
        int texW, texH;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        frameW = texW;
        frameH = texH;
        srcRect.x = srcRect.y = 0;
        if (type == "player") {
            frameW = texW/4;
            frameH = texH/4;
            srcRect.w = frameW;
            srcRect.h = frameH;
            dstRect.w = frameW * transform->scale;
            dstRect.h = frameH * transform->scale;
        }
        else {
            srcRect.w = transform->width;
            srcRect.h = transform->height;
            dstRect.w = transform->width * transform->scale;
            dstRect.h = transform->height * transform->scale;
        }
        
    }

    void update() override
    {

        // Handle frame animation logic
        if (transform->velocity.x != 0 || transform->velocity.y != 0) {
            currentFrame++;
            if (currentFrame == 10) {
                currentFrame = 0;
                srcRect.x += srcRect.w;
                if (srcRect.x >= srcRect.w * 4) {
                    srcRect.x = 0;
                }
            }
        }
        else {
            srcRect.x = 0;
        }
        if (transform->velocity.x > 0) {
            srcRect.y = 78;
        }
        else if (transform->velocity.x < 0) {
            srcRect.y = 52;
        }
        else if (transform->velocity.y > 0) {
            srcRect.y = 0; 
        }
        else if (transform->velocity.y < 0) { 
            srcRect.y = 26;
        }

        // Update position based on transform's velocity
        dstRect.x = (int)transform->position.x;
        dstRect.y = (int)transform->position.y;
    }

    void draw() override
    {
        textureManager::draw(texture, srcRect, dstRect);
        
    }
};