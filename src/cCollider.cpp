#include "cCollider.h"
#include "overWorldState.h"  // Required for using overWorldState
#include "textureManager.h"

colliderComponent::colliderComponent(std::string t) : tag(t) {}

colliderComponent::colliderComponent(std::string t, int xpos, int ypos, int size)
{
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.h = collider.w = size;
}

void colliderComponent::init()
{
    if (!entity->hasComponent<transformComponent>()) {
        entity->addComponent<transformComponent>();
    }
    // get entity position
    transform = &entity->getComponent<transformComponent>();

    tex = textureManager::loadTexture("assets/grass.png");
    srcR = { 0, 0, 32, 32};
    destR = { collider.x, collider.y, collider.w, collider.h};
}

void colliderComponent::update()
{
    //update position of collider box
    if (tag != "terrain")
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y) + 20;
        collider.w = 32;
        collider.h = 32;
    }
}

void colliderComponent::draw()
{
    textureManager::draw(tex, srcR, destR);
}