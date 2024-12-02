#pragma once

#include <ECS.h>
#include <components.h>

class KeyboardController : public Component {
public:
    transformComponent *transform;

    void init() override;
    void update() override;
};