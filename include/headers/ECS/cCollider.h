#pragma once

#include <string>
#include <SDL.h>
#include <Components.h>

class ColliderComponent : public Component
{
    SDL_Rect collider;
    std::string tag;

    transformComponent* transform;

    void init() override
    {
        if (!entity->hasComponent<transformComponent>())
        {
            entity->addComponent<transformComponent>();
        }
        transform = &entity->getComponent<transformComponent>();
    }

    
};