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
        position.Zero();
    }

    transformComponent(int sc)
    {
        position.Zero();
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
        velocity.Zero();
    }
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};