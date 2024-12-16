#pragma once

#include "ECS.h"
#include "cTransform.h"
#include "cSprite.h"
#include "SDL.h"

class tileComponent : public Component
{
public:
    transformComponent *transform;
    spriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    const char* path;

    tileComponent() = default;

    tileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
            case 0:
                path = "assets/water.png";
                break;
            case 1:
                path = "assets/dirt.png";
                break;
            case 2:
                path = "assets/grass.png";
                break;
            default:
                break;
        }
    }

    void init() override
    {
        entity->addComponent<transformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
        transform = &entity->getComponent<transformComponent>();

        entity->addComponent<spriteComponent>(path);
        sprite = &entity->getComponent<spriteComponent>();
    }
};