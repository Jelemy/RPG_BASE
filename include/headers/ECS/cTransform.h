#pragma once

#include "components.h"
#include <Vector2D.h>

class transformComponent : public Component
{

public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int speed = 3;
    int scale = 1;


    transformComponent()
    {
        position.x = 0.0f;
        position.y = 0.0f;
    }

    transformComponent(int sc)
    {
        position.x = 0.0f;
        position.y = 0.0f;
        scale = sc;
    }


    transformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    transformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};