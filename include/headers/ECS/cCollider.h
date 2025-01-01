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

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    transformComponent* transform;

    colliderComponent(std::string t);
    colliderComponent(std::string t, int xpos, int ypos, int size);

    void init() override;
    void update() override;
    void draw() override;
};