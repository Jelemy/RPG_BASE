#pragma once

#include "components.h"

class positionComponent : public Component
{
private:
    int xpos;
    int ypos;
public:

    positionComponent()
    {
        xpos = 0;
        ypos = 0;
    }

    positionComponent(int x, int y)
    {
        xpos = x;
        ypos = y;
    }
    void update() override
    {
        xpos++;
        ypos++;
    }

    int  x() { return xpos; }
    int  y() { return ypos; }

    void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }
    
};