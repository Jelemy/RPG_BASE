#pragma once

#include "components.h"
#include <Vector2D.h>

class transformComponent : public Component
{

public:
    Vector2D position;


    transformComponent()
    {
        position.x = 0.0f;
        position.y = 0.0f;
    }

    transformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }
    void update() override
    {

    }
};