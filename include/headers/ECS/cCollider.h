#pragma once

#include <string>
#include <SDL.h>
#include <Components.h>

class overWorldState;  // Forward declaration

class colliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    transformComponent* transform;

    colliderComponent(std::string t);

    void init() override;
    void update() override;
};