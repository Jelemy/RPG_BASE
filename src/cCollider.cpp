#include "cCollider.h"
#include "overWorldState.h"  // Required for using overWorldState

colliderComponent::colliderComponent(std::string t) : tag(t) {}

void colliderComponent::init()
{
    if (!entity->hasComponent<transformComponent>()) {
        entity->addComponent<transformComponent>();
    }
    transform = &entity->getComponent<transformComponent>();

    overWorldState::addCollider(this);  // Use static method from overWorldState
}

void colliderComponent::update()
{
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
}