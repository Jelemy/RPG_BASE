#pragma once

#include <string>
#include <SDL.h>
#include <Components.h>

class colliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    transformComponent* transform;

    colliderComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {
        if (!entity->hasComponent<transformComponent>())
        {
            entity->addComponent<transformComponent>();
        }
        transform = &entity->getComponent<transformComponent>();
    }

    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }

    
};