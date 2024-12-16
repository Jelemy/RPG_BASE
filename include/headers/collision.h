#pragma once
#include <SDL.h>

class colliderComponent;

class collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const colliderComponent& colA, const colliderComponent& colB);

};